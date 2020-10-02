/*
 * Nama Muhammad Adnan
 * NIRP 07111848007001 (ITS), NIM D400160004(UMS)
 * Tugas SET IoT
 */
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
char ssid [] = "SSD";  
char pass [] = "coba123aja"; 
byte mac[6];
char INSERT_SQL[] = "INSERT INTO coba1.esp8266(Suhu) VALUES (%f)"; 
int datasensor[10];
float suhu;
int PinSuhu = A0 ;
float suhu1,data ;
WiFiServer server(80);
WiFiClient client;
MySQL_Connection conn((Client *)&client);

char query [128];

IPAddress server_addr(192,168,1,116);//MySQL Server IP
char user[]     = "adnan123"; //MySQL User
char password[] = "adnan";//MySQL password

void setup() 
  {
  Serial.begin(9600) ;//BOUDRATE
  pinMode(PinSuhu, INPUT) ;
  Serial.println("Initialising connection");
  Serial.print(F("Setting static ip to : "));
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  WiFi.macAddress(mac);
  Serial.println(mac)
  Serial.print("Assigned IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  Serial.println("Connecting to database");
  while (conn.connect(server_addr, 3306, user, password) != true) 
  {
    delay(1000);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("Connected to SQL Server!");
  }
void loop() 
  {
  data = analogRead(PinSuhu) ; 
  suhu =  (data * 0.0048828125 * 100); //RUMUS ADC ke Suhu
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  for (int b=0;b<1;b++)
  {
    sprintf(query, INSERT_SQL, suhu);
    cur_mem->execute(query);
  }
  delete cur_mem;
  Serial.print(" Suhu : ");
  Serial.print(suhu) ;
  Serial.print(" C") ;
  delay(1000) ;
}
