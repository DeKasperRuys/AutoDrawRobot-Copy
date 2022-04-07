#ifndef UltraSonic_h
#define UltraSonic_h
#include "Arduino.h"
#include "Bluetooth/Bluetooth.h"
#include "Motor/Motor.h"

class UltraSonic
{
private:
  
public:
    UltraSonic(int trigL, int echoL, int trigF, int echoF);
    //Variables
    int trigPinL;
    int echoPinL;
    int trigPinF;
    int echoPinF;
    int rotation = 0;
    int nextY;
    int nextX;
    int currentY;
    int currentX;
    char data;
    int gyroOrientation = 45;
    bool Fflag = true;
    bool Lflag = false;
    bool Cflag = false;
    bool RiFlag = false;
    bool LeFlag = false;
    bool goToCenter = true;
    bool frontCenter = false;
    bool searchX = false;
    bool goForward;
    bool goBack;
    bool searchY = true;
    int centerPoint = 105;
    int Front, Left;
    bool start,secondStart,thirdStart = false;
    int front, frontLoop, backLoop, back;
    int loop = 20;
    int totalLength;
    int j,f = 0;
    int x, y;

    Motor motor;

    int collision;
    int INTERVAL_MESSAGE_1 = 50;
    int INTERVAL_MESSAGE_2 = 150;
    int INTERVAL_MESSAGE_3 = 1070;
    int MaxRange = 244;
    int MinRange = 15;
    int Length = 244;
    int LengthRobot = 55;
    int WidthRobot = 11;
    unsigned long time_1,time_2,time_3,time_4, time_5 = 0;
    long duration, distance, duration2, distance2, FrontSensor, LeftSensor;
    bool sensor;

    //Methods
    void ObstacleDetector();
    void Init();
    void PrintTime(unsigned long time_millis);
    void PositionTracker();
    void SendData();
    void SonarSensor();
    void Collision();
    void GetPosition();
    void TrackCenter();
    void GoToCenterReverse();
    void GoToCenterForward();
    void MeasureLength();
    void MeasureFront();
    void MeasureBack();
    void GoToCoordinate();

};
#endif
