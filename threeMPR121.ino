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

#include "mpr121.h"

void setup() {
Serial.begin(9600);
init_mpr121();
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
