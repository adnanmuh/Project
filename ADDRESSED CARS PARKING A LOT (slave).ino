#include <AntaresESP8266HTTP.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define ACCESSKEY "4398d61fc70bddcf:deccd923f2241613"
#define WIFISSID "Taoo"
#define PASSWORD "taoofeexs"
#define projectName "AddressedCarsParkingLots"
#define deviceName "CarsSensor"
#define PBX 0
volatile bool state = false;
volatile long debounce_time = 0;
volatile long current_time = 0;
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte x;
byte count = 0;
AntaresESP8266HTTP antares(ACCESSKEY);

void setup() {
  waiting();
  pinMode(PBX, INPUT_PULLUP);
  servo.attach(2);
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnectionNonSecure(WIFISSID, PASSWORD);
  attachInterrupt(digitalPinToInterrupt(PBX), intCallBack, RISING);
  Wire.begin(4, 5);
  refresh();
}

void loop() {
  while(state==false){
      Display();
    }
  if ((x == 8) || (x == 13) || (x == 16) || (x == 17)) {
    if (state == true) {
      Serial.println("Program mobil terakhir oke...");
      processX();
      delay(1000); 
      //SERVO MEMBUKA BEBERAPA DETIK
      Serial.println("Portal Opened");
      servo.write(8);
      delay(3000);
      state = !state;
      //SERVO MENUTUP BEBERAPA DETIK
      Serial.println("Portal Closed");
      servo.write(90);
      refresh();  
      Serial.println("Refresh complete..");
      count = 0;
      x = 18;
      Serial.println("x is 18");
      }
    else {}
   }  
  else {}
  if (state == true) {
    processX();
    delay(1000);
    //SERVO MEMBUKA BEBERAPA DETIK
    Serial.println("Portal Opened");
    servo.write(8);
    delay(3000);
    //SERVO MENUTUP BEBERAPA DETIK
    Serial.println("Portal Closed");
    servo.write(90);
    state = !state;
    refresh();
    count = 0;
  } 
  else if (count == 3) {
    while(state==false){
    refresh();
    Serial.println("Refresh complete..");
    break;  
    }
    count = 0;
  }
  else {
    Serial.println("Wait for Button Pressed");
    count++;
    Serial.println("COUNT :" + String(count));
  }
}
void refresh() {
  Serial.println("Get Lastest Data");
  waiting();
  antares.get(projectName, deviceName);
  x = antares.getInt("XValue");
  //Serial.println("Data from Antares is :"+String(x)); //check Nilai X
}
void intCallBack() {
  current_time = millis();
  //Serial.println("millis :"+String(current_time-debounce_time));
  if ((current_time - d][\\ebounce_time) > 250) {
    Serial.println("Interrupt Button Pressed");
    state = !state;
    debounce_time = current_time;
    exit;
  } else {}
  //Serial.println("State :"+String(state));
}
void processX() {
  // Parkir yang TERSEDIA akan ditampilkan di "serial-Monitor",
  // Parkir yang Terpakai tidak ditampilkan
  //lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  Serial.println("");
  switch (x) {
    case 18:
      Serial.println("Parkiran Penuh");
      lcd.print("MOHON MAAF");
      lcd.setCursor(4, 1);
      lcd.print("PARKIR PENUH");
      break;
    case 17:
      Serial.println("\tA");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("A");
      break;
    case 16:
      Serial.println("\tB");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("B");
      break;
    case 15:
      Serial.println("\tAB"); //Data Awal Salah (cp : adnan)
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("AB");
      break;
    case 13:
      Serial.println("\tC");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("C");
      break;
    case 12:
      Serial.println("\tAC");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("AC");
      break;
    case 11:
      Serial.println("\tBC");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("BC");
      break;
    case 10:
      Serial.println("\tABC");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("ABC");
      break;
    case 8:
      Serial.println("\tD"); //Data Awal Salah (cp : adnan)
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("D");
      break;
    case 7:
      Serial.println("\tAD");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("AD");
      break;
    case 6:
      Serial.println("\tBD");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("BD");
      break;
    case 5:
      Serial.println("\tABD");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("ABD");
      break;
    case 3:
      Serial.println("\tCD");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("CD");
      break;
    case 2:
      Serial.println("\tACD");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("ACD");
      break;
    case 1:
      Serial.println("\tBCD");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("BCD");
      break;
    case 0:
      Serial.println("\tABCD");
      lcd.print("TEMPAT TERSEDIA :");
      lcd.setCursor(8, 1);
      lcd.print("ABCD");
      break;
    default:
      Serial.println("\t\tError");
      break;
  }
  Serial.println("");
  Serial.println("");
}
void Display() {
  lcd.begin();
  lcd.setCursor(7, 0);
  lcd.print("SELAMAT DATANG ....");
  lcd.setCursor(17, 1);
  lcd.print("SILAHKAN TEKAN TOMBOL X");
  for (byte i = 0; i < 26; i++) {
    lcd.scrollDisplayLeft();
    if(state==false){
    delay(250);  
    }else{break;}
  }
  lcd.clear();
}
void waiting() {
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("TUNGGU SEBENTAR");
  lcd.setCursor(0, 1);
  lcd.print("  SYSTEM REFRESH");
}
