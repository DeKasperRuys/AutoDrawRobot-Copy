#include "CoordMovement.h"

void CoordMovement::turnDirection(){

//Move on Y-AXIS
do
{
    
    if(compass != 180 && yNext>yCoord) // 
{
  compass =180; //TURN ROBOT TO LOOK SOUTH
    Serial.println("Looking south");
    //info();
}
if(compass != 0 && yNext<yCoord) //
{
  compass =0; //TURN ROBOT TO LOOK NORTH
   Serial.println("Looking north");
  // info();
}

//Bekijk de Y as met hoogste getal links boven
  if(compass == 0 && yCoord > yNext ){
  Serial.println("MOVING north");
  yCoord--; //  MOVE ROBOT FORWARD SO IT MOVES UP ON Y-AXIS
  info();
}

if(compass == 180 && yCoord < yNext){
    Serial.println("MOVING south");
  yCoord++; //  MOVE ROBOT FORWARD SO IT MOVE DOWN ON X-AXIS
  info();
}


} while (yCoord != yNext);


//MOVE ON X-AXIS
do{


   //TURN ROBOT TO CORRECT WAY
if(compass != 270 && xNext<xCoord ) //
{
  compass =270; //TURN ROBOT TO LOOK WEST
    Serial.println("Looking west");
   // info();
}
if(compass != 90 && xNext>xCoord) //
{
  compass = 90; //TURN ROBOT TO LOOK EAST
  Serial.println("Looking east");
 // info();
}

if(compass == 90 && xCoord < xNext ){
  Serial.println("MOVING east");
  xCoord++; //  MOVE ROBOT FORWARD SO IT UP DOWN ON Y-AXIS
  info();
}

if(compass == 270 && xCoord > xNext ){
  Serial.println("MOVING west");
  xCoord--; //  MOVE ROBOT FORWARD SO IT MOVE DOWN ON X-AXIS
  info();
}
}while(xCoord!=xNext);


teller++;
if(teller>= 9){
  teller = 0;
}  

}

void CoordMovement::setNextCoord(){

xNext = myXCoords[teller];
yNext = myYCoords[teller];
if (compass >= 360)
{
    compass = 0;
    
    Serial.println("Compass set to 0 degree");
}


}

void CoordMovement::info(){
  Serial.print("X =     ");
  Serial.print(xCoord);
  Serial.print(" , Y =        ");
  Serial.println(yCoord);
  Serial.print("xNext = ");
  Serial.print(xNext);
  Serial.print(" , yNext, Y = ");
  Serial.println(yNext);
}









