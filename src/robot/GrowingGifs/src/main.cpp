#include <Arduino.h>
#include "Bluetooth/Bluetooth.h"
#include "Motor/Motor.h"
#include "ServoTimer2.h"
#include "Ultrasonic/UltraSonic.h"
#include "NineDof/NineDof.h"
#include <TimerOne.h>
Motor motor;
#include "Coordinaten/CoordinatenHandler.h"
#include "MemoryFree/MemoryFree.h"
Bluetooth BT(16,17);
UltraSonic UltraSonicSensor(13, 2, 14,15);
NineDof nineDof;
CoordinatenHandler handler(16,17);

void nineDofStates(){
   switch (motor.stateNineDof){
    case 0:
     nineDof.angle = 0;
     motor.state = 0;
      break;
    case 1:
      nineDof.angle = 42.5;
      motor.state = 3;
      break;
    case 2:
      nineDof.angle = 42.5;
      motor.state = 4;
      break;
    case 3:
      nineDof.angle = 85;
      motor.state = 3;
      break;
    case 4:
      nineDof.angle = 85;
      motor.state = 4;
      break;
    case 5:
      nineDof.angle = 127.5;
      motor.state = 3;
      break;
    case 6:
      nineDof.angle = 127.5;
      motor.state = 4;
      break;
    case 7:
      nineDof.angle = 170;
      motor.state = 3;
      break;
    case 8:
      nineDof.angle = 170;
      motor.state = 4;
      break;
    }
}

void timerFunction(){

  if (motor.aanUit == true){
    nineDof.OnOrOff = 2;
    motor.aanUit = false;
  }

  switch (nineDof.OnOrOff){
    case 0:
      Serial.println("ninedof uit");
     motor.state = 0;
     Timer1.stop();
      break;
    case 1:
      nineDof.OnOrOff = 1;
      nineDofStates();
      break;
    case 2:
      //startposition start op 2 gaat meteen naar 1 nadat de timer wordt aangezet
      nineDof.OnOrOff = 1;
      break;
    }
  }

  void timerInit(){
    Timer1.initialize(250000); // 1 million microseconds is 1 second (250 000 = 1/4 of a second)
    Timer1.attachInterrupt(timerFunction);
    Timer1.stop();
}

void setup() {
  motor.Init();
  nineDof.Init();
  timerInit();
  Serial.begin(19200);
  Serial.begin(115200);
  Serial.println("Hello from Arduino");
  UltraSonicSensor.start = true;
}

void loop() {
 BT.Receive();

handler.Run();

  if(Serial.available() > 0)
  {
    char data = Serial.read();
    BT.Send(data);
  }

 if(nineDof.OnOrOff == 1){
nineDof.loopPart();
 }

  motor.InitMotorStates();

 UltraSonicSensor.Collision();
 UltraSonicSensor.ObstacleDetector();
 UltraSonicSensor.SonarSensor();
if(nineDof.OnOrOff != 1 && motor.state !=0 && motor.state !=5 && motor.state !=6 ){
}

void loop() {

handler.Run();

}

//UltraSonicSensor.SonarSensor();
 //UltraSonicSensor.PositionTracker();
 //UltraSonicSensor.ObstacleDetector();
 //UltraSonicSensor.Collision();
  
  // UltraSonicSensor.MeasureFront();
  // UltraSonicSensor.MeasureBack();
  // UltraSonicSensor.MeasureLength();
  //UltraSonicSensor.TrackCenter();
  //UltraSonicSensor.GoToCoordinate();
 //BT.Send(UltraSonicSensor.data);

}


