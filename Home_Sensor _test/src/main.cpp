#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#include <U8g2lib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 1
#define OLED_SCL 2
#define OLED_ADDR 0x3C   // meistens 0x3C

//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
volatile bool pressed = false;
bool displayOn = false;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
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
  Wire.begin(1, 2);

  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}

void loop() {

  if(pressed==true){
    Serial.println("HALLO WORLDDD");
    digitalWrite(19, !digitalRead(19));
    digitalWrite(3,  !digitalRead(3));
    digitalWrite(18, !digitalRead(18));
    pressed=false;


    displayOn = !displayOn;
    u8g2.clearBuffer();
    if (displayOn) {
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(10, 30, "Hallo Karola");
    }
    u8g2.sendBuffer(); 
  }
  
}

