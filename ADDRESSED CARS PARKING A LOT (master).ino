#include <AntaresESP8266HTTP.h>
#define ACCESSKEY "4398d61fc70bddcf:deccd923f2241613"
#define WIFISSID "SSID"
#define PASSWORD "coba123aja"
#define projectName "percobaan2"
#define deviceName "cobaaja"
#define pBA 5
#define pBB 4
#define pBC 14 //Flash
#define pBD 12 //TXD1 SAAT UPLOAD TOLONG DI NULL KAN! <<<<<<<<<<<< Perhatian
  byte x;      // Var ada berpotensi kesamaan
  byte A;
  byte B;
  byte C;
  byte D;

AntaresESP8266HTTP antares(ACCESSKEY);
void setup() {
  pinMode(pBA,INPUT_PULLUP);
  pinMode(pBB,INPUT_PULLUP);
  pinMode(pBC,INPUT_PULLUP);
  pinMode(pBD,INPUT_PULLUP);
  
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
 
  Serial.begin(115200);
}

void loop() {
  byte stateA = digitalRead(pBA);
  byte stateB = digitalRead(pBB);
  byte stateC = digitalRead(pBC);
  byte stateD = digitalRead(pBD);
  //active HIGH
  if(stateA == HIGH) 
  {
    A=0;
    Serial.print("A = 0" /*+String(A)*/);
  }else{
    A=1;
    Serial.print("A = 1"/*+String(A)*/);
  }
   if(stateD == HIGH)
  {
    D=0;
    Serial.println("\tD = 0"/*+String(D)*/);
  }else{
    D=10;
    Serial.println("\tD = 1"/*+String(D)*/);
  }
  if(stateB == HIGH)
  {
    B=0;
    Serial.print("B = 0"/*+String(B)*/);
  }else{
    B=2;
    Serial.print("B = 1"/*+String(B)*/);
  }
   if(stateC == HIGH)
  {
    C=0;
    Serial.println("\tC = 0"/*+String(C)*/);
  }else{
    C=5;
    Serial.println("\tC = 1"/*+String(C)*/);
  }
  x=A+B+C+D;
 Serial.print("nilai x = ");
 Serial.println(String(x)+"\n");
  int sizeData = 1;
  String dataName[sizeData],dataValue[sizeData];
  dataName[0] = "nilai x";
  dataValue[0] = (byte) x;
 Serial.println(antares.storeData(projectName, deviceName, dataName, dataValue, sizeData));
 delay(1000);
 
}
