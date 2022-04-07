#include "CoordinatenHandler.h"

CoordinatenHandler::CoordinatenHandler(int rxPin, int txPin):bt(rxPin,txPin)
{
    state = 0; // no state;
    pinMode(LED_BUILTIN, OUTPUT);
}

void CoordinatenHandler::sendRequest()
{
   state = ASK_AANTAL;
}

Coordinaat CoordinatenHandler::splitCoordinaat(String s)
{
    // s = 0.2132132,0.321321321,10;

    String x,y,z;
    int index;
    //x
    index = s.indexOf(',');
    x = s.substring(0,index);
    z = s.substring(index+1);

    //y
    index = z.indexOf(',');
    y = z.substring(0,index);
    z = z.substring(index+1);

    //z
    index = z.indexOf(';');
    z = z.substring(0,index);

    // Serial.print("x = ");
    // Serial.println(x);
    // Serial.print("y = ");
    // Serial.println(y);
    // Serial.print("z = ");
    // Serial.println(z);

    return Coordinaat(x,y,z);
;
}

Coordinaat* CoordinatenHandler::addCoordinaten(String coordinaten)
{
    //coordinaten = 0.2132132,0.321321321,10;0.343324,0.3214525,10;
    //split coordinaten in verschillende coordinaten;
    int index = coordinaten.indexOf(';');
    Coordinaat* result;
    String coordinaat1 = coordinaten.substring(0,index); //0.2132132,0.321321321,10;
    String coordinaat2 = coordinaten.substring(index+1); //0.343324,0.3214525,10;
    if (coordinaat2.endsWith(";")) // als coordinaat2 niet leeg dan is 1 ook niet leeg;
    {
        result = new Coordinaat[2]{splitCoordinaat(coordinaat1), splitCoordinaat(coordinaat2)};
    // Serial.print("x0 = ");
    // Serial.println(result[0].GetX(),6);
    // Serial.print("y0 = ");
    // Serial.println(result[0].GetY(),6);
    // Serial.print("z0 = ");
    // Serial.println(result[0].GetStrength());
    // Serial.print("x1 = ");
    // Serial.println(result[1].GetX(),6);
    // Serial.print("y1 = ");
    // Serial.println(result[1].GetY(),6);
    // Serial.print("z1 = ");
    // Serial.println(result[1].GetStrength());
    }
    else
    {
        result = new Coordinaat[1]{splitCoordinaat(coordinaat1)};

    // Serial.print("x = ");
    // Serial.println(result[0].GetX(),6);
    // Serial.print("y = ");
    // Serial.println(result[0].GetY(),6);
    // Serial.print("z = ");
    // Serial.println(result[0].GetStrength());
    }

    return result;
    
}
bool CoordinatenHandler::Available()
{
    return available;
}

double CoordinatenHandler::getAantal()
{
    return aantal;
}

void CoordinatenHandler::Run()
{
    //Eerst wordt aantal gestuurd,
    //als CONTINUE is -> deze laag is gedaan, na REQUEST begint opnieuw
    
    if (aantal == 0)
    {
        state = ASK_AANTAL;
    }
    
    switch (state)
    {
    case 1:
    Serial.print("State = ");
    Serial.println(state);
    available = false;

    bt.Read();
    digitalWrite(LED_BUILTIN, HIGH); //High = wacht op reading

    if (bt.getData().endsWith(String(COUNT) ))
    {
            //Voorbereiden, init
            delete [] coordinaten;
            currentPosition = 0;

            aantal = bt.getData().toDouble();
            Serial.print("aantal = ");
            Serial.println(aantal);
            aantal = (aantal-210)/1000;
            Serial.print("na berekening = ");
            Serial.println(int(aantal));
            delay(1000);
            coordinaten = new Coordinaat[int(aantal)]; // init coordinaten
            bt.ResetData();
            state = READING; //Ga naar reading
            delay(100);
            digitalWrite(LED_BUILTIN, LOW); // low = aantal is binnengekregen, en moet naar case 2 READING gaan'
    }
    break;
    case 2:
   
        bt.Read();
        if (bt.getData() != "")
        {
            Serial.print("data = ");
            Serial.println(bt.getData());
            if (bt.getData() == String(DONE) ) //==203
            {
                state = PAUZE;
                break;
            }        

            Coordinaat* temp;
            temp = addCoordinaten(bt.getData()); // coordinaten toevoegen
            int size = 0;
            if (abs(temp[1].GetX()*1000) == 0) //in float, 0,313 kan soms niet gelijk zijn 0,313
            {
                Serial.println("size = 1");
                size = 1;
            }
            else
            {
                Serial.println("size = 2");
                size = 2;
            }
        
            if (size == 2)
            {
                for (int i = 0; i < 2; i++)
                {
                    coordinaten[currentPosition] = temp[i]; // voeg coordinaten toe
                    currentPosition++;
                }
            }
            else
            {
                coordinaten[currentPosition] = temp[0];
                currentPosition++;
            }
        }
        bt.ResetData();
        break;
    case 3: 
        // for (int i = 0; i < aantal ; i++)
        // {
        //     Serial.print("x = ");
        //     Serial.println(coordinaten[i].GetX(),6);
        //     Serial.print("y = ");
        //     Serial.println(coordinaten[i].GetY(),6);
        //     Serial.print("z = ");
        //     Serial.println(coordinaten[i].GetStrength());
        // }
        available = true;
        Serial.println("Robot is moving");
        break;
    case 4:
        //Robot is naar alle coordinaten zijn geweest
        break;
    default:
        break;
    }
    bt.Read();
    
}


