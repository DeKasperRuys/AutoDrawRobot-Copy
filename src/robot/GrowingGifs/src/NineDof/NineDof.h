#ifndef NineDof_h
#define NineDof_h
#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include "Motor/Motor.h"
#include <TimerOne.h>

#define LSM9DS1_M	30
#define LSM9DS1_AG	107 
//#define PRINT_CALCULATED
#define PRINT_SPEED 50 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time
#define DECLINATION -1.42

class NineDof
{
private:
LSM9DS1 imu;   
public:
Motor motor;
float turnDeg;
float degTotaal = 0;
float fullTurns[5] = {90,90,90,90,90};
int teller;
int OnOrOff = 2;
float Xcoords[2] = {1,2};
float Ycoords[2] = {1,2};
float rico;
float angle;
bool left;
bool anglecalc = false;
int compass=0;

//methods
void Init();
void printGyro();
void degreeCalc();
void readSensors();
void loopPart();
void start();
void SensorOnorOff();
};






#endif