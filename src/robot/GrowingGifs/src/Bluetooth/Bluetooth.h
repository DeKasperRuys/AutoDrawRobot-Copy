#ifndef Bluetooth_h
#define Bluetooth_h
#include "Arduino.h"
#include <SoftwareSerial.h>
#include <WString.h>

class Bluetooth
{
private:
    SoftwareSerial BT;
    String coordinaten;
    int state;
    bool heeftAlleCoordinaten;
    bool availble;
    char c; //gebruik bij BT.read();
    String s; //gebruik bij BT.read();
    int motorState;
    String data;
public:
    const int OK = 200; //Gedaan met ontvangen van 1 part
    const int ACCEPTED = 202; // Ontvangen van coordinaten
    const int CONTINUE = 100; // Er zijn nog coodinaten moeten sturen;
    const int NO_CONTENT = 204; // GEEN COORDINATEN
    const int REQUEST = 201; // Request for next part
    const int DONE = 203; // Geen coordinaten meer

    Bluetooth(int rxPin, int txPin);
    void Send(int data); // verzend een int van Arduino naar mobile
    void Send(char data); // verzend een char van Arduino naar mobile
    String GetCoordinaten(); 
    void SetCoordinaten(String data);
    int GetState();
    void SetState(int code);
    void Receive();  // Arduino ontvangt de data via bluetooth, data wordt in variable coordianaten gezet
    void Request();  // Vraag de coordinaten van volgende afbeelding, en wacht de data vanuit mobile, data wordt in variable coordianaten gezet
    bool Availble();
    int GetMotorState();
    String getData();
    void ResetData();
    void Read();


};

#endif