#include <Arduino.h>


volatile bool pressed = false;

void IRAM_ATTR isr() {
  pressed=true;
}
void setup() {
  Serial.begin(115200);
  pinMode(18, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(19, OUTPUT);
  digitalWrite(19,LOW);
  digitalWrite(3, LOW);
  digitalWrite(18,LOW);

  pinMode(0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(0), isr, RISING);
}

void loop() {

  if(pressed==true){
    Serial.println("HALLO WORLDDD");
    digitalWrite(19, !digitalRead(19));
    digitalWrite(3,  !digitalRead(3));
    digitalWrite(18, !digitalRead(18));
    pressed=false;
  }
  
}

