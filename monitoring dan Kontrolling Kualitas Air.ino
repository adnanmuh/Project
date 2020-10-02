#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>
const int oneWireBus = 26;  
#define SensorPin 25        
int sensor_in = 36;         
const int relay1 = 33;
const int relay2 = 32;

OneWire oneWire(oneWireBus); 
DallasTemperature sensors(&oneWire);
float temperatureC,temperatureF;
float phValue;
String stateKeruh;
int KeruhValue;
char auth[] = "32915c91569e42fe9fea855fe402f33f";
char ssid[] = "SSID";//WiFi
char pass[] = "coba123aja";//Pass WiFi
byte x,In,Out;
WidgetLED led1(V12),led2(V13);
BLYNK_WRITE(V5)
{
  x = param.asInt();  
}
BLYNK_WRITE(V11)
{
  In = param.asInt(); 
}
BLYNK_WRITE(V10)
{
  Out = param.asInt(); 
}
void setup() {
  Serial.begin(115200);
  sensors.begin();
  Blynk.begin(auth, ssid, pass, "iwancilibur.my.id", 8080);
  pinMode(sensor_in, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}
void loop() {
  bacasensorSuhu();
  membacapH();
  membacakeruh();
  Blynk.virtualWrite(V1,temperatureC);
  Blynk.virtualWrite(V2,phValue);
  Blynk.virtualWrite(V3,stateKeruh);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  Serial.print("PH: ");
  Serial.println(phValue);
  Serial.print("Tingkat Kerjernihan air: ");
  Serial.println(stateKeruh);
  if (x==1){
    Serial.println("MODE AUTOMATIS");
    if(In==1 || Out==1){
     Blynk.notify("TIDAK BISA MENGGUNAKAN KETIKA MODE AUTOMATIS"); 
    }
    else if (KeruhValue==1){
      Serial.println("AIR JERNIH DO NOTHING");
    }
    else if(KeruhValue==0){
      Serial.println("Start Siklus 1");
      digitalWrite(relay1, LOW);
      delay (5000);
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, LOW);
      delay (5000);
      digitalWrite(relay2,HIGH);
    }
    else{}
  }
  else if (x==0){
    Serial.println("MODE MANUAL");
    if (In==1 && Out==1){
     Serial.println(" In =1 & Out==1");
     led1.on();
     led2.on();
     digitalWrite(relay1, HIGH);
     digitalWrite(relay2, HIGH);
     Blynk.notify("EROR TIDAK BISA BEKERJA SECARA BERSAMAAN");
    }
    else if(In==1 && Out==0){
     Serial.println(" In =1 & Out==0");
     led1.on();
     led2.off(); 
     digitalWrite(relay1, HIGH);
     digitalWrite(relay2, LOW);
    }
    else if(In==0 && Out==1){
     Serial.println(" In =0 & Out==1");
     led1.off();
     led2.on();
     digitalWrite(relay1, LOW);
     digitalWrite(relay2, HIGH);
    }
     else if(In==0 && Out==0){
      Serial.println("In dan Out = 0 ");
      led1.off();
      led2.off();
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
    }
    else{}
  }
  else{
    Serial.println("EROR");
  }
  Blynk.run();
  delay(1000);
}
void bacasensorSuhu(){
  sensors.requestTemperatures(); 
  temperatureC = sensors.getTempCByIndex(0);
  temperatureF = sensors.getTempFByIndex(0);
}

void membacapH(){
unsigned long int avgValue;  
float b;
int buf[10],temp;
   for(int i=0;i<10;i++)   
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)  
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      
  avgValue+=buf[i];
  phValue=(float)avgValue*5.0/4096/6;  
  phValue=3.5*phValue; 
}
void membacakeruh(){
  int q=digitalRead(sensor_in);
   if(q==LOW){
   stateKeruh="jernih";
   KeruhValue=1;
  }
  else{
   stateKeruh="keruh";
   KeruhValue=0;
  } 
}
