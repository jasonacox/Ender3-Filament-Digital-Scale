/*
  ATtiny85 Weight Scale (grams) using HX711 Load Cell module and TM1637 Display

  Author: Jason A. Cox - @jasonacox

  Date: 22 June 2020

  Components:
      ATiny85 Microcontroller
      TM1636 4 Digit 7-Segment LED Display
      Load Cell
      HX711 Load Cell Amplifier (ADC)
      100uF Electrolytic Capacitor
      5V Power Supply

  Callibration:
      This sketch requires that you calibrate the load cell.  This involves the following steps:
      1) Run the sketch with DEBUG true (using a Arduino Uno or other microcontroller with serial)
      2) Record the "HX711 reading" values with NO load on the scale - this is your "CAL_OFFSET"
      3) Use an trusted scale and weigh an object (grams) - record this value as your "KNOWN_VALUE"
      4) Place the object on the load cell and record the "HX711 reading" - this is "CAL_VALUE"
      5) Compute the CAL_RATIO value = (CAL_VALUE - CAL_OFFSET) / KNOWN_VALUE
      6) Edit the #defines below

      Example:
        CAL_OFFSET = -148550
        KNOWN_VALUE =  382.7186 g
        CAL_VALUE = -107150
        CAL_RATIO = (CAL_VALUE - CAL_OFFSET) / KNOWN_VALUE
        CAL_RATIO = ((-107150) - (-148550 )) / (382.7186)
        CAL_RATIO = 108.17

  Programming Notes:
      The TARE button uses PB0. If you use the Tiny AVR Programmer from Sparkfun
      it drives an LED on PB0 and once the sketch is uploaded, the TTiny will read PB0 as LOW
      and assume you wish to TARE the scale. You will need to remove the the chip from the
      programmer after uploading to get it to work correctly in the circuit.

  Function:
      On start the circuit will read the last TARE value from EEPROM and display the the
      current weight. Press and hold the TARE button and the current weight value will be
      recorded in EEPROM and subtracted from the current reading to "Zero" out the scale.

*/

// Includes
#include "EEPROM.h"   // Used to store tare values in EEPROM
#include "segment.h"  // Animations for Display

// Include TM1637TinyDisplay Library https://github.com/jasonacox/TM1637TinyDisplay
#include <Arduino.h>
#include <TM1637TinyDisplay.h>

// Include HX711 Arduino Library https://github.com/bogde/HX711
#include <HX711.h>

/*
    CONFIGURATION SECTION - Update these values
*/
// Arduino Pin settings - UPDATE this section for your circuit
const int LOADCELL_DOUT_PIN = 2;  // HX711 DT Pin             (ATtiny85: 1)
const int LOADCELL_SCK_PIN = 3;   // HX711 SK Pin             (ATtiny85: 2)
#define CLK 4                     // TM1637 Display CLK Pin   (ATtiny85: 3)
#define DIO 5                     // TM1637 Display DIO Pin   (ATtiny85: 4)
#define BUTTON 8                  // Tare Button - Pulled up  (ATtiny85: 0)

// Turn on debug mode for setting callibration
#define DEBUG true

// Calibration values - UPDATE this section for your load cell - see instructions above
#define CAL_OFFSET -148550       // HX711 reading with no weight
#define CAL_VALUE  -107150       // HX711 reading with item placed on scale
#define KNOWN_VALUE    382.7186  // True weight of item placed on scale (e.g. in grams)

/*
   Calibration ratio will be computed based on the above
   CAL_RATIO = (CAL_VALUE  -  CAL_OFFSET)  /  KNOWN_VALUE
*/
#define CAL_RATIO  ((CAL_VALUE) - (CAL_OFFSET)) / (KNOWN_VALUE)

#define READ_SAMPLES 15   // Number of readings to average each cycle

/*
   SETUP
*/
// Initialize Global Classes 
TM1637TinyDisplay display(CLK, DIO);
HX711 scale;

void setup() {
#if DEBUG == true
  Serial.begin(38400);
#endif
  pinMode(BUTTON, INPUT);       // Set Tare button
  display.setBrightness(0x0f); // set the brightness to 100 %
  delay(10);

  // Display Startup Sequence
  for (int x = 0; x < 5; x++) {
    display.showStr ing(" On ");
    delay(200);
    display.clear();
    delay(100);
  }
  display.showAnimation(ANIMATION, FRAMES(ANIMATION), TIME_MS(10));
  display.showString("Ender 3 Pro");
  display.showString("----");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  long offset = 0;
  scale.set_scale(CAL_RATIO);
  EEPROM.get(0, offset);
  if (offset == 0) {
    scale.set_offset(CAL_OFFSET); // default
  }
  else {
    scale.set_offset(offset);
  }
}

/*
   LOOP
*/
void loop() {
  if (scale.is_ready()) {
    long reading = scale.read_average(READ_SAMPLES);
#if DEBUG == true
    Serial.print("HX711 reading: ");
    Serial.print(reading);
    Serial.print(" ::: [ CAL_OFFSET: ");
    Serial.print(scale.get_offset());
    Serial.print(", CAL_RATIO: ");
    Serial.print(scale.get_scale());
    Serial.print(", Adjusted Value: ");
    Serial.print((reading - scale.get_offset()) / scale.get_scale());
    Serial.println(" ]");
#endif
    // Display weight
    display.showNumber((int)((reading - scale.get_offset()) / scale.get_scale()));

    // Check to see if TARE button is pushed
    if (digitalRead(BUTTON) == LOW) {
      display.showString("Tare");
      delay(500);
      EEPROM.put(0, reading);       // Save tare value to EEPROM
      scale.set_offset(reading);    // Update offset
      // Display flashing zero to indicate tare set
      for (int x = 0; x < 5; x++) {
        display.clear();
        delay(50);
        display.showNumberDec(0, 4);
        delay(100);
      }
      display.showString("----");
    }
    else {
      delay(100);
    }
  }
  else {
    // HX711 not responding
#if DEBUG == true
    Serial.println("HX711 not found.");
#endif
    display.showString("Err");
    delay(100);
  }
}
