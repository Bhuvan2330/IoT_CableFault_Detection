//Header File
#include<LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

#include <SoftwareSerial.h>
// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(10, 11);

//Voltage Sensor
int vol = A1;  //Voltage Sensor
int volt= 0;
int vrv = 0;
int voltv=0;

int c1v = A2;
int c2v = A4;

int c1 = 0;
int c2 = 0;

String latlan = "10.92816,78.74825";

//Relay and Buzzer
int relay = 12;
int buz = 13;
int incomingByte = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(vol, INPUT);
  pinMode(c1v, INPUT);
  pinMode(c2v, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(buz, OUTPUT);
  
  Serial.begin(9600);
  gpsSerial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("SMART IOT BASED");
  lcd.setCursor(0,1);
  lcd.print("CABLE FAULT DET.");
  delay(1500);

  digitalWrite(buz, HIGH);
  delay(500);
  lcd.clear();
  digitalWrite(buz, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  volt = analogRead(vol);
  volt = volt/2.5;

  c1 = digitalRead(c1v);
  c2 = digitalRead(c2v);

  lcd.setCursor(0,0);
  lcd.print("V:");
  lcd.print(volt);
  lcd.print(" ");

  lcd.setCursor(6,0);
  lcd.print("C1:");
  lcd.print(c1);
  
  lcd.setCursor(12,0);
  lcd.print("C2:");
  lcd.print(c2);


  if(volt <= 160){
    digitalWrite(buz, HIGH);
    digitalWrite(relay, HIGH);
    lcd.setCursor(0,1);
    lcd.print("VOLT FAULT");
    delay(500);
    digitalWrite(buz, LOW);
    gsm_msg(1);
  }
  else if(volt >= 250){
    digitalWrite(buz, HIGH);
    digitalWrite(relay, HIGH);
    lcd.setCursor(0,1);
    lcd.print("VOLT FAULT");
    delay(500);
    digitalWrite(buz, LOW);
    gsm_msg(1);
  }
  else if(c1 == 1 || c2 == 1){
    digitalWrite(buz, HIGH);
    lcd.setCursor(0,1);
    lcd.print("CABLE FAULT");
    delay(500);
    digitalWrite(buz, LOW);
    gsm_msg(1);
  }
  else{
    digitalWrite(relay, LOW);
    lcd.setCursor(0,1);
    lcd.print("NORMAL     ");
    digitalWrite(buz, LOW);
  }
 
  delay(800);

}


void gsm_msg(int a)
{
  lcd.setCursor(6,1);
  lcd.print("SDG.");
  delay(100);
  gpsSerial.println("AT");
  delay(500);
  gpsSerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  digitalWrite(buz, HIGH);
  delay(1000);
  digitalWrite(buz, LOW);
  if (a == 1){
    gpsSerial.println("AT+CMGS=\"+919943554772\"\r"); // change to the phone number you using
    lcd.setCursor(6,1);
    lcd.print("SDG..1");
    delay(100);
  }
  else if(a == 2){
    gpsSerial.println("AT+CMGS=\"+91\"\r"); // change to the phone number you using 
    lcd.setCursor(6,1);
    lcd.print("SDG..2");
    delay(100);
  }
  
  digitalWrite(buz, HIGH);
  delay(1000);
  digitalWrite(buz, LOW);
  lcd.setCursor(6,1);
  lcd.print("SDG..");
  //10.815226, 78.673857
  gpsSerial.println("Emergency Cable Fault...@");//the content of the message
  delay(500);
  lcd.setCursor(6,1);
  lcd.print("SDG...");
  delay(1000);
  gpsSerial.println((char)26);//the stopping character
  delay(1000);
  digitalWrite(buz, HIGH);
  lcd.setCursor(6,1);
  lcd.print("SMS SENT....");
  delay(1000);
  lcd.setCursor(6,1);
  lcd.print("           ");
  digitalWrite(buz, LOW); 
  
}
