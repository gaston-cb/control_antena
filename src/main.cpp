#include <Arduino.h>
#include <Ethernet.h> 
#include <LiquidCrystal_I2C.h> 
#include <configTCPportsandOutput.h> 
#include <bridgeH.h>
#include <calib_control_antenna.cpp> 



LiquidCrystal_I2C lcd(0x3F, 16, 2); 

bridgeH bridge_az (PWM11,PWM12)  ; 
bridgeH bridge_H (PWM21,PWM22)  ; 


/*variables config */
char state_con = 0 ;  // state_con = 0 -- no conectado a Gpredict -- state_con = 1 conectado a Gpredict 
int gpredict_azimuth = 0 ; 
int gpredict_declinacion = 0 ; 
unsigned long int RA12HS = 0x80000000  ; 
extern char state_bridgeH[4];

int azimuth_act = 0  ;
int declinacion_act = 0  ;
// fin  config  

//Definicion de servidores y puertos 
EthernetServer Gpredict_rotator(PORTGPREDICT) ;// socket tcp/ip para Gpredict 
EthernetServer stelarium(PORTSTELARIUM) ;      // socket tcp/ip para stelarium 
// fin definicion de servidores 




void setup() {
  lcd.init() ;
  lcd.backlight();
  lcd.clear() ;
  lcd.print(F("calibrando")) ; 
  lcd.setCursor(0,1); 
  lcd.print(F("antena")); 
  bridge_az.moveS1() ; 
  bridge_H.moveS1() ; 
  //FUNCION DE CALUBRACION 
  helloword() ; 
//  calibrate() ; 
  delay(500) ; 
  bridge_az.moveS2() ; 
  bridge_H.moveS2() ; 
  //while (calibrate()){} ;

  
  

  






}

void loop() {
  // put your main code here, to run repeatedly:
}