#include <MQ2.h>
#include <SimpleDHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "AntaresESP8266HTTP.h"
#define ACCESSKEY "2e5ffa817daa2d6d:b54ad64256d0a29d"
#define WIFISSID "bilal34"
#define PASSWORD "coba123aja"
#define projectName "SmartEnviroment"
#define deviceName "coba"

AntaresESP8266HTTP antares(ACCESSKEY);
LiquidCrystal_I2C lcd(0x3f, 16, 2);
int pin = A0;
int pinDHT11 = 16;
SimpleDHT11 dht11(pinDHT11);
int lpg;
byte temperature;
byte humidity;
MQ2 mq2(pin);
byte relayInput_1 = 0;
byte relayInput_2 = 2;
/*
   -PIN-
=============
LCD
SDA     => D2
SCL     => D1
==============
RELAY 1 => D0
RELAY 2 => D2
==============
MQ2     => A0
==============
DHT11   => D16
*/
void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
  mq2.begin();
  lcd.begin();
  pinMode(relayInput_1, OUTPUT);
  pinMode(relayInput_2, OUTPUT);
  displayawal();
}
void loop() {
  lcd.begin();
  lcd.clear();
  pengukuransensor();
  displayhasilsensor();
  rule();
  kirim();
  delay(1000);
}
void displayawal()
{
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("IT WILL START IN");
    for (byte i = 0; i < 10; i++) {
        lcd.setCursor(7, 1);
        lcd.print(i);
        delay(250);
  } 
}
void pengukuransensor(){
  temperature = 0;
  humidity = 0;
  float* values = mq2.read(true);
  lpg = mq2.readLPG();  
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
    return;
  }
}
void displayhasilsensor(){
  Serial.print("SUHU SEKARANG:"); Serial.print((int)temperature); Serial.println("*C");
  Serial.print("Kadar LPG: "); Serial.println((int)lpg);
  lcd.setCursor(0,0);
  lcd.print("SUHU NOW : "+String(temperature));
  lcd.setCursor(0,1);
  lcd.print("LPG NOW: "+String(lpg));
}
void kirim(){
  int sizeData = 2;
  String dataName[sizeData],dataValue[sizeData];
  dataName[0] = "Suhu";
  dataName[1] = "Kadar CO";

  dataValue[0] = (int)temperature;
  dataValue[1] = (int)lpg;
  Serial.println(antares.storeData(projectName, deviceName, dataName, dataValue, sizeData));  
}
void rule(){
   if (temperature >= 33 )
  {
    Serial.println("relay SUHU hidup");
    digitalWrite(relayInput_1, HIGH);
  }
  else if (temperature <= 33 )
  {
    Serial.println("relay SUHU mati");
    digitalWrite(relayInput_1, LOW);
  }
  else if (lpg >=30 )
  {
    Serial.println("RELAY LPG HIDUP");
    digitalWrite(relayInput_2, HIGH);;
  }
  else if (lpg <= 30 )
  {
    Serial.println("RELAY LPG MATI");
    digitalWrite(relayInput_2, LOW);;
  }
  else{} 
}
