#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include <TimerOne.h>
#include"ServoTimer2.h"


class Motor
{
private:
//Servo servo;
ServoTimer2 servo;     
public:
//pwmpinnen
const int speedLeftPin = 3; // H-bridge enable pin for speed control Link Motor
const int speedRightPin = 5; // H-bridge enable pin for speed control Right Motor
const int motor4RightPin = 4; // H-bridge leg 2.R (4) reverse
const int motor3RightPin = 9; // H-bridge leg 1.R (3) forward
const int motor1LeftPin = 8; // H-bridge leg 1.L (1) forward
const int motor2LeftPin = 7; //  H-bridge leg 2.L (2) reverse
const int servoPin = 10;
const int led = 12; //led 

//values
int servoAngle = 750;   // servo position in degrees
int speed_value_motor1Left; // value for motor speed
int speed_value_motor2Right; // value for motor speed
int state = 0;
int stateNineDof = 0;
bool aanUit = false;

//methods
void Init();
void Forward();
void Reverse();
void Left();
void Right();
void PenUp();
void LedOn();
void LedOut();
void PenDown();
void MotorOut();
void InitMotorStates();
void InitPenStates();
};

#endif