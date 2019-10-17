#include<SoftwareSerial.h>

SoftwareSerial serial(13, 12); //rx, tx

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  while(!Serial);

  serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  serial.write(millis());
  delay(500);
}
