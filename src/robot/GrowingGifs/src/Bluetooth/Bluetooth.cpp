#include "Bluetooth.h"

Bluetooth::Bluetooth(int rxPin, int txPin):BT(SoftwareSerial(rxPin,txPin))
{
    BT.begin(9600);
    state = NO_CONTENT;
    heeftAlleCoordinaten = false;
    
}

void Bluetooth::Send(int data)
{
    BT.print(data);
}

void Bluetooth::Send(char data)
{
    BT.print(data);
}

void Bluetooth::SetCoordinaten(String data)
{   
    coordinaten = data;
    if (coordinaten != NULL) {
        state = ACCEPTED;
    }
    else
    {
        state = NO_CONTENT;
    }
      
}

String Bluetooth::GetCoordinaten()
{
    return (coordinaten);
}

int Bluetooth::GetState()
{
    return state;
}

void Bluetooth::Receive()
{
    c = NULL;
    s = String(c);

    availble = false;
    while(BT.available() > 0){

        c = BT.read();
        s = String(s+c);

        if (s.endsWith("200")) 
        {
            availble = true;
            SetCoordinaten(s);
        }
        if (s.toInt() >= 0 && s.toInt() <11) {
            availble = true;
            motorState = s.toInt();
        }
        
    }
}

void Bluetooth::Request()
{
    if (state == REQUEST) {      
        Send(REQUEST);
        Receive();
    }
    
}

bool Bluetooth::Availble()
{
    return availble;
}

void Bluetooth::SetState(int code)
{
    switch (code)
    {
        case 200 :
            state = OK;
            break;
        case 201:
            state = REQUEST;
            break;
        case 202:
            state = ACCEPTED;
            break;
        case 203:
            state = DONE;
            break;
        case 204: 
            state = NO_CONTENT;
        case 100:
            state = CONTINUE;
    }
}

int Bluetooth::GetMotorState()
{
    return motorState;
}

String Bluetooth::getData()
{
    return data;
}

void Bluetooth::ResetData()
{
    data = "";
}
void Bluetooth::Read()
{
    c = NULL;
    s = String(c);

    availble = false;
    while(BT.available() > 0){

        c = BT.read();
        s = String(s+c);

        data = s;
    }
}


