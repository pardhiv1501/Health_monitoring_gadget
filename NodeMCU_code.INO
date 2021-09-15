#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int ActivateSwitch = D4;  //send data to server only when this switch is high


const int pulse=A0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(pulse,INPUT);
  pinMode(ActivateSwitch,INPUT);
  mlx.begin();
}
float farh;
void loop() { 
  float farh = mlx.readObjectTempF();
  string puls=string(analogRead(pulse));
  String t = String(farh);
  Serial.print(t);
  Serial.print(puls);
}

