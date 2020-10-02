  
#include <ESP8266WiFi.h>      
#include <DHT.h>              
#include <ThingerESP8266.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
/*
DHT11 => A0
Platform IoT Using thinger & Telegram
*/
#define BOTtoken "709016179:AAGrJJllgzw_PCFV3btTQmIc8uBpQEoUGSg"
String chatid = "607520351";
#define USERNAME "User Name" 
#define DEVICE_ID "Device id"
#define DEVICE_CREDENTIAL "code credential" 
#define SSID "Nama Wifi" 
#define SSID_PASSWORD "Password Wifi" 
#define DHTPIN D0 
#define DHTTYPE DHT11
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); 
DHT dht(DHTPIN, DHTTYPE); 
float hum,temp; 
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
void setup() {
  Serial.begin(9600); //baudrate
  Serial.println("Baca DHT11");
  dht.begin();
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["dht11"] >> [](pson& out){
    out["humidity"] = hum;
    out["celsius"] = temp;
  };
}
 
void loop() 
{  
  String Suhu;
  thing.handle(); 
  float h = dht.readHumidity(); //Membaca kelembaban
  float t = dht.readTemperature(); //Membaca suhu dalam satuan Celcius
  float f = dht.readTemperature(true); //Membaca suhu dalam satuan Fahrenheit
  hum = h;
  temp = t;
  Suhu="Suhu Sekarang"+String(t)
  bot.sendMessage(chatid, Suhu);
  Serial.println("Pesan Terkirim ke Telegram");
}
