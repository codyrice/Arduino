#include <SoftwareSerial.h>
SoftwareSerial BT (10, 11); // RX, TX
String command = ""; // Stores response of bluetooth device

void setup ()
{
  Serial.begin (9600);
  Serial.println ("Type AT commands");
  BT.begin (9600); // HC-05 Usually default baud-rate
}

void loop ()
{
  if (BT.available ()) // receive data if available.
  {
    while (BT.available ()) // "keep receiving".
    {
      delay (10); // Delay added to make thing stable
      char c = BT.read (); // Conduct serial read
      command += c; // Build the string.
    }
    Serial.println (command);
    command = ""; // No repeats
  }
  if (Serial.available ())
  {
    delay (10);
    BT.write (Serial.read ());
  }
}
