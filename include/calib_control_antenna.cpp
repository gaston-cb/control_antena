#include <Arduino.h>
#include <configTCPportsandOutput.h> 
#include "calib_control_antenna.h" 

/*
int calAz[2]= {0,0};   
int calH[2] = {0,0}; 
*/


bool calibrate()
{
    int r1 = analogRead(LECTAZ) ; // LECTURA DE AZIMUTH 
    int r2 = analogRead(LECTH) ; // LECTURA DE ALTURA 
    return true ; 
} 

void helloword()
{
    Serial.println("olaaa!") ; 
}