#include "WiFi.h"
#include "esp_bt.h"
#include "LittleFS.h"

#define BTN 32
#define UV_RELAY 26
#define LED_EXTERIOR_RED 22
#define LED_EXTERIOR_GREEN 23
#define LED_INTERIOR_RED 21
#define AUDIO_T00 18
#define AUDIO_T03 14
#define AUDIO_T02 25
#define AUDIO_RST 27

const char* countFile = "/counter.txt";

uint32_t readCount(){
  File f = LittleFS.open(countFile, "r");
  if (!f)
    return 0;
  uint32_t val = f.parseInt();
  f.close();
  return val;
}

void writeCount(uint32_t val){
  File f = LittleFS.open(countFile, "w");
  if (f){
    f.print(val);
    f.close();
  }
}

void triggerAudio(int pin){
  delay(100);
  digitalWrite(pin, LOW);
  delay(200);
  digitalWrite(pin, HIGH);
}

void resetAudio(){
  digitalWrite(AUDIO_RST, LOW);
  delay(10);
  digitalWrite(AUDIO_RST, HIGH);
  delay(500);
}

void setup(){
  WiFi.mode(WIFI_OFF);
  btStop();
  esp_bt_controller_disable();
  LittleFS.begin(true);

  Serial.begin(115200);
  Serial.print("Presentation count: ");
  Serial.println(readCount());
  pinMode(BTN, INPUT_PULLUP);

  pinMode(UV_RELAY, OUTPUT);
  digitalWrite(UV_RELAY, HIGH);

  pinMode(LED_EXTERIOR_RED, OUTPUT);
  digitalWrite(LED_EXTERIOR_RED, LOW);

  pinMode(LED_EXTERIOR_GREEN, OUTPUT);
  digitalWrite(LED_EXTERIOR_GREEN, HIGH);

  pinMode(LED_INTERIOR_RED, OUTPUT);
  digitalWrite(LED_INTERIOR_RED, LOW);

  pinMode(AUDIO_T00, OUTPUT);
  digitalWrite(AUDIO_T00, HIGH);

  pinMode(AUDIO_T03, OUTPUT);
  digitalWrite(AUDIO_T03, HIGH);

  pinMode(AUDIO_T02, OUTPUT);
  digitalWrite(AUDIO_T02, HIGH);

  pinMode(AUDIO_RST, OUTPUT);
  digitalWrite(AUDIO_RST, HIGH);
}

#define IDLE 0
#define PHASE_1 1
#define PHASE_2 2
#define PHASE_3 3

int currState = IDLE;
unsigned long phaseStart = 0;

unsigned long lastBtnPress = 0;
const unsigned long debounce_ms = 50;

void loop(){
  switch (currState){

    case IDLE:
      if (digitalRead(BTN) == LOW && millis() - lastBtnPress > debounce_ms){
        lastBtnPress = millis();
        currState = PHASE_1;
        phaseStart = millis();

        writeCount(readCount() +1);

        // LEDs | green turns off & red turns on
        digitalWrite(LED_EXTERIOR_GREEN, LOW);
        digitalWrite(LED_EXTERIOR_RED, HIGH);

        // trigger audio 1
        triggerAudio(AUDIO_T00);

      }

      break;

    case PHASE_1:
      if (millis() - phaseStart >= 30000){
        currState = PHASE_2;
        phaseStart = millis();

        resetAudio(); // resetting the audio before trigger audio 2
        digitalWrite(UV_RELAY, LOW); // uv lights turn on
        digitalWrite(LED_INTERIOR_RED, HIGH); // red interior light turns off

        // trigger audio #2, switched to T03 in testing, but final result should be set to T01)
        triggerAudio(AUDIO_T03);
      }
      break;

    case PHASE_2:
      if (millis() - phaseStart >= 60000){
        currState = PHASE_3;
        phaseStart = millis();

        resetAudio(); //reset before triggering audio 3

        digitalWrite(UV_RELAY, HIGH);  // uv turns off for last 30 seconds
        // trigger audio #3
        triggerAudio(AUDIO_T02);
      }
      break;

    case PHASE_3:
      if (millis() - phaseStart >= 30000){
        currState = IDLE;

        resetAudio(); // reset sound board one last time to idle state for preparing next narration cycle

        // LEDs | green turns on & red turns off for idle state
        digitalWrite(LED_EXTERIOR_RED,   LOW);
        digitalWrite(LED_EXTERIOR_GREEN, HIGH);

        digitalWrite(LED_INTERIOR_RED, LOW); // red interior back on for idle state


      }
      break;
  }
}
