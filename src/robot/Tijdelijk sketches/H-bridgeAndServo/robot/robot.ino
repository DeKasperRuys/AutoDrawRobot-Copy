 //servo libraries
 #include <Servo.h>
 Servo servo;  

//pins
 //pwmpinnen
 const int speedLeftPin = 3; // H-bridge enable pin for speed control Link Motor
 const int speedRightPin = 5; // H-bridge enable pin for speed control Right Motor
 
 const int motor4RightPin = 4; // H-bridge leg 2.R (4) reverse
 const int motor3RightPin = 9; // H-bridge leg 1.R (3) forward
 
 const int motor1LeftPin = 8; // H-bridge leg 1.L (1) forward
 const int motor2LeftPin = 7; // H-bridge leg 2.L (2) reverse
 const int servoPin = 10;
 
//values
  int servoAngle = 0;   // servo position in degrees
  int speed_value_motor1Left; // value for motor speed
  int speed_value_motor2Right; // value for motor speed
  int state = 0;

void setup() {
  
 //serial
  Serial.begin(9600);  
  
 // set digital i/o pins as outputs: H-bridge
 pinMode(speedLeftPin, OUTPUT);
 pinMode(speedRightPin, OUTPUT);
 pinMode(motor1LeftPin, OUTPUT);
 pinMode(motor2LeftPin, OUTPUT);
 pinMode(motor3RightPin, OUTPUT);
 pinMode(motor4RightPin, OUTPUT);
 
 //servo
 servo.attach(servoPin);
 servo.write(0);  

  // control the speed 0- 255
 speed_value_motor1Left = 180; // half speed
 speed_value_motor2Right = 180;
 analogWrite(speedLeftPin, speed_value_motor1Left); // output speed as PWM value Links
 analogWrite(speedRightPin, speed_value_motor2Right );// output speed as PWM value Rechts

 state = 2;
}
void loop() {
 switch (state){
    case 0:
      delay(50);
      break;
    case 1:
      Forward();
      break;
     case 2:
     Reverse();
      break;
     case 3:
     Left();
      break;
    case 4:
     Right();
      break;
    case 5:
     PenUp();
      break;
    case 6:
    PenDown();
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      delay(50);
      break;
  } 
}

int Reverse(){
  // put motor in back motion
 digitalWrite(motor1LeftPin, LOW); // set leg 1 of the H-bridge low
 digitalWrite(motor2LeftPin, HIGH); // set leg 2 of the H-bridge high
 digitalWrite(motor3RightPin, LOW); // set leg 1 of the H-bridge low
 digitalWrite(motor4RightPin, HIGH); // set leg 2 of the H-bridge high
}

int Forward(){
  // put motor in forward motion
 digitalWrite(motor1LeftPin, HIGH); // set leg 1 of the H-bridge low
 digitalWrite(motor2LeftPin, LOW); // set leg 2 of the H-bridge high
 digitalWrite(motor3RightPin, HIGH); // set leg 1 of the H-bridge low
 digitalWrite(motor4RightPin, LOW); // set leg 2 of the H-bridge high
}

int Left(){
    // put motor in Left motion
 digitalWrite(motor1LeftPin, LOW); // set leg 1 of the H-bridge low
 digitalWrite(motor2LeftPin, HIGH); // set leg 2 of the H-bridge high
 digitalWrite(motor3RightPin, HIGH); // set leg 1 of the H-bridge low
 digitalWrite(motor4RightPin, LOW); // set leg 2 of the H-bridge high
}

int Right(){
  // put motor in right motion
 digitalWrite(motor1LeftPin, HIGH); // set leg 1 of the H-bridge low
 digitalWrite(motor2LeftPin, LOW); // set leg 2 of the H-bridge high
 digitalWrite(motor3RightPin, LOW); // set leg 1 of the H-bridge low
 digitalWrite(motor4RightPin, HIGH); // set leg 2 of the H-bridge high
}

int PenUp(){
  // put pen up
 //if you change the delay value (from example change 50 to 10), the speed of the servo changes
  for(servoAngle = 90; servoAngle < 180; servoAngle++)  //move the micro servo from 0 degrees to 180 degrees
  {                                  
    servo.write(servoAngle);              
    delay(10);                  
  }
}

int PenDown(){
  for(servoAngle = 180; servoAngle > 90; servoAngle--)  //now move back the micro servo from 0 degrees to 180 degrees
  {                                
    servo.write(servoAngle);          
    delay(10);      
  }
  }
