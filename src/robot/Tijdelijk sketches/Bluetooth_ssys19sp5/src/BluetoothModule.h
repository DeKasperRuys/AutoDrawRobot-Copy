#ifndef BluetoothModule_h
#define BluetoothModule_h
#include "Arduino.h"
#include <SoftwareSerial.h>

class BluetoothModule
{
private:
    SoftwareSerial BT;
    char coordinaten;
    int code;
public:
    const int OK = 200; //Gedaan met sturen van coodinaten
    const int ACCEPTED = 202; // Ontvangen van coordinaten
    const int CONTINUE = 100; // Er zijn nog coodinaten moeten sturen;
    const int NO_CONTENT = 204; // GEEN COORDINATEN
    BluetoothModule(int rxPin, int txPin);
    void Send(int data);
    void Send(char data);
    char GetCoordinaten();
    void SetCoordinaten(char data);
    int GetCode();

};

#endif