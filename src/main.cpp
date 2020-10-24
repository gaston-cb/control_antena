#include <Arduino.h>
#include <Ethernet.h> 
#include <LiquidCrystal_I2C.h> 
#include <configTCPportsandOutput.h> 
#include <bridgeH.h>
#include <calib_control_antenna.cpp> 
#include <tiempo.h>


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
  Serial.begin(9600) ;
  lcd.init() ;
  lcd.backlight();
  lcd.clear() ;
  lcd.print(F("calibrando")) ; 
  lcd.setCursor(0,1); 
  lcd.print(F("antena")); 
  bridge_az.moveS1() ; 
  bridge_H.moveS1() ; 
  Serial.println("olaaaaa!")  ;
  while(calibrate(0)){} ; 
  Serial.print("segunda_calibracion") ; 
  delay(500) ; 
  bridge_az.moveS2() ; 
  bridge_H.moveS2() ; 
  while (calibrate(1)){} ;
  ConfSentidoGiro() ; 
  bridge_H.getPs() ; 
  bridge_az.getPs() ; 
  while(control_error(9000,9000)){
    //Serial.print("WHILE") ; 
    delay(2000); 
  }

}

void loop() {
  timerEvent() ;
  long int dec ; 
  unsigned long int RA = 0 ; 
  uint8_t sunP[20] ;
  size_t cant = 20 ; 
  EthernetClient cliente = Gpredict_rotator.available() ;
  EthernetClient cliente_s = stelarium.available(); 
  if (cliente)
  { 
    while (cliente.connected())
    { 
      
      timerEvent() ;
      String cadena = "" ;      
      if (cliente.available())
      {
        //timerEvent() ;  
        char c = cliente.read()  ;   
        if (c == 'P')
        {
          
           cliente.print("RPRT 0") ; // lectura correcta 
           //Asignar_Azimuth_Declinacion(cliente,cadena) ;             
           cliente.flush() ;// VACIADO DE BUFFER 
           cadena ="" ;   
        }else if (c == 'p')
        {      
          //cadena = az_dec_pos_actual() ;       
          cliente.print(cadena);
          cliente.flush() ; 
          cadena ="" ;     
        }else if (c=='q' || c=='Q' )
        {                
          cliente.flush() ; 
          cliente.stop()  ;
          cadena ="" ; 
          break ;          
        }else if (c=='S')
        {
          cliente.flush() ;  
          cliente.stop() ;
          cadena = "" ; 
        } 
     }
  }
  cliente.stop() ; 
  delay(10) ; 
 }
 //stelarium_connection
 if (cliente_s)
 {  
   while (cliente_s.connected())
   {
    timerEvent() ; 
    
    char i = 0 ; 
    while (cliente_s.available())
    {
      //Serial.println(cliente_s.read(),HEX) ; 
      sunP[i] = cliente_s.read() ;  
      i = i + 1 ;          
      state_con = 1 ; 
    }
    if(state_con == 1)
    {
      dec = 0x00000000 | (long (sunP[19])<<24) | (long (sunP[18])<<16) | (long (sunP[17])<<8) | (long (sunP[16])<<0);
      RA  = 0x00000000 | (long (sunP[15])<<24) | (long (sunP[14])<<16) | (long (sunP[13])<<8) | (long (sunP[12])<<0);
      state_con = 0 ; 
      // declinacion en angulo 
      //ra en angulo 
//      RA12HS -- 12hs 
      unsigned long int hsra = (((RA*12.0)/RA12HS) * 10000)*15   ;
      float hsrf  = ((RA*12.0)/RA12HS)*15 ;      
      cliente_s.write(sunP,20) ;  
    }
     
   }
   cliente.stop() ; 
   delay(10) ; 
 }

}