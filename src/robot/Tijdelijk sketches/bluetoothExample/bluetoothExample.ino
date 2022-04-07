#include <SoftwareSerial.h>
SoftwareSerial bt(0,1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bt.begin(38400);
  bt.println("Hello, world");
  
}

void loop() {

  if(bt.available())
  {
    Serial.write(bt.read());
  }
  
  while(Serial.available()){
    bt.write(Serial.read());
  }
}
