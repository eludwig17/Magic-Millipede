#include <SPI.h>
#include <SD.h>

// GPIO Pin Layout for Raspi Pico 2 W
// pinout may need to be changed based on soldering location on perf board
#define LED_INTERIOR_RED 4
#define LED_EXTERIOR_RED 5
#define LED_EXTERIOR_GREEN 6
#define BTN 2
#define UV_RELAY 3
#define AUDIO_T00 7
#define AUDIO_ACT 10


void triggerAudio(int pin){
  digitalWrite(pin, LOW);
  delay(200);
  digitalWrite(pin, HIGH);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_INTERIOR_RED, OUTPUT);
  pinMode(LED_EXTERIOR_RED, OUTPUT);
  pinMode(LED_EXTERIOR_GREEN, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);

  pinMode(UV_RELAY, OUTPUT);
  digitalWrite(UV_RELAY, LOW);
  pinMode(AUDIO_T00, OUTPUT);
  digitalWrite(AUDIO_T00, HIGH);

  // setting all LEDS to LOW(OFF) state until its finished idling/device booted and running state
  digitalWrite(LED_INTERIOR_RED, LOW);
  digitalWrite(LED_EXTERIOR_RED, LOW);
  digitalWrite(LED_EXTERIOR_GREEN, LOW);
  
  // after short idle state sets appropriate LEDS to HIGH(ON)
  delay(2000);
  
  digitalWrite(LED_EXTERIOR_GREEN, HIGH);
  digitalWrite(LED_INTERIOR_RED, HIGH);
}

// state machine setup
#define IDLE 0
#define PHASE_1 1
#define PHASE_2 2
#define PHASE_3 3

int currState = IDLE;
unsigned long phaseStart = 0;

void loop() {
  switch(currState){
    case IDLE:
      if(digitalRead(BTN) == LOW){
        delay(200);
        currState = PHASE_1;
        phaseStart = millis();

        digitalWrite(LED_EXTERIOR_GREEN, LOW);
        digitalWrite(LED_EXTERIOR_RED, HIGH);
        
        // will need to add the trigger for audio track 1 on Adafruit FX sound board here
        triggerAudio(AUDIO_T00);
    }
    break;
    
    case PHASE_1:
      if(millis() - phaseStart >= 30000){
        currState = PHASE_2;
        phaseStart = millis();

        // will need to set trigger for power relay module to turn UV light strip HIGH(ON)
        digitalWrite(UV_RELAY, HIGH);
      }
      break;

    case PHASE_2:
      if(millis() - phaseStart >= 60000){
        currState = PHASE_3;
        phaseStart = millis();

        // at 1:30 turn off interior light for the final 30 seconds of narration
        digitalWrite(LED_INTERIOR_RED, LOW);

        // also another trigger event for power relay module but to turn UV LOW(OFF)
        digitalWrite(UV_RELAY, LOW);
      }
      break;
    
    case PHASE_3:
      if(millis() - phaseStart >= 30000){
        currState = IDLE;
        
        digitalWrite(LED_EXTERIOR_RED, LOW);
        digitalWrite(LED_EXTERIOR_GREEN, HIGH);
        digitalWrite(LED_INTERIOR_RED, HIGH);
      }
      break;
  }
}
