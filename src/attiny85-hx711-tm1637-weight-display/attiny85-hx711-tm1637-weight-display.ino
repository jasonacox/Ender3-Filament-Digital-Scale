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
      2) Record the "HX711 reading" values with NO load on the scale - this is your "offset_value"
      3) Use an trusted scale and weigh an object (grams) - record this value as your "known_value"
      4) Place the object on the load cell and record the "HX711 reading" - this is "calibration_value"
      5) Compute the ratio_value = (calibration_value - offset_value) / known_value
      6) Edit the #defines below for CAL_RATIO and CAL_OFFSET

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
#include "EEPROM.h"
#include "HX711.h"
#include "segment.h"

// Include TM1637TinyDisplay Library https://github.com/jasonacox/TM1637TinyDisplay
#include <Arduino.h>
#include <TM1637TinyDisplay.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 1;
const int LOADCELL_SCK_PIN = 2;

// Pins definitions for TM1637 and can be changed to other ports
#define CLK 3
#define DIO 4
TM1637TinyDisplay display(CLK, DIO);

// Pin for Tare button
#define BUTTON 0

// Debug mode for setting callibration
#define DEBUG false

// Calibration values
#define CAL_RATIO 103.64
#define CAL_OFFSET -123916

HX711 scale;

void setup() {

#if DEBUG == true
  Serial.begin(38400);
#endif

  // Set Tare button
  pinMode(BUTTON, INPUT);

  display.setBrightness(0x0f); // set the brightness to 100 %
  delay(10);

  // Display Startup Sequence
  for (int x = 0; x < 5; x++) {
    display.setSegments(SEG_ON);
    delay(200);
    display.clear();
    delay(100);
  }
  for (int count = 0; count < 3; count++) {
    for (int x = 0; x < 12; x++) {
      display.setSegments(SEG_START[x]);
      delay(10);
    }
  }
  display.showString("----");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  long offset = 0;
  scale.set_scale(CAL_RATIO); // 98.11
  EEPROM.get(0, offset);
  if (offset == 0) {
    scale.set_offset(CAL_OFFSET); // default
  }
  else {
    scale.set_offset(offset);
  }

}

void loop() {

  if (scale.is_ready()) {
    long reading = scale.read();
#if DEBUG == true
    Serial.print("HX711 reading: ");
    Serial.println(reading);
#endif
    // Display weight
    display.showNumberDec((int)scale.get_units(10), false);

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
