#include "UltraSonic.h"
 UltraSonic::UltraSonic(int trigL, int echoL, int trigF, int echoF)
{
   
  trigPinL = trigL;
  echoPinL = echoL;
  trigPinF = trigF;
  echoPinF = echoF;
}

void UltraSonic::SonarSensor()
{

  digitalWrite(trigPinF, LOW);
  if(micros() > time_3 + 2){
    time_3 = micros();
    digitalWrite(trigPinF, HIGH);
    digitalWrite(trigPinL, HIGH);
  }
  if(micros() > time_4 + 10){
    time_4 = micros();
    digitalWrite(trigPinL, LOW);
    duration = pulseIn(echoPinL, HIGH);
    LeftSensor = (duration/2) / 29.1;
    digitalWrite(trigPinF, LOW);
    duration2 = pulseIn(echoPinF, HIGH);
    FrontSensor = (duration2/2) / 29.1;
  } 
}

void UltraSonic::ObstacleDetector()
{
  if(FrontSensor != 0)
  {
    Front = FrontSensor;
  }
  if(LeftSensor != 0)
  {
    Left = LeftSensor;
  }
  if(millis() > time_1 + INTERVAL_MESSAGE_1){
    time_1 = millis();
    if(Front <= MinRange && Front != 0)
    {
       collision = 1;
       Serial.print("Obstacle detected front ");
       Serial.print(collision);
       Serial.print (" ");
       Serial.print(Front);
       Serial.println(" cm");
    }
    else
    {
       collision = 0;
       Serial.print("Obstacle detected front ");
       Serial.print(collision);
       Serial.print (" ");
       Serial.print(Front);
       Serial.println(" cm");
    }}

     if(millis() > time_2 + INTERVAL_MESSAGE_2){
    time_2 = millis();
    if(Left <= MinRange && Left != 0)
    {
       collision = 2;
       Serial.print("Obstacle detected left ");
       Serial.print(collision);
       Serial.print (" ");
       Serial.print(Left);
       Serial.println(" cm");
    }
    else
    {
       collision = 0;
       Serial.print("Obstacle detected left ");
       Serial.print(collision);
       Serial.print (" ");
       Serial.print(Left);
       Serial.println(" cm");
    }}

    
}

void UltraSonic::PositionTracker()
{
  if(FrontSensor != 0)
  {
    Front = FrontSensor;
  }
  if(LeftSensor != 0)
  {
    Left = LeftSensor;
  }
    switch (motor.state)
    {
      case 0:
        Serial.print("Positie van de robot is ");
        Serial.print("(");
        Serial.print(Left);
        Serial.print(",");
        Serial.print(Front);
        Serial.println(")");
        currentY = Front;
        currentX = Left;
        break;
      
      case 7:
        rotation = 90;
        nextY = Left;
        nextX = (Length - Front) - LengthRobot;
        Serial.print("Positie van de robot is ");
        Serial.print("(");
        Serial.print(nextX);
        Serial.print(",");
        Serial.print(nextY);
        Serial.println(")");
        currentX = nextX;
        currentY = nextY;
        break;

      case 8:
        rotation = 180;
        nextY = (Length - Front) - LengthRobot;
        nextX = (Length - Left) - WidthRobot;
        Serial.print("Positie van de robot is ");
        Serial.print("(");
        Serial.print(nextX);
        Serial.print(",");
        Serial.print(nextY);
        Serial.println(")");
        currentY = nextY;
        currentX = nextX;
        break;

      case 9:
        rotation = 270;
        nextY = (Length - Left) - WidthRobot;
        nextX = Front;
        Serial.print("Positie van de robot is ");
        Serial.print("(");
        Serial.print(nextX);
        Serial.print(",");
        Serial.print(nextY);
        Serial.println(")");
        currentY = nextY;
        currentX = nextX;

      default:
        break;
    }
}

void UltraSonic::Collision()
{
  if (collision == 0){
  motor.LedOut();
  motor.MotorOut();
  }else if (collision == 1){
  motor.LedOn();
  motor.Forward();
  //motor.Reverse();
  delay(100);
  motor.MotorOut();
  collision = 0;
  }else if (collision == 2){
  motor.LedOn();
  motor.Right();
  delay(100);
  motor.MotorOut();
  collision = 0;}
}

void UltraSonic::TrackCenter()
{
  if(FrontSensor != 0)
  {
    Front = FrontSensor;
  }
  if(LeftSensor != 0)
  {
    Left = LeftSensor;
  }

  if (Cflag == true){
    if(Fflag == false){
      motor.MotorOut();
      Serial.println("Robot heeft het middenpunt bereikt");
      Cflag = false;
      goToCenter = false;
    }
   }

  if(goToCenter == true)
  {

    if (RiFlag == true){
      motor.Right();
      Serial.print("robot gaat naar rechts");
      Serial.println(Left);
      delay(1800);
      motor.MotorOut();
      RiFlag = false;
      Fflag = true;
    }

    if(LeFlag == true)
    {
      motor.Left();
      Serial.print("robot gaat naar links");
      Serial.println(Left);
      delay(1800);
      motor.MotorOut();
      motor.LedOn();
      LeFlag = false;
      Fflag = true;
    }

    if(goForward == true)
    {
      motor.Forward();
      delay(50);
      Serial.print("vooruit ");
      Serial.println(Front);
      goForward = false;
    }

    if(goBack== true)
    {
      motor.Reverse();
      delay(50);
      Serial.print("achteruit ");
      Serial.println(Front);
      goBack = false;
    }

    if(Fflag == true){
      if(Front < centerPoint && Front > 0)
      {
        goBack = true;
      }
      else if (Front > centerPoint && Front <= 400)
      {
        goForward = true;
      }
      else if(Front >= centerPoint && Front <= (centerPoint + 5))
      { 
        motor.MotorOut();
        if(Left < centerPoint)
        {
          RiFlag = true;
        }
        else if(Left > centerPoint)
        {
          LeFlag = true;
        }
      }
      else if(Front > 400){}
      else if(Front >= centerPoint && Front <= (centerPoint + 5) && Left >= centerPoint && Left <= (centerPoint + 5))
      {
        Fflag = false;
        Cflag = true;
      }
    }
  }
}

void UltraSonic::MeasureFront()
{
  if(start == true)
  {
  while(FrontSensor != 0){
    for (int i = 0; i < loop; i++)
    {
     SonarSensor();
     if(FrontSensor != 0){
     front = FrontSensor;
     Serial.println(front);
     frontLoop += front;
     j++;
     }
    }
     front = frontLoop/j;
    
    Serial.print("front length is ");
    Serial.println(front);
    motor.Right();
    delay(/*4000*/2200/*2800*/);
    motor.MotorOut();
    delay(500);
    start = false;
    delay(500);    
    secondStart = true;     
    break;
  }}
}

void UltraSonic::MeasureBack()
{
  if(secondStart == true)
  {
  while(FrontSensor != 0){
    for (int i = 0; i < loop; i++)
    {
     SonarSensor();
     if(FrontSensor != 0){
     back = FrontSensor;
     Serial.println(back);
     backLoop += back;
     f++;
     }
    }
    back = backLoop/f;
    Serial.print("back length is ");
    Serial.println(back);
    start = false;
    secondStart = false;
    thirdStart = true;
    break;
  } }
}

void UltraSonic::MeasureLength()
{
  if(thirdStart == true)
  {
    totalLength = front + back + LengthRobot ;
    Serial.print("Lengte van de bak is ");
    Serial.println(totalLength);
    thirdStart = false;
    centerPoint = totalLength / 2;
  }
  }

void UltraSonic::GoToCoordinate()
{
    if(FrontSensor != 0)
    {
      Front = FrontSensor;
    }
    if(LeftSensor != 0)
    {
      Left = LeftSensor;
    }

    
    if (RiFlag == true)
    {
      motor.Right();
      Serial.print("robot gaat naar rechts");
      Serial.println(LeftSensor);
      delay(1800);
      motor.MotorOut();
      RiFlag = false;
      searchY = false;
      searchX = true;
    }

    if(LeFlag == true)
    {
      motor.Left();
      Serial.print("robot gaat naar links");
      Serial.println(LeftSensor);
      delay(1800);
      motor.MotorOut();
      motor.LedOn();
      LeFlag = false;
      searchY = false;
      searchX = true;
    }

     if(goForward == true)
      {
        motor.Forward();
        delay(50);
        Serial.print("vooruit");
        Serial.println(Front);
        goForward = false;
      }

      if(goBack== true)
      {
        motor.Reverse();
        delay(50);
        Serial.print("achteruit");
        Serial.println(Front);
        goBack = false;
      }
    

    if(searchY == true)
    {
      //ga naar y = 20
      if(Front > 20 && Front != 0)
      {
          goForward = true;
      }
      else if(Front < 20 && Front != 0)
      {
          goBack = true;
      }
      else if(Front == 20 && Front != 0)
      {
          motor.MotorOut();
        //draai naar de juiste richting
          if(LeftSensor < centerPoint && LeftSensor !=0 )
          {
            RiFlag = true;
          }   
          else if(LeftSensor > centerPoint && LeftSensor != 0)
          {
              LeFlag = true;
          }
      }
      }

    

    if(searchX == true)
    {
      //ga naar x = 30
      if(Front > 30 && Front != 0)
      {
          goForward = true;
      }
      else if (Front < 30 && Front != 0)
      {
         goBack = true;
      }
      else if (Front == 30)
      {
          motor.MotorOut();
          searchX = false;
          Serial.println("Robot bevindt zich op de positie (30, 20)");
      }
    }
    
    
    
}



//}


