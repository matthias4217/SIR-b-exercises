import processing.serial.*; //import serial communication classes

import cc.arduino.*; //import Arduino classes

/**
 * Simple program to get a raw measure on pin measurPin
 */

Arduino arduino;

//declare an Arduino object

int measurePin = 3;

void setup() // runs once at start
{
//println(Arduino.list()); // use this to get port#
  arduino = new Arduino(this, Arduino.list()[0], 57600); //instanciate own Arduino object // COM port number and baudrate

//arduino.pinMode(ledPin, Arduino.OUTPUT);

}

void draw() //loops forever
{
  println(arduino.analogRead(measurePin));
  delay(100);
}
