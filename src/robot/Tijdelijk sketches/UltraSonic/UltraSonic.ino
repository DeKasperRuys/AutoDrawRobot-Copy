#define trigPin1 8
#define echoPin1 3
#define trigPin2 12
#define echoPin2 10
#define trigPin3 A5
#define echoPin3 11
#define trigPin4 A0
#define echoPin4 6
#define INTERVAL_MESSAGE 1000
#define INTERVAL_STOP 5000

int ledFront = A1;
int ledBack = A2;
int ledLeft = A3;
int ledRight = A4;

unsigned long time_ = 0;
long duration, distance,BackSensor,FrontSensor, LeftSensor, RightSensor;

int maximumRange = 400; // Maximum range needed
int minimumRange = 10; // Minimum range needed

void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  
  pinMode(ledFront, OUTPUT);
  pinMode(ledBack, OUTPUT);
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
}

void loop() {

  SonarSensor(trigPin1, echoPin1);
  FrontSensor = distance;
  SonarSensor(trigPin2, echoPin2);
  BackSensor = distance;
  SonarSensor(trigPin3, echoPin3);
  LeftSensor = distance;
  SonarSensor(trigPin4, echoPin4);
  RightSensor = distance;
  DetectObstacle();
  if(millis() > time_ + INTERVAL_MESSAGE){
        time_ = millis();
       // print_time(time_);
        Serial.print(FrontSensor);
        Serial.print("cm FRONT, ");
        Serial.print(" - ");
        Serial.print(BackSensor);
        Serial.print("cm BACK, ");
        Serial.print(LeftSensor);
        Serial.print("cm LEFT, ");
        Serial.print(" - ");
        Serial.print(RightSensor);
        Serial.print("cm RIGHT, ");
        Serial.println();
 }
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
}

void DetectObstacle()
{
  if(FrontSensor > maximumRange || FrontSensor < minimumRange)
  {
    digitalWrite(ledFront, HIGH);
    if(millis() > time_ + INTERVAL_STOP){
      time_ = millis();
     // print_time(time_);
      Serial.println("Front sensor stops");
    }
  }
  else if(BackSensor > maximumRange || BackSensor < minimumRange)
  {
    digitalWrite(ledBack, HIGH);
    if(millis() > time_ + INTERVAL_STOP){
      time_ = millis();
    //  print_time(time_);
      Serial.println("Back sensor stops");
    }
  }
  else if(LeftSensor > maximumRange || LeftSensor < minimumRange)
  {
    digitalWrite(ledLeft, HIGH);
    if(millis() > time_ + INTERVAL_STOP){
      time_ = millis();
     // print_time(time_);
      Serial.println("Left sensor stops");
    }
  }
  else if(RightSensor > maximumRange || RightSensor < minimumRange)
  {
    digitalWrite(ledRight, HIGH);
    if(millis() > time_ + INTERVAL_STOP){
      time_ = millis();
      //print_time(time_);
      Serial.println("Right sensor stops");
    }
  }
  else
  {
    digitalWrite(ledFront, LOW);
    digitalWrite(ledBack, LOW);
    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, LOW);
  }
}

void print_time(unsigned long time_millis){
    Serial.print("Time: ");
    Serial.print(time_millis/1000);
    Serial.print("s - ");
}
