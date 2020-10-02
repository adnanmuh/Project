#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#define echoPin 3
#define trigPin 2 
const int buzzer = 5;
long duration;
int distance;
/*
PIN 
Ultrasonic
echo  => D3
trig  => D2
===========
Buzzer=> D5
===========
LCD I2C
SDA => pinSDA
SCL => pinSCL
===========
MLX90614
SDA => pinSDA
SCL => pinSCL
*/
LiquidCrystal_I2C lcd(0x27, 16, 2);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); 
  Serial.println("Ultrasonic Sensor HC-SR04 Test");
  Serial.println("with Arduino UNO R3");
  mlx.begin();
}
void loop() {
  mengukurjarak();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  lcd.setCursor(0, 0);
  lcd.print("DEKATKAN KEPALA");
  lcd.setCursor(0,1);
  lcd.print("SEDEKAT 10 CM");
  if (distance<=10){
    lcd.clear();
    Serial.println("Cek SUHU");
    loadingcuk();
    float suhuObject=mlx.readObjectTempC()+1.8;
    if (suhuObject<37){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SUHU ANDA:"+String(suhuObject));
      lcd.setCursor(0,1);
      lcd.print("CUCI TANGANMU");
      digitalWrite(buzzer,HIGH);    
      delay(1000);
      digitalWrite(buzzer,LOW);
    }
    else{
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("SUHU ANDA");
      lcd.setCursor(1,1);
      lcd.print("MELEBIHI BATAS");
        for (byte i=0;i<10;i++){
        digitalWrite(buzzer,HIGH);    
        delay(1000);
        digitalWrite(buzzer,LOW);
        delay(250);
      }
    }
  }
  else if(distance>10){
    Serial.println("BUAT JARAK 5CM AGAR DAPAT DILAKUKAN PENGECEKAN SUHU");
    delay(100);   
    digitalWrite(buzzer,LOW);
  }
  else{//Do nothing
    }
  delay(1000);
}
void mengukurjarak(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034 / 2)+2;
}
void loadingcuk(){
  lcd.setCursor(0,0);
  lcd.print("SCANING SUHU");
  for (byte i=0;i<10;i++){
    lcd.setCursor(7,1);
    lcd.print(i);
    delay(250);
  }
}
