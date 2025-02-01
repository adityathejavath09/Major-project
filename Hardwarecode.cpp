#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>         
 #include <LiquidCrystal_I2C.h>  
#define WIFI_SSID "trafficiot"                                          
#define WIFI_PASSWORD "trafficiot01"     

String fireStatus = "";  
String fireStatus1 = "";   
 
LiquidCrystal_I2C lcd(0x27,16,2);  
int g1 = D6;
int r1 = D5;
int g2 = D3;
int r2 = D0;

void setup() 
{

   lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
    Serial.begin(9600);
    lcd.print(" SMART TRAFFIC   "); 
    lcd.setCursor(0,1);  
   lcd.print("  MANAGEMENT SYS "); 

  pinMode(g1, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(g2, OUTPUT);

  Serial.begin(9600);
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  delay(200);
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  delay(200);

  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  delay(200);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  delay(200);

  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
    Serial.print("Connecting");
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
      }
      Serial.println();
      Serial.print("connected: ");
      Serial.println(WiFi.localIP());

      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  

delay(1000);


}

void loop() 
{

     if(Firebase.failed())
     {
       Serial.print("Firebase error");
       Serial.println(Firebase.error());
     }    



fireStatus = Firebase.getString("TRAFFIC/COUNT"); 

Serial.println(fireStatus);
lcd.clear();  
lcd.setCursor(0,0);
lcd.print("TRAFFIC LANE : "); 
if(fireStatus != "")
{
  if(fireStatus == "1")
  {
    digitalWrite(g1, LOW);
    digitalWrite(r2, LOW);
    digitalWrite(g2, HIGH);
    digitalWrite(r1, HIGH);
    delay(200);

    lcd.setCursor(0,0);
    lcd.print("TRAFFIC LANE: "); 
    lcd.setCursor(0,1);  
     lcd.print(fireStatus); 
  }
  else if(fireStatus == "2")
  {
    digitalWrite(g2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(g1, HIGH);
    digitalWrite(r2, HIGH);
    delay(200);
    lcd.setCursor(0,0);
    lcd.print("TRAFFIC LANE: "); 
    lcd.setCursor(0,1);  
     lcd.print(fireStatus); 
  }
  else if( fireStatus == "3")
  {
    digitalWrite(g1, HIGH);
    digitalWrite(r2, LOW);
    digitalWrite(g2, HIGH);
    digitalWrite(r1, LOW);
    delay(200);
    lcd.setCursor(0,0);
     lcd.print("TRAFFIC LANE: "); 
    lcd.setCursor(0,1);  
     lcd.print(fireStatus);
  }
  else
  {
    digitalWrite(g1, HIGH);
    digitalWrite(r2, LOW);
    digitalWrite(g2, HIGH);
    digitalWrite(r1, LOW);
    delay(100);
    lcd.setCursor(0,0);
     lcd.print("TRAFFIC LANE: "); 
    lcd.setCursor(0,1);  
     lcd.print(fireStatus);
  }
   Firebase.setString("Traffic/SIGN", ""); 
}


}