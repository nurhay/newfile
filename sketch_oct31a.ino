
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include "EmonLib.h"
 
EnergyMonitor emon1;
 
int tegangan = 220.0;
 
//pin yang digunakan sensor SCT
int pin_sct = A0;
 
LiquidCrystal_PCF8574 lcd(0x38); 
// dapat dicek menggunakan i2c finder
 
void setup()
{
Serial.begin(9600);
lcd.begin(16, 2); //prosedur pemanggilan LCD
lcd.setBacklight(255);
 
lcd.setCursor(00, 00); //set pada baris 1 dan kolom 1
lcd.print("*Hello World*"); //menuliskan "Hello World"
lcd.setCursor(00, 1); //set pada baris 2 dan kolom 1
lcd.print("*nyebarilmu.com*"); //menuliskan "nyebarilmu.com"
 
lcd.clear(); //menghapus data sebelumnya
 
delay(3000);
 
//calib - Cur Const= Ratio/BurdenR. 2000/33 = 60
emon1.current(pin_sct, 60);
}
 
void loop()
{ 
  double Irms = emon1.calcIrms(1480);
  //menampilkan di serial monitor
  Serial.print("Arus yang terbaca : ");
  Serial.print(Irms);
  Serial.print("Daya yang terbaca : ");
  Serial.println(Irms*tegangan);
 
  //menampilkan di LCD 16x2
  lcd.setCursor(00,00);
  lcd.print("Arus (A):");
  lcd.setCursor(00,1);
  lcd.print("Daya (W):"); 
 
//Arus
  lcd.setCursor(10,00);
  lcd.print(Irms);
 
//Daya
  lcd.setCursor(10,1);
  lcd.print("      ");
  lcd.setCursor(10,1);
  lcd.print(Irms*tegangan,1);
  
  delay(1000);
}
