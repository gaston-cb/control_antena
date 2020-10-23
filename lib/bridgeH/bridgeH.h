class bridgeH
{
private:
    char _pin1 ; 
    char _pin2 ; 
    char _state_bridge ;    //two caracter 00,01,10,11 
    char p1 ;               // 00 
    char p2 ;               // move h to az or move west - est 
    char p3 ;               // move inverse p2 
    char p4 ;               // 11 
public:
       bridgeH(char pin1 , char pin2);
    
    void setPS(char pmax) ; 
    void moveS1();  // move h to az or west - est 
    void moveS2();  // move inverse s1 
    void parkAnt() ; //stop the antenna  

};

