#include "BluetoothModule.h"

BluetoothModule::BluetoothModule(int rxPin, int txPin):BT(SoftwareSerial(rxPin,txPin))
{
    BT.begin(9600);
    code = NO_CONTENT;
}
void BluetoothModule::Send(int data)
{
    BT.print(data);
}
void BluetoothModule::Send(char data)
{
    BT.print(data);
}
void BluetoothModule::SetCoordinaten(char data)
{
    coordinaten = data;
    if (coordinaten != NULL) {
        code = ACCEPTED;
    }
    else
    {
        code = NO_CONTENT;
    }
    
    
}

char BluetoothModule::GetCoordinaten()
{
    return coordinaten;
}

int BluetoothModule::GetCode()
{
    return code;
}
