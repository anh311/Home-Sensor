#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <U8g2lib.h>

// --- BME680 SENSOR ---
#define BME_SDA 5
#define BME_SCL 4
Adafruit_BME680 bme;

// --- OLED AUSKOMMENTIERT ---
/*
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 1
#define OLED_SCL 2
#define OLED_ADDR 0x3C
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
*/

volatile bool pressed = false;
bool displayOn = false;
int textX = 128;
const char* message = "HALLO!";
unsigned long lastFrame = 0;

void IRAM_ATTR isr() {
  pressed = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(18, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(19, OUTPUT);
  digitalWrite(19, LOW);
  digitalWrite(3, LOW);
  digitalWrite(18, LOW);

  pinMode(0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(0), isr, RISING);

  //INITIALISIERUNG BME680
  Serial.println("Initialisiere BME680 auf IO5(SDA) und IO4(SCL)...");
  Wire.begin(BME_SDA, BME_SCL);

  if (!bme.begin(0x76)) {
    Serial.println("Konnte BME680 nicht finden! Adresse 0x76 prüfen.");
  } else {
    Serial.println("BME680 erfolgreich gestartet!");
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setGasHeater(320, 150);
  }

  //OLED SETUP
  /*
  Wire.begin(1, 2);
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.sendBuffer();
  */
}

void loop() {
  if (pressed == true) {
    Serial.println("BUTTON PRESSED - Messung ein/aus");
    digitalWrite(19, !digitalRead(19));
    digitalWrite(3, !digitalRead(3));
    digitalWrite(18, !digitalRead(18));
    pressed = false;
    displayOn = !displayOn;

    if (bme.performReading()) {
      Serial.print("Temperatur: "); Serial.print(bme.temperature); Serial.println(" *C");
      Serial.print("Luftfeuchte: "); Serial.print(bme.humidity); Serial.println(" %");
      Serial.print("Luftdruck: "); Serial.print(bme.pressure / 100.0); Serial.println(" hPa");
      Serial.print("Gas-Widerstand: "); Serial.print(bme.gas_resistance / 1000.0); Serial.println(" KOhms");
      Serial.println("-------------------------");
    } else {
      Serial.println("Fehler beim Lesen des BME680 :(");
    }
  }

  //MESSUNG STATT OLED
  if (!displayOn) return;

  // Alle 1000ms eine Messung durchführen
  if (millis() - lastFrame > 1000) {
    lastFrame = millis();
    //OLED
    /*
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB14_tr);
    int textWidth = u8g2.getStrWidth(message);
    u8g2.drawStr(textX, 40, message);
    u8g2.sendBuffer();
    textX--;
    if (textX < -textWidth) {
      textX = 128;
    }
    */
  }
}