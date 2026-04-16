#include <SPI.h>
#include <SD.h>
// header files from testing speaker I2S protocol
// #include <AudioFileSourceSD.h>
// #include <AudioGeneratorWAV.h>
// #include <AudioOutputI2S.h>

// GPIO Pin Layout for Raspi Pico 2 W
// pinout may need to be changed based on soldering location on perf board
#define LED_INTERIOR_RED 4
#define LED_EXTERIOR_RED 5
#define LED_EXTERIOR_GREEN 6
#define BTN 2

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_INTERIOR_RED, OUTPUT);
  pinMode(LED_EXTERIOR_RED, OUTPUT);
  pinMode(LED_EXTERIOR_GREEN, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);

  // setting all LEDS to LOW(OFF) state until its finished idling/device booted and running state
  digitalWrite(LED_INTERIOR_RED, LOW);
  digitalWrite(LED_EXTERIOR_RED, LOW);
  digitalWrite(LED_EXTERIOR_GREEN, LOW);
  
  // after short idle state sets appropriate LEDS to HIGH(ON)
  delay(2000);
  
  digitalWrite(LED_EXTERIOR_GREEN, HIGH);
  digitalWrite(LED_INTERIOR_RED, HIGH);
}

void loop() {

  // button logic in testing
  if (digitalRead(BTN) == LOW) {
    delay(200);  
    digitalWrite(LED_EXTERIOR_GREEN, LOW);
    digitalWrite(LED_EXTERIOR_RED, HIGH);  

  }
}
