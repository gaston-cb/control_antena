#include <Arduino.h> 
#include "bridgeH.h" 

bridgeH::bridgeH(char pin1 , char pin2)
{
    _pin1 = pin1 ; 
    _pin2 = pin2 ;
    pinMode(pin1 , OUTPUT) ; 
    pinMode(pin2 , OUTPUT) ; 
        
}



void bridgeH::setPS(char pmax) 
{
    //SET P2 Y P3 
    if (pmax ==0)
    {
      p2 = 10 ;
      p3 = 01 ; 
    }else if(pmax == 1)
    {
      p3 = 10 ; 
      p2 = 01 ; 
    }


} 

void bridgeH::moveS1() 
{
   digitalWrite(_pin1,HIGH) ; 
   digitalWrite(_pin2,LOW) ; 
   _state_bridge = 10 ;  
    
}
void bridgeH::moveS2()
{
   digitalWrite(_pin1,LOW) ; 
   digitalWrite(_pin2,HIGH) ; 
   _state_bridge = 01 ;  

}

void bridgeH::parkAnt()
{
   digitalWrite(_pin1,LOW) ; 
   digitalWrite(_pin2,LOW) ;  
   _state_bridge = 00 ;  
     
}


void bridgeH::getPs()
{
   Serial.print("posiciones: ") ; 
   Serial.println(p1,DEC) ;Serial.print("  ") ; 
   Serial.print(p2,DEC) ; 
} 