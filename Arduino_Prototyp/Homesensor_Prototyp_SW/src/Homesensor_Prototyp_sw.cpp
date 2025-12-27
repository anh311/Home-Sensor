#include <DHT.h>
#include <Arduino.h>
#include <Stepper.h>
//DHT 
#define DHTPIN 5
#define DHTTYP DHT11
DHT dht(DHTPIN,DHTTYP);

//MOTOR
#define STEPS 200
#define IN1 12
#define IN2 11
#define IN3 10
#define IN4 9
Stepper stepper(STEPS,IN1,IN2,IN3,IN4);

//JOY-Stick
#define VRx A1
#define VRy A0

//init
void setup(){
    Serial.begin(9600);     //Serielle SChnittstelle (PC Kommunikation)
    dht.begin();            //init Temp Sensor
    stepper.setSpeed(60); 
}

void loop(){
    static unsigned long auslese_Zeit = 0;
    if(millis() - auslese_Zeit > 2000){
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        if (isnan(h) || isnan(t)) {
            Serial.println("Fehler beim Lesen des Sensors!");
        } else {
            Serial.print("Temp: "); Serial.print(t); Serial.print(" C, ");
            Serial.print("Humidity: "); Serial.print(h); Serial.println(" %");
        }
        auslese_Zeit = millis();
    }
     
    int xValue = analogRead(VRx);  // X-Achsenwert (0-1023)
    int yValue = analogRead(VRy);  // Y-Achsenwert (noch nicht genutzt)
    
    // --- Konstantgeschwindigkeit definieren ---
    int threshold = 50;   // toleriere kleine Abweichungen in der Mittelstellung

    // --- Richtung bestimmen ---
    if (xValue > 450 + threshold) {
        Serial.println("Joystick nach rechts bewegt");
        stepper.step(200);
    } 
    else if (xValue < 450 - threshold) {
        Serial.println("Joystick nach links bewegt");
        stepper.step(-200);
    } 

}