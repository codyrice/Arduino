/******************************************************************************
Force_Sensitive_Resistor_Example.ino
Example sketch for SparkFun's force sensitive resistors
  (https://www.sparkfun.com/products/9375)
  (https://learn.sparkfun.com/tutorials/force-sensitive-resistor-hookup-guide)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Create a voltage divider circuit combining an FSR with a 3.3k resistor.
- The resistor should connect from A0 to GND.
- The FSR should connect from A0 to 3.3V
As the resistance of the FSR decreases (meaning an increase in pressure), the
voltage at A0 should increase.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
#include <SoftwareSerial.h>

// Setup Bluetooth
SoftwareSerial BT (10, 11); // RX, TX

// Setup input pin for the pressure sensors
const int FSR_PIN = A0; // Pin connected to FSR/resistor divider

// Define Mux control pins
int s0 = 4;
int s1 = 5;
int s2 = 6;
int s3 = 7;

// Setup voltage divider
// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
// their value's below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 990.0; // Measured resistance of 3.3k resistor
int pressure;

// read the value from a specific channel
int readMux(int channel) { 

  // define signal pin
  int SIG_pin = FSR_PIN;
  
  // define control pins
  int controlPin[] = {s0, s1, s2, s3}; 

  // create array of channel values
  int muxChannel[16][4]= { 
    {0,0,0,0}, //channel 0 
    {1,0,0,0}, //channel 1 
    {0,1,0,0}, //channel 2 
    {1,1,0,0}, //channel 3 
    {0,0,1,0}, //channel 4 
    {1,0,1,0}, //channel 5 
    {0,1,1,0}, //channel 6 
    {1,1,1,0}, //channel 7 
    {0,0,0,1}, //channel 8 
    {1,0,0,1}, //channel 9 
    {0,1,0,1}, //channel 10 
    {1,1,0,1}, //channel 11 
    {0,0,1,1}, //channel 12 
    {1,0,1,1}, //channel 13 
    {0,1,1,1}, //channel 14 
    {1,1,1,1}  //channel 15 
  }; 
  
  //loop through the 4 sig 
  for(int i = 0; i < 4; i ++) { 
    digitalWrite (
      controlPin[i], muxChannel[channel][i]
    ); 
  } 
  
  //read the value at the SIG pin 
  int val = analogRead(SIG_pin); 
  
  //return the value 
  return val; 
}

void setup() {

  // Set FSR_PIN to input
  pinMode(FSR_PIN, INPUT);

  // Initialize Bluetooth
  BT.begin(9600);
//  BT.println("Bluetooth initializing...");

  // Set pins to output mode
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

}

void loop() {
String output = "";
  //Loop through and read all 16 values
  //Reports back Value at channel 6 is: 346
  for(int i = 0; i < 16; i ++) {  

    // calculate the pressure
    int calcPressure = readMux(i);
    
    output = output + String(calcPressure) + ",";
//    delay(2);
  } 

  BT.println(output);
    
}

