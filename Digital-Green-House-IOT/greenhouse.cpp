
#include "DHT.h"
#include <LiquidCrystal.h>
DHT dht;
int moisturesensorPin = A0;
int moisturesensorValue = 0;
int percent = 0;
int dhtPin = 53;
int Delay;
int humidity;
int temp;
int waterpin = 6;
int fan = 7;
int dryer = 5;

const int rs = 12, en = 11, d4 = 9, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.


  Serial.begin(9600);
  dht.setup(dhtPin);
  pinMode(fan, OUTPUT);
  pinMode(dryer, OUTPUT);
  pinMode(waterpin, OUTPUT);
//  digitalWrite(fan, HIGH);
//  digitalWrite(waterpin, HIGH);
//  digitalWrite(dryer, LOW);
}

void loop() {
  lcd.clear();
  Delay = dht.getMinimumSamplingPeriod();
  delay(Delay);
  Serial.print("humidity\n");
  humidity = dht.getHumidity();
  Serial.print(humidity);
  Serial.print("\n");
  temp = dht.getTemperature();
  // Serial.print(temp);
  //  temp=32+(temp*9/5);
  if (temp >= 25)
  {
    digitalWrite(fan, LOW);
    Serial.print("khub gorom porse\n");

  }
  else if (temp <= 20)
  {
    digitalWrite(fan, HIGH);
    Serial.print("onek thanda porse\n");

  }
  else
  {
    digitalWrite(fan, LOW);
    Serial.print("onek thanda porse new\n");

  }



  if (humidity >= 70)
  {
    digitalWrite(dryer, HIGH);

  }
  else if (humidity <= 60)
  {
    digitalWrite(dryer, LOW);

  }

  Serial.print("temperature\n");
  Serial.print(temp);
  Serial.print("\n");
  moisturesensorValue = analogRead(moisturesensorPin);
  Serial.print("Sensor Value ");
  Serial.print(moisturesensorValue);
  percent = convertToPercent(moisturesensorValue);
  if (percent <= 20)
  {
    digitalWrite(waterpin, HIGH);
  }
  else if (percent >= 60)
  {
    digitalWrite(waterpin, LOW);
  }
  Serial.print(" \npersent Value ");
  Serial.print(percent);
  Serial.print("\n");
 // Print first line to LCD
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(round(temp));
  lcd.print("C  MOS:");

  // Print second line to LCD
  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%  "); // extra space in case humidity drops to single digit
  lcd.print(percent);
  lcd.print("%");
  delay(750);


}

int convertToPercent(int value)
{
  int persentValue = 0;
  persentValue = map(value, 983, 330, 0, 100);
  if (persentValue > 100)
    persentValue = 100;
   if (persentValue < 0)
    persentValue = 0;

  return persentValue;
}
