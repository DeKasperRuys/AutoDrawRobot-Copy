#include "Motor.h"

void Motor::InitMotorStates(){
   switch (state){
    case 0:
    // Timer1.stop();
      MotorOut();
      break;
    case 1:
    // Timer1.stop();
      //Forward();
      Reverse();
      break;
    case 2:
    // Timer1.stop();
      //Reverse();
      Forward();
      break;
    case 3:
    // Timer1.stop();
      Left();
      break;
    case 4:
    // Timer1.stop();
      Right();
      break;
    case 5:
    // Timer1.stop();
      PenUp();
      break;
    case 6:
    // Timer1.stop();
      PenDown();
      break;
    case 7:
      Timer1.restart();
      Timer1.start();
      stateNineDof = 1;
      aanUit= true;
      break;
    case 8:
      Timer1.restart();
      Timer1.start();
      stateNineDof = 4;
      aanUit= true;
      break;
    case 9:
      Timer1.restart();
      Timer1.start();
      stateNineDof = 8;
      aanUit= true;
      break;
    case 10:
      Timer1.restart();
      Timer1.start();
      stateNineDof = 5;
      aanUit= true;
      break;
    default:
   // MotorOut();
      break;
  }
 }


void Motor::Reverse(){
  // put motor in back motion
  digitalWrite(motor1LeftPin, LOW); // set leg 1 of the H-bridge low
  digitalWrite(motor2LeftPin, HIGH); // set leg 2 of the H-bridge high
  digitalWrite(motor3RightPin, LOW); // set leg 1 of the H-bridge low
  digitalWrite(motor4RightPin, HIGH); // set leg 2 of the H-bridge high
}

void Motor::Forward(){
  // put motor in forward motion
  digitalWrite(motor1LeftPin, HIGH); // set leg 1 of the H-bridge low
  digitalWrite(motor2LeftPin, LOW); // set leg 2 of the H-bridge high
  digitalWrite(motor3RightPin, HIGH); // set leg 1 of the H-bridge low
  digitalWrite(motor4RightPin, LOW); // set leg 2 of the H-bridge high
}

void Motor::Left(){
    // put motor in Left motion
  digitalWrite(motor1LeftPin, HIGH); // set leg 1 of the H-bridge low
  digitalWrite(motor2LeftPin, LOW); // set leg 2 of the H-bridge high
  digitalWrite(motor3RightPin, LOW); // set leg 1 of the H-bridge low
  digitalWrite(motor4RightPin, HIGH); // set leg 2 of the H-bridge high
}

void Motor::Right(){
  // put motor in right motion
  digitalWrite(motor1LeftPin, LOW); // set leg 1 of the H-bridge low
  digitalWrite(motor2LeftPin, HIGH); // set leg 2 of the H-bridge high
  digitalWrite(motor3RightPin, HIGH); // set leg 1 of the H-bridge low
  digitalWrite(motor4RightPin, LOW); // set leg 2 of the H-bridge high
}

void Motor::LedOn(){
  digitalWrite(led,LOW);
}

void Motor::LedOut(){
  digitalWrite(led,HIGH);
}

void Motor::PenUp(){
 //if you change the delay value (from example change 50 to 10), the speed of the servo changes
 if (servoAngle>=1000){
   // do nothing
 }else
 {
   for(servoAngle = 750; servoAngle < 1000; servoAngle++)  //move the micro servo from 0 degrees to 180 degrees
  {                                  
    servo.write(servoAngle);                            
  }
 } 
}

void Motor::PenDown(){

if (servoAngle<=750){
  // do nothing
 }else
 {
 for(servoAngle = 1000; servoAngle > 750; servoAngle--)  //now move back the micro servo from 0 degrees to 180 degrees
  {                                
    servo.write(servoAngle);              
  }
 } 
}

void Motor::MotorOut(){
    // put motor in Left motion
 digitalWrite(motor1LeftPin, LOW); // set leg 1 of the H-bridge low
 digitalWrite(motor2LeftPin, LOW); // set leg 2 of the H-bridge high
 digitalWrite(motor3RightPin, LOW); // set leg 1 of the H-bridge low
 digitalWrite(motor4RightPin, LOW); // set leg 2 of the H-bridge high
}

void Motor::Init(){
      // set digital i/o pins as outputs: H-bridge
 pinMode(speedLeftPin, OUTPUT);
 pinMode(speedRightPin, OUTPUT);
 pinMode(motor1LeftPin, OUTPUT);
 pinMode(motor2LeftPin, OUTPUT);
 pinMode(motor3RightPin, OUTPUT);
 pinMode(motor4RightPin, OUTPUT);
 pinMode(led, OUTPUT);
 
 
 //servo
 servo.attach(servoPin);
 servo.write(750);  

  // control the speed 0- 255
 speed_value_motor1Left = 255;
 speed_value_motor2Right = 255;
 analogWrite(speedLeftPin, speed_value_motor1Left); // output speed as PWM value Links
 analogWrite(speedRightPin, speed_value_motor2Right );// output speed as PWM value Rechts

 //PenUp();
 }