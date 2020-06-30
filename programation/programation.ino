#include <LiquidCrystal.h>
//entradas
#define potenciometro  1 //A1
#define cruce_x_0      2 //D2
//salidas 
#define disparo1       6  //D6
#define disparo2       7  //D7
#define frec_1         5  //D5
#define frec_2         13
#define rx             0   //pin entrada para comunicacion bluetooth

int  tiempo=0;
int  bandera1=0;
int  bandera2=0;
int  contador=0;
char  c;
int var=0;
int numero;

String readString="";
LiquidCrystal lcd(12, 11, 10, 9, 8, 4); 

void interrupcion()  //LOS CRUCES POR CERO SON TOMADOS POR MEDIO DE UNA INTERRUPCION
{
  digitalWrite(frec_1, !digitalRead(frec_1));
 if(bandera2==0)
  {
  bandera1=1;
  contador++;
  }
    
  if(contador==60)
  {
     digitalWrite(frec_2, !digitalRead(frec_2));
     contador=0;    
  }
 
}
void setup()
{
   pinMode(disparo1,OUTPUT);
   pinMode(disparo2,OUTPUT);
   pinMode(frec_1,OUTPUT);
   pinMode(frec_2,OUTPUT);
   attachInterrupt(digitalPinToInterrupt(cruce_x_0), interrupcion, FALLING); //SE HABILITA LA INTERRUPCION POR EL PIN D2
   Serial.begin(115200);
   lcd.begin(16, 2);
   lcd.print("Valor Promedio:");
}

long k,l;
void loop()
{
  if(bandera1==1 )  //SE USA UNA BANDERA PARA SABER EN QUE MOMENTO SE HIZO UN CRUCE POR CERO
  {                 //SERVIRA COMO SINCRONISMO PARA DISPARO 
    delayMicroseconds(tiempo);
    digitalWrite(disparo1,HIGH);   //SE DISPARA POR ESTOS PINES A LOS SCR
    digitalWrite(disparo2,HIGH);
    delayMicroseconds(25);
    digitalWrite(disparo1,LOW);
    digitalWrite(disparo2,LOW);
     bandera1=0;    //SE PONE  A 0 LA BANDERA HASTA QUE OCURRA OTRO CRUCE POR CERO
    pantalla_lcd();
  }
 // int v=analogRead(2);
 //Serial.println(v);
lectura_analogica();  //POR MEDIO DE ESTA FUNCION SE HACE LA LECTURA DE UN POTENCIOMETRO
}                     //ESTO PARA CONTROLAR LA VELOCIDAD DEL MOTOR DC


void pantalla_lcd() //SE USA PANTALLA LCD PARA MOSTRAR EL VOLTAJE PROMOEDIO DC
{
   l++;
    if(l==100 )
    {
      bandera2=1;
     lcd.clear();
     lcd.setCursor(0, 0);
      lcd.print("voltaje Promedio");
      
    digitalWrite(disparo1,LOW);
    digitalWrite(disparo2,LOW);
      lcd.setCursor(0, 1);
      lcd.print(26-(tiempo*0.0035286));
      lcd.setCursor(7, 1);
      lcd.print("Vcd");
      contador=0;
      bandera2=0; 
      l=0;
    }
}

void lectura_analogica()
{
  k++;
    if(k==20)
    {  
       int tiempo_v=analogRead(potenciometro);
       delayMicroseconds(20);
       tiempo=int(tiempo_v*7
       );
      // Serial.println(tiempo);
       k=0;
    }
} 
