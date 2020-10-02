#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <dht11.h>
#define DHT11PIN 16
#define LIGHT 14
dht11 DHT11;
char auth[] = "psFJZcT2sCndd9G2TmoawPdz3ygi_Hck";
char ssid[] = "OPPO";
char pass[] = "AYRAFAZIA";
byte Relay_State1, Relay_State2, Relay_State3, Relay_State4;
byte relay1 = 5;
byte relay2 = 4;
byte relay3 = 0;
byte relay4 = 2;
float suhu;
int L;
byte mode;
WidgetLCD lcd(V6);
WidgetLED led1(V7),led2(V8),led3(V9),led4(V10);
BlynkTimer timer;
/*
PIN
relay1 = D5
relay2 = D4
relay3 = D0
relay4 = D2
DHT 11 = D16
LDR    = D14
MIKROKONTROLLER ESP8266
Platform IoT = Blynk
*/
BLYNK_WRITE(V1)
{
  Relay_State1 = param.asInt(); // assigning incoming value from pin V1 to a variable
}
BLYNK_WRITE(V2)
{
  Relay_State2 = param.asInt(); // assigning incoming value from pin V1 to a variable
}
BLYNK_WRITE(V3)
{
  Relay_State3 = param.asInt(); // assigning incoming value from pin V1 to a variable
}
BLYNK_WRITE(V4)
{
  Relay_State4 = param.asInt(); // assigning incoming value from pin V1 to a variable
}
BLYNK_WRITE(V5)
{
  mode = param.asInt(); // assigning incoming value from pin V1 to a variable
}

void setup()
{
  Serial.begin(9600);
  pinMode(LIGHT, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10000L, lcdblynk);
}

void loop()
{
  int chk=DHT11.read(DHT11PIN);
  suhu=(float)DHT11.temperature;
  L =digitalRead(LIGHT);
  Serial.println("SUHU :"+String(suhu)+"C");
  Serial.println("Kecerahan :"+String(L));
  Serial.println("Kondisi Relay 1 : "+String(Relay_State1));
  Serial.println("Kondisi Relay 2 : "+String(Relay_State2));
  Serial.println("Kondisi Relay 3 : "+String(Relay_State3));
  Serial.println("Kondisi Relay 4 : "+String(Relay_State4));
  Mode();
  Blynk.run();
  timer.run();
}

void lcdblynk()
{
  lcd.clear();
  lcd.print(0, 0, "SUHU :"+String(suhu)); 
  if(L==1){
   lcd.print(0, 1, "CAHAYA REDUP");
  }
  else if(L==0){
   lcd.print(0, 1, "CAHAYA TERANG"); 
   digitalWrite(relay2, HIGH);
  }
  else{}
}
void Mode(){
  if (mode==1){// Mode Automatis Dimana Relay 1(Kipas)akan hidup berdasarkan kondisi suhu dan Relay2(Lampu)akan hidup berdasarkan tergantung seberapa terang kondisi pencahayaan ruangan
    if (suhu>32 && L==1){
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    } 
    else if(suhu>32 || L==0){
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    } 
    else if(suhu<32 || L==1){
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);  
    } 
    else if(suhu<32 && L==0){
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);  
    }
    else if( Relay_State1==0 || Relay_State2==0){
    Blynk.notify("TIDAK BISA DIGUNAKAN KETIKA MODE AUTOMATIS");  
    }
    else if (Relay_State3==1){
    digitalWrite(relay3, HIGH);  
    led3.off();
    }
    else if (Relay_State3==0){
    digitalWrite(relay3, LOW);  
    led3.on();
    }
    else if (Relay_State4==1){
    digitalWrite(relay4, HIGH);  
    led4.off();
    }
    else if (Relay_State4==0){
    digitalWrite(relay4, LOW);  
    led4.on();
    } 
    else{}    
  }
  else if (mode==0){
    if (Relay_State1==1){
    digitalWrite(relay1, HIGH);  
    led1.off();
    }
    else if (Relay_State1==0){
    digitalWrite(relay1, LOW);  
    led1.on();
    }
    else if (Relay_State2==1){
    digitalWrite(relay2, HIGH);  
    led2.off();
    }
    else if (Relay_State2==0){
    digitalWrite(relay2, LOW);  
    led2.on();
    }
    else if (Relay_State3==1){
    digitalWrite(relay3, HIGH);  
    led3.off();
    }
    else if (Relay_State3==0){
    digitalWrite(relay3, LOW);  
    led3.on();
    }
    else if (Relay_State4==1){
    digitalWrite(relay4, HIGH);  
    led4.off();
    }
    else if (Relay_State4==0){
    digitalWrite(relay4, LOW);  
    led4.on();
    } 
    else{}
  }
  else{}
}
