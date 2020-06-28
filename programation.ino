//#include <Arduino.h>

// Half wave controlled rectifier with Arduino (SCR controller with Arduino)
 
#define scr_trig  8
#define pot       A0
 
bool ZC = 0;
uint16_t alpha;


void setup(void) {
  pinMode(scr_trig, OUTPUT);
  digitalWrite(scr_trig, LOW);
  attachInterrupt(0, ZC_detect, FALLING);       // Enable external interrupt (INT0)
}
 
void loop() {
  if(ZC){
    delayMicroseconds(alpha);
    digitalWrite(scr_trig, HIGH);
    delay(1);
    digitalWrite(scr_trig, LOW);
    ZC = 0;
    alpha = analogRead(pot) * 10;
    if(alpha > 10000)
      alpha = 10000;
  }
  
  }

void ZC_detect() {
  ZC = 1;
}
