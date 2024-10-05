#include <Arduino.h>

int latchPin = 2;
int clockPin = 3;
int dataPin = 5; 
int resetPin = 4;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  Serial.begin(9600);
}

// Function to shift data in LSB (Least Significant Bit) first
void shiftInByteLSB(byte data) {
  for(int i = 0; i <= 8; i++) {    // Loop from 0 to 7
    int bit = (data >> i) & 0x01;  // shift data right ny i positions and mask with 0x01
    Serial.println(bit);           // Print the extracted bit 
    shiftInBit(bit);               // Call the function to shift in the current bit 
  }
}

// Function to shift data in MSB (Most Significant Bit) first
void shiftInByteMSB(byte data) {
  for(int i = 8; i > 0; i--) {    // Loop from 7 to 0
    int bit = (data >> i) & 0x01; // Shift data right by i positions and mask with 0x01
    Serial.println(bit);          // Print the extracted bit
    shiftInBit(bit);              // Call function to shift in the current bit
  }
}

// Code to Shift in a single bit to the register
void shiftInBit(int bit){
  digitalWrite(dataPin, bit);   // Write the bit to the data pin
  digitalWrite(clockPin, HIGH); 
  digitalWrite(clockPin, LOW);  // Pulse the clock pin to shift the data in
}

// Function to latch the shifted in data to the shift registers output pins
void latch() {
  digitalWrite(latchPin, HIGH);
  delayMicroseconds(50);  // delay to ensure HigH pulse is registered
  digitalWrite(latchPin, LOW);
}

// Function to reset the data inside the shift register
void reset() {
  digitalWrite(resetPin, LOW);
  delayMicroseconds(50);  // Delay to ensure LOW pulse is registered
  digitalWrite(resetPin, HIGH);
}

void loop() {

  // example code
  digitalWrite(resetPin,HIGH);
  byte dataA = 0x00;
  for(int i = 0; i<256; i++) {
    shiftInByteMSB(dataA + i);
    latch();
    delay(500);
    reset();
  }
}