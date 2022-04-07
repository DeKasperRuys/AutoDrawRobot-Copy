
#ifndef CoordMovement_h
#define CoordMovement_h
#include "Arduino.h"

class CoordMovement
{
private:

public:
int xCoord=0;
int yCoord=0;
int teller =0;
int xNext =0;
int yNext=0;
int myXCoords[9] = {0,2,3,4,5,4,3,2,3};
int myYCoords[9] = {5,5,5,5,5,5,5,5,5};
int compass = 360;

void turnDirection();
void setNextCoord();
void info();
};


#endif



