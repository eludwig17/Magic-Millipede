#include "WiFi.h"
#include "esp_bt.h"
#include "LittleFS.h"

#define BTN 32
#define UV_RELAY 26
#define LED_EXTERIOR_RED 22
#define LED_EXTERIOR_GREEN 23
#define LED_INTERIOR_RED 21

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
  digitalWrite(pin, LOW);
  delay(200);
  digitalWrite(pin, HIGH);
}

void setup(){
  WiFi.mode(WIFI_OFF);
  btStop();
  esp_bt_controller_disable();
  LittleFS.begin(true);

  pinMode(BTN, INPUT_PULLUP);

  pinMode(UV_RELAY, OUTPUT);
  digitalWrite(UV_RELAY, HIGH); 

  pinMode(LED_EXTERIOR_RED, OUTPUT);
  digitalWrite(LED_EXTERIOR_RED, LOW); 

  pinMode(LED_EXTERIOR_GREEN, OUTPUT);
  digitalWrite(LED_EXTERIOR_GREEN, HIGH);

  pinMode(LED_INTERIOR_RED, OUTPUT);
  digitalWrite(LED_INTERIOR_RED, LOW);
}

#define IDLE 0
#define PHASE_1 1
#define PHASE_2 2
#define PHASE_3 3

int currState = IDLE;
unsigned long phaseStart = 0;

void loop(){
  switch (currState){

    case IDLE:
      if (digitalRead(BTN) == LOW){
        currState = PHASE_1;
        phaseStart = millis();

        writeCount(readCount() +1);

        // LEDs | green turns off & red turns on
        digitalWrite(LED_EXTERIOR_GREEN, LOW); 
        digitalWrite(LED_EXTERIOR_RED,   HIGH);
    
      }
      
      break;

    case PHASE_1:
      if (millis() - phaseStart >= 30000){
        currState = PHASE_2;
        phaseStart = millis();

        digitalWrite(UV_RELAY, LOW); // uv lights turn on
        digitalWrite(LED_INTERIOR_RED, HIGH); // red interior light turns off
      }
      break;

    case PHASE_2:
      if (millis() - phaseStart >= 60000){
        currState = PHASE_3;
        phaseStart = millis();

        digitalWrite(UV_RELAY, HIGH);  // uv turns off for last 30 seconds
      }
      break;

    case PHASE_3:
      if (millis() - phaseStart >= 30000){
        currState = IDLE;

        // LEDs | green turns on & red turns off for idle state
        digitalWrite(LED_EXTERIOR_RED,   LOW); 
        digitalWrite(LED_EXTERIOR_GREEN, HIGH);

        digitalWrite(LED_INTERIOR_RED, LOW); // red interior back on for idle state
      }
      break;
  }
}
