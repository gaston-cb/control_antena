#include <Arduino.h>
#include <Ethernet.h> 



/*---------Puertos PWM 1-------------------*/
#define PWM11 9   
#define PWM12 10  
/*---------Puertos PWM 2 ------------------*/
#define PWM21 5   
#define PWM22 6  

// Definicion de pines Azimuth y declinacion 
#define AZIMUTH A1      // pin analogico para azimuth 
#define DECLINACION A0  // pin analogico para declinacion  
// fin definicion lectura de pines -- 
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
EthernetServer Gpredict_rotator(4532) ;// socket tcp/ip para Gpredict 
EthernetServer stelarium(10001) ;      // socket tcp/ip para stelarium 
// fin definicion de servidores 




void setup() {
  Serial.begin(9600) ; 
  digitalWrite(8,HIGH) ; 
  byte mac [] = {0x00, 0xCD, 0xEF, 0xEE, 0xAA, 0xBC}; // dirmac
  Ethernet.init(4); 
  delay(250) ; 
  if (Ethernet.begin(mac) == 0)
  {
    
   Serial.print(F("Fallo DHCP"));
    
  } else {
    Serial.print(Ethernet.localIP());
  }

}

void loop() {
  // put your main code here, to run repeatedly:
}