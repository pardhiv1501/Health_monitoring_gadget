#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h> 
int Contrast=75;
LiquidCrystal lcd(12, 11, 9, 8, 7, 3);  
SoftwareSerial espSerial(5, 6);
#include "MAX30100_PulseOximeter.h"
 
#define REPORTING_PERIOD_MS     1000

int PulseSensorPurplePin = A0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED

 
PulseOximeter pox;
uint32_t tsLastReport = 0;
String str; 

int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.

void onBeatDetected()
{
    Serial.println("Beat!");
}
void setup()
{
    Serial.begin(9600);
    espSerial.begin(9600);
     analogWrite(2,80);
     lcd.begin(16, 2);
     lcd.print("Device starting");
    Serial.print("Initializing pulse oximeter..");
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
  lcd.setCursor(0, 0);
     lcd.print("IOT Health");
   
    lcd.setCursor(0, 1);
     lcd.print("Monitoring");
     delay(2000);
    lcd.clear();
}
int counting=0; 
void loop()
{
   lcd.setCursor(0, 0);
     lcd.print("HRT:");
   
    lcd.setCursor(0, 1);
     lcd.print("So2:");

     lcd.setCursor(8, 0);
     lcd.print("Tem:");
   
    lcd.setCursor(8, 1);
     lcd.print("Pul:");
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        lcd.setCursor(4, 0);
        
        lcd.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(random(70, 100));
        lcd.setCursor(4, 1);
        lcd.print(random(pox.getSo2Level());
        
        String t = espSerial.readString();
        lcd.setCursor(12, 0);
        float tem = t.toFloat();
        lcd.print(tem);
        
        tsLastReport = millis();
        Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
        lcd.setCursor(12, 1);
        lcd.print(Signal);
        Serial.println(Signal);                    // Send the Signal value to Serial Plotter.
    
}
