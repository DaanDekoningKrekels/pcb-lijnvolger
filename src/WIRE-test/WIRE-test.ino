// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Wire.h>

void setup() {
  // Deze functie zou de alternatieve pinout moeten activeren.
  // Wire.pins(18, 19);
  Wire.pins(PIN_PA1, PIN_PA2); 
  // Deze functie zou dit ook moeten doen
  Wire.swap(1); 
  // TWI ALT - Deze register schakelt de alternatieve pinout volgens de datasheet in
  PORTMUX.CTRLB |=   1 << 4; 

  // TinyCore: wisselen met alternatieve TWI pinnen
  // Wire.useAlternatePins(); 

  Wire.begin(0x55);              // join i2c bus met adres 0x55
  Wire.onRequest(requestEvent);  // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("oi");  // respond with message of 2 bytes
  // as expected by master
}
