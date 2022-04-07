#include "Coordinaat.h"

Coordinaat::Coordinaat(String _x, String _y, String _strength)
{
    x = _x.toFloat();
    y = _y.toFloat();
    strength = _strength.toInt();
}

Coordinaat::Coordinaat(float _x, float _y, float _strength )
{
    x = _x;
    y = _y;
    strength = _strength;
}
Coordinaat::Coordinaat()
{
    
}

float Coordinaat::GetX()
{
    return x;
}

float Coordinaat::GetY()
{
    return y;
}

int Coordinaat::GetStrength()
{
    return strength;
}

void Coordinaat::SetX(float _x)
{
    x = _x;
}

void Coordinaat::SetX(String _x)
{
    x = _x.toFloat();
}

void Coordinaat::SetY(float _y)
{
    y = _y;
}

void Coordinaat::SetY(String _y)
{
    y = _y.toFloat();
}

void Coordinaat::SetStrength(int _strength)
{
    strength = _strength;
}

void Coordinaat::SetStrength(String _strength)
{
    strength = _strength.toInt();
}

