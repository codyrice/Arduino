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

//Mux control pins
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

void setup() 
{
  Serial.begin(9600);
  Serial.println("Serial initializing...");
  pinMode(FSR_PIN, INPUT);
  BT.begin(9600);
  BT.println("Bluetooth initializing...");

  // Set pins to output mode
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  // Read from Channel 15 on MUX
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
}

void loop() 
{
  int fsrADC = analogRead(FSR_PIN);
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC != 0) // If the analog reading is non-zero
  {
    pressure = 1;
    // Use ADC reading to calculate voltage:
    float fsrV = fsrADC * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR = R_DIV * (VCC / fsrV - 1.0);
    BT.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float force;
    float fsrG = 1.0 / fsrR; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR <= 600) 
      force = (fsrG - 0.00075) / 0.00000032639;
    else
      force =  fsrG / 0.000000642857;
    BT.println("Force: " + String(force) + " g");
    BT.println();

  }
  else
  {
    // No pressure detected
    if (pressure == 1) 
    {
      BT.println("no pressure detected");
      pressure = 0;
    }
    
  }
  delay(500);
}

