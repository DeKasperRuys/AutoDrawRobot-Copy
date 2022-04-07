#include "NineDof.h"


void NineDof::Init(){
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;

  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                  "work for an out of the box LSM9DS1 " \
                  "Breakout, but may need to be modified " \
                  "if the board jumpers are.");
    while (1);
  }
 }

 void NineDof::loopPart(){
 // Update the sensor values whenever new data is available

  if ( imu.gyroAvailable() )
  {
    imu.readGyro();
  }
   if ((lastPrint + PRINT_SPEED) < millis())
  {

    printGyro(); // // Print "G: gx, gy, gz"
    //degreeCalc(); //Calculate degrees of 2 points with XY coords.
    lastPrint = millis(); // Update lastPrint time
  }
  
 }


 void NineDof::printGyro()
{
    turnDeg = abs(imu.calcGyro(imu.gz));

          
          if (anglecalc == true){
          degreeCalc();
          }

         if ( degTotaal < angle )//fullTurns[teller]) //foutmarge 5 graden per 90   0.0555555555555556 per graden
         {
              if ( turnDeg > 0.5 )
              {
                  degTotaal += (turnDeg -0.11)*0.050; // //graden maal seconden
          
              }
              else
              {
                  
                  degTotaal += 0;
              }
        }
        else 
        {
          // if (teller < sizeof(fullTurns)/sizeof(*fullTurns))
          // {
          //   teller ++;
          // }

          OnOrOff = 0;
          Serial.println("Triggered angle bereikt");
          Serial.println("State bereikt: ");
          Serial.print(motor.state);
          degTotaal = 0;
        }

          Serial.print("G: ");
          Serial.println(turnDeg);
          Serial.println(" deg/s");
          Serial.println(degTotaal);
    }

void NineDof::readSensors(){
  //Reads out the Gyro sensor for heading calculations
  if ( imu.gyroAvailable() )
  {
    // To read from the gyroscope,  first call the
    // readGyro() function. When it exits, it'll update the
    // gx, gy, and gz variables with the most current data.
    imu.readGyro();
  }
}

 void NineDof::degreeCalc(){
//XCOORD & YCOORD ZIJN DE PUNTEN DIE BLUETOOTH DOORSTUURT
// DEZE WAARDES ZIJN NORMAAL :   KOMMAGETAL * 240(baklengte)
rico = (Ycoords[0] - Ycoords[1])/(Xcoords[0]-Xcoords[1]);

 float angle = abs((atan (rico)*180/3.14)-(atan (rico)*180/3.14)*0.05555);

 Serial.println(angle);
 
 if(Xcoords[0]<Xcoords[1] && Ycoords[0]<Ycoords[1]){
   //IN DIT GEVAL MOET DE ROBOT NAAR RECHTS DRAAIEN MET HET
   //TEGENOVERGESTELDE VAN DE ANGLE
  angle = 85-angle;
 
  
  Serial.println(angle);
  Serial.print(" naar RECHTS");
  left = false;
  compass+=85-angle;
 }
 else if(Xcoords[0]>Xcoords[1] && Ycoords[0]>Ycoords[1]){
 //IN DIT GEVAL MOET DE ROBOT NAAR LINKS DRAAIEN MET DE
   //ANGLE + 90 GRADEN ALS WE ERVAN UITGAAN DAT ROBOT ALTIJD TERUG NAAR
   // NOORDEN KIJKT
   angle+=85;/*normaal 90, maar foutmarge was 5graden*/

  Serial.println(angle);
  Serial.print(" naar LINKS");
  left = true;
  compass-=angle+85;
 }
 else if(Xcoords[0]<Xcoords[1] && Ycoords[0]>Ycoords[1]){
   //IN DIT GEVAL MOET DE ROBOT NAAR RECHTS DRAAIEN MET DE
   //ANGLE + 90 GRADEN ALS WE ERVAN UITGAAN DAT ROBOT ALTIJD TERUG NAAR
   // NOORDEN KIJKT
   angle +=85;
  

  Serial.println(angle);
  Serial.print(" naar RECHTS");
  left = false;
  compass+=85;
 }
 else if(Xcoords[0]>Xcoords[1] && Ycoords[0]<Ycoords[1]){
   //IN DIT GEVAL MOET DE ROBOT NAAR LINKS DRAAIEN MET HET
   //TEGENOVERGESTELDE VAN DE ANGLE
  angle = 85-angle;

  Serial.println(angle);
  Serial.print(" naar LINKS");
  left = true;
  compass-=85+angle;
 }
 }