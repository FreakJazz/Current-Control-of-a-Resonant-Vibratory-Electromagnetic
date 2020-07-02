#include <LiquidCrystal.h>
//entradas
#define pot  A1 //A1
#define cero_cross    2 //D2
//salidas 
#define trigger       6  //trigger of SCR
#define trigger2      7  //D7                                                                                                                       
#define frec_1        5  //D5
#define frec_2        13

int  time1 = 0;
int  flag1 = 1;
int  flag2 = 0;
int  count = 0;
char  c;
int var = 0;
int number;
long k,l;

String readString = "";
LiquidCrystal lcd(12, 11, 10, 9, 8, 4); 

void interrupt()  //zero-cross interrupt detected
  flag1=1;
  count++;
  digitalWrite(frec_1, !digitalRead(frec_1));
 if(flag2==0)
  {
  flag1=1;
  count++;
  }
    
  if(count==60)
  {
     digitalWrite(frec_2, !digitalRead(frec_2));
     count=0;    
  }
 
}
void setup()
{
   //Configuration pins of system
   pinMode(trigger,OUTPUT);
   pinMode(trigger2,OUTPUT);
   pinMode(frec_1,OUTPUT);
   pinMode(frec_2,OUTPUT);  
   attachInterrupt(digitalPinToInterrupt(cero_cross), interrupt, FALLING); //SE HABILITA LA INTERRUPCION POR EL PIN D2
   Serial.begin(115200);
  
}

void loop()
{
  if(flag1==1 )  //flag is 1 if the zero-cross is active
  {                 //and send the trigger 
    delayMicroseconds(time1);
    digitalWrite(trigger,HIGH);   //ON TRIGGER
    //digitalWrite(trigger2,HIGH);   //ON TRIGGER
    delayMicroseconds(time1);
    digitalWrite(trigger,LOW);
    //digitalWrite(trigger2,LOW);
    //delayMicroseconds(25);
    flag1=0;    //the flag is off
    l++;
    if(l==100 ){
      //digitalWrite(trigger,LOW);   //ON TRIGGER
      //digitalWrite(trigger2,LOW);
      count=0;
      flag2=0; 
      l=0;
      lectura_analogica();
    }
  }
 // int v=analogRead(2);
 //Serial.println(v);
}            

void lectura_analogica()
{
  k++;
    if(k==20)
    {  
       int tiempo_v=analogRead(pot);
       delayMicroseconds(20);
       time1=int(tiempo_v*7
       );
      // Serial.println(tiempo);
       k=0;
    }
} 


