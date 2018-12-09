/*
 * http://www.instructables.com/id/Arduino-Reading-Sensor-Data-Using-Bluetooth/
 * CONNECT TO OUTGOING PORT HC-05 'DEV-B' TO VIEW DATA ON SERIAL MONITOR
 * USE THIS SKETCH ONLY FOR VIEWING SENSOR DATA ON SERIAL MONITOR.....NOT FOR FILE WRITING
 */

#include <SoftwareSerial.h>
SoftwareSerial BT (10, 11); // RX, TX

int temp; //variable to hold temperature sensor value
long tm,t,d; //variables to record time in seconds
void setup()
{
  Serial.begin(9600);
  //pinMode(0,INPUT);//temperature sensor connected to analog 0
  //analogReference(DEFAULT);
  Serial.println("Starting Test");
  BT.begin(9600);
}

void loop()
{
  //temp = analogRead(0); //analog reading temperature sensor values

  //required for converting time to seconds
//  tm = millis();
//  t = tm/1000;
//  d = tm%1000;

  Serial.flush();

//  //printing time in seconds
//  Serial.print("time : ");
//  Serial.print(t);
//  Serial.print(".");
//  Serial.print(d);
//  Serial.print("s\t");
//
//  //printing temperature sensor values
//  Serial.print("temperature : ");
//  Serial.print(temp);
//  Serial.println("f");

  BT.println("testing");
  
  delay(2000);//delay of 2 seconds
}


