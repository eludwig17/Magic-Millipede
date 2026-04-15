#include <SPI.h>
#include <SD.h>
// header files from testing speaker I2S protocol
// #include <AudioFileSourceSD.h>
// #include <AudioGeneratorWAV.h>
// #include <AudioOutputI2S.h>

// GPIO Pin Layout for Raspi Pico 2 W
// pinout may need to be changed based on soldering location on perf board
#define LED_R   5   
#define LED_G   6   
#define BTN     2  

void setup() {
  Serial.begin(9600);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);

  delay(2000);
  
  digitalWrite(LED_G, HIGH);
}

void loop() {

  // button logic in testing
  if (digitalRead(BTN) == LOW) {
    delay(200);  
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, HIGH);  

  }
}
