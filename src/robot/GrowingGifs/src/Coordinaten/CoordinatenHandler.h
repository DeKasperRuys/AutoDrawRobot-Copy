#ifndef CoordinatenHandler_h
#define CoordinatenHandler_h
#include "./Bluetooth/Bluetooth.h"
#include "Coordinaat.h"

class CoordinatenHandler
{
private:
    Bluetooth bt;
    double aantal;
    Coordinaat* coordinaten;
    int state;
    int currentPosition;
    Coordinaat* addCoordinaten(String coordinaten);
    Coordinaat splitCoordinaat(String s);
    bool available;

public:
    static const int FINISHMOVING = 100; //Naar alle coordinaten geweest
    static const int REQUEST = 201; // Request for next part
    const int OK = 200; //Gedaan met ontvangen van 1 part
    const int ACCEPTED = 202; // Ontvangen van coordinaten
    const int CONTINUE = 100; // Er zijn nog coodinaten moeten sturen;
    const int NO_CONTENT = 204; // GEEN COORDINATEN
    const int DONE = 203; // Geen coordinaten meer
    const int COUNT = 210; ////eind met 210 betekent deze message is aantal
    const int RESET = 205; // Reset gestuurde coordinaten, zal opnieuw beginnen
    const int WRONG = 400; // het aantal van verzonden coordianten klopt niet met het aantal van ontvangen coordinaten
    
   static const int ASK_AANTAL = 1; // wacht op aantal
   static const int READING = 2; // reading coordinaten
   static const int PAUZE = 3; //even op pauze, want de robot is aan het bewegen

    CoordinatenHandler(int rxPin, int txPin);
    void Run();
    void sendRequest(); //Als de robot naar alle coordinaten is geweest dan sendRequest();

    bool Available();    ////True -> je kan nu coordinaten gebruiken
    double getAantal(); //aantal coordinaten in de array Coordinaten;
};




#endif