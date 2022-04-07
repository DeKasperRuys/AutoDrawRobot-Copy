#ifndef Coordinaat_h
#define Coordinaat_h

#include <WString.h>

class Coordinaat
{
private:
    /* data */
     float x;
     float y;
     int strength;
public:
    Coordinaat( String _x,  String _y,  String _strength );
    Coordinaat(float _x, float _y, float _strength );
    Coordinaat();

    float GetX();
    float GetY();
    int GetStrength();

    void SetX(float _x);
    void SetX(String _x );
    void SetY(float _y);
    void SetY(String _y);
    void SetStrength(int _strength);
    void SetStrength(String _strength);

    

};

#endif