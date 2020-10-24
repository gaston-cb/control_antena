#include <Arduino.h>
#include <configTCPportsandOutput.h> 
#include "calib_control_antenna.h" 

extern bridgeH bridge_az ; 
extern bridgeH bridge_H ; 
int calAz[2]= {0,0};   
int calH[2] = {0,0}; 



bool calibrate(char i)
{
    int r1 = analogRead(LECTAZ) ; // LECTURA DE AZIMUTH 
    int r2 = analogRead(LECTH)  ; // LECTURA DE ALTURA 
    delay(1000); // espera de un segundo ; 
    int l3 = analogRead(LECTAZ) ; // 87microsegundos  
    int l4 = analogRead(LECTH) ; 
    Serial.print("az=") ; Serial.print(r1); Serial.print("  ") ; Serial.println(l3) ; 
    Serial.print("z=") ; Serial.print(r2); Serial.print("  ") ; Serial.println(l4) ; 
    // revisar si llego al maximo o minimo ; 
    char f1 = 5 ; char f2 = 5 ; //variables centinela 
    if (r1 == l3)
    {
        f1 = 0 ; 
        calAz[i] = l3 ; 
    }
    
    if (r2 == l4)
    {
        f2 = 0 ;  
        calH[i] = l4 ; 
    }
    //si esta calibrado ambas son cero  
    if (f1==0 && f2==0)
    {
        return false ; 
    }
    
    return true; 
} 

void ConfSentidoGiro(){
    /*
     * detecta el maximo y guarda la configuracion en p1 y p2 de calibrado
     * clase bridgeH 
    */
    if (calAz[0]>calAz[1])
    {
       int aux =calAz[0] ; 
       calAz[0] = calAz[1]  ; 
       calAz[1] = aux ; 
       bridge_az.setPS(0) ; 
    }else
    {
       bridge_az.setPS(1) ; 
    }
    if (calH[0]>calH[1])
    {
        int aux =calH[0] ; 
        calH[0] = calH[1]  ; 
        calH[1] = aux ; 
        bridge_H.setPS(0) ; 
    }else 
    {
        //calH[0]<calH[1] ; 
        bridge_H.setPS(1) ;
    }

}

/*
    * r1 = referencia de AZIMUTH
    * r2 = referencia de altura 
*/
bool control_error(int r1,int r2)
{
    
    int res_Az = 100*((180.0/(calAz[1] - calAz[0]))+0.005);  ; 
    int res_H = 100*((90.0/(calH[1] - calH[0]))+0.005); 
    int posH = (analogRead(LECTH)*90.0/calH[1])*100; 
    int posAz = (res_Az*(analogRead(LECTAZ)-calAz[0])); 
    
    
    int errorH  = r2 -  (analogRead(LECTH)*90.0/calH[1])*100;         // (res_H*(analogRead(LECTH) - calH[0])); 
    int errorAz = r1-(res_Az*(analogRead(LECTAZ)-calAz[0]));; 

    /*
    *
    * error H > 0 ---> sentido H a Z  
    * error H <0  ---> sentido Z a H 
    * error Azimuth <0   --->  sentido 
    * error Azimuith >0  --->  sentido 
    * 
    */
    
    Serial.print("error en ALTURA") ; 
    Serial.println(errorH) ; 
    Serial.print("Error en Azimuth") ; 
    Serial.println(errorAz) ; 
    Serial.print("resAz: ");Serial.println(res_Az); 
    Serial.print("Res_H: ") ; Serial.print(res_H) ; 
    Serial.print("POSH:  ") ; Serial.println(posH) ; 
    Serial.print("az: ") ; Serial.println(posAz) ; 
    
    
    if (abs(errorH)<res_H)
    {
        Serial.println("stop ") ; 
        return false ; 
        //park Antena 
    }else if (errorH > res_H)
    {
        //move H to Z 
        Serial.print("error positivo") ; 
        return true  ; 
        
    }else if (errorH< - res_H)
    {
         //move Z to H 
         Serial.print("error negativo") ; 
        return true ;   
    }



}
