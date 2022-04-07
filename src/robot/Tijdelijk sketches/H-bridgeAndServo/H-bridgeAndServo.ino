/*
 * Arduino code for SN754410 H-bridge
 * motor driver control.
 * servo
 */

 //servo libraries
 #include <Servo.h>
 Servo servo;  

//pins
 const int speedLeftPin = 3; // H-bridge enable pin for speed control Link Motor
 const int motor4RightPin = 4; // H-bridge leg 2.R (4) reverse
 const int motor3RightPin = 5; // H-bridge leg 1.R (3) forward
 const int motor1LeftPin = 13; // H-bridge leg 1.L (1) forward
 const int motor2LeftPin = 7; // H-bridge leg 2.L (2) reverse
 const int speedRightPin = 8; // H-bridge enable pin for speed control Right Motor
 const int servoPin = 9;
 
//values
  int servoAngle = 0;   // servo position in degrees
  int speed_value_motor1Left; // value for motor speed
  int speed_value_motor2Right; // value for motor speed

void setup() {
  
 //serial
  Serial.begin(9600);  
  
 // set digital i/o pins as outputs: H-bridge
 pinMode(speedLeftPin, OUTPUT);
 pinMode(speedRightPin,OUTPUT);
 pinMode(motor1LeftPin, OUTPUT);
 pinMode(motor2LeftPin, OUTPUT);
 pinMode(motor3RightPin, OUTPUT);
 pinMode(motor4RightPin, OUTPUT);
 
 //servo
 servo.attach(servoPin);

  // control the speed 0- 255
 speed_value_motor1Left = 200; // half speed
 speed_value_motor2Right = 200;
}
void loop() {
 
//Reverse();
//Forward();
//Left();
//Right();

 analogWrite(speedLeftPin, speed_value_motor1Left); // output speed as PWM value Links
 analogWrite(speedRightPin, speed_value_motor2Right);// output speed as PWM value Rechts
 //control the servo's direction and the position of the motor

 /* servo.write(45);      // Turn SG90 servo Left to 45 degrees
   delay(1000);          // Wait 1 second
   servo.write(90);      // Turn SG90 servo back to 90 degrees (center position)
   delay(1000);          // Wait 1 second
   servo.write(135);     // Turn SG90 servo Right to 135 degrees
   delay(1000);          // Wait 1 second
   servo.write(90);      // Turn SG90 servo back to 90 degrees (center position)
   delay(1000); 

//end control the servo's direction and the position of the motor


//control the servo's speed  

//if you change the delay value (from example change 50 to 10), the speed of the servo changes
  for(servoAngle = 0; servoAngle < 180; servoAngle++)  //move the micro servo from 0 degrees to 180 degrees
  {                                  
    servo.write(servoAngle);              
    delay(50);                  
  }

  for(servoAngle = 180; servoAngle > 0; servoAngle--)  //now move back the micro servo from 0 degrees to 180 degrees
  {                                
    servo.write(servoAngle);          
    delay(10);      
  }
  //end control the servo's speed  
  */
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
