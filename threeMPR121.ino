/*
Simple arduino sketch to show three MPR121 boards working at the same time

Remember to set the address pins.

As standard address is tied to Ground which gives the default address of 0x5A

To use the other three available channels you need to cut the address pad in the middle and then connect address to the following:

Connect address to 3.3v for 0x5B
Connect address to SDA for 0x5C
Connect address to SCL for 0x5D

gawainhewitt.co.uk
https://github.com/gawainhewitt
*/

#include <Wire.h>
#include <bus1_MPR121.h> // use this modified adafruit library to allow use of other i2c busses - https://github.com/gawainhewitt/bus1_MPR121
// #include "Adafruit_MPR121.h" // alternatively you can use the standard Adafruit library if using bus 0


Adafruit_MPR121 mprBoard_A = Adafruit_MPR121();
Adafruit_MPR121 mprBoard_B = Adafruit_MPR121();
Adafruit_MPR121 mprBoard_C = Adafruit_MPR121();

uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;

uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;

uint16_t lasttouched3 = 0;
uint16_t currtouched3 = 0;

void setup() {
Serial.begin(9600);
if (!mprBoard_A.begin(0x5A)) {
Serial.println("MPR121 A not found, check wiring?");
while (1);
}
Serial.println("MPR121 A found!");

if (!mprBoard_B.begin(0x5B)) {
Serial.println("MPR121 B not found, check wiring?");
while (1);
}
Serial.println("MPR121 B found!");

if (!mprBoard_C.begin(0x5C)) {
Serial.println("MPR121 C not found, check wiring?");
while (1);
}
Serial.println("MPR121 C found!");
}

void loop() {
currtouched1 = mprBoard_A.touched();
currtouched2 = mprBoard_B.touched();
currtouched3 = mprBoard_C.touched();

//For A----------------------------------------------------------
for (uint8_t i=0; i<12; i++) {
if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
Serial.print(i); Serial.println(" touched of A");
}

if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
Serial.print(i); Serial.println(" released of A");
}


//For B----------------------------------------------------------
if ((currtouched2 & _BV(i)) && !(lasttouched2 & _BV(i)) ) {
Serial.print(i); Serial.println(" touched of B");
}

if (!(currtouched2 & _BV(i)) && (lasttouched2 & _BV(i)) ) {
Serial.print(i); Serial.println(" released of B");
}


//For C----------------------------------------------------------
if ((currtouched3 & _BV(i)) && !(lasttouched3 & _BV(i)) ) {
Serial.print(i); Serial.println(" touched of C");
}

if (!(currtouched3 & _BV(i)) && (lasttouched3 & _BV(i)) ) {
Serial.print(i); Serial.println(" released of C");
}
}

lasttouched1 = currtouched1;
lasttouched2 = currtouched2;
lasttouched3 = currtouched3;
return;
}
