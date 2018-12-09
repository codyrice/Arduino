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
    {1,1,1,1} //channel 15 
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

float CalculatePressure(int fsrADC) {
  
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC != 0) { // If the analog reading is non-zero
//    pressure = 1;
    // Use ADC reading to calculate voltage:
    float fsrV = fsrADC * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR = R_DIV * (VCC / fsrV - 1.0);
//    BT.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float force;
    float fsrG = 1.0 / fsrR; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR <= 600) {
      force = (fsrG - 0.00075) / 0.00000032639;
    }
    else {
      force =  fsrG / 0.000000642857;
//    BT.println("Force: " + String(force) + " g");
//    BT.println();
    }

    // Return calculated force
    return force;
  }
  else
  {
    // No pressure detected
    return fsrADC;
//    if (pressure == 1) 
//    {
//      BT.println("no pressure detected");
//      pressure = 0;
//    }
    
  }
}

void setup() {

  // Set FSR_PIN to input
  pinMode(FSR_PIN, INPUT);

  // Initialize Bluetooth
  BT.begin(9600);
  BT.println("Bluetooth initializing...");

  // Set pins to output mode
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

}

void loop() {

  //Loop through and read all 16 values
  //Reports back Value at channel 6 is: 346
  for(int i = 0; i < 16; i ++) {  

    // calculate the pressure
    float calcPressure = CalculatePressure(readMux(i));
    
    // print the pressure if it isn't zero
    if (calcPressure != 0) {
      BT.print("Value at channel "); 
      BT.print(i); 
      BT.print(" is : ");
      BT.println(calcPressure);
    }
    delay(20); 
  } 
}

