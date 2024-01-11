#include <LiquidCrystal.h>
#include <Ultrasonic.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Ultrasonic ultrasonico(12, 13);
int sensorPin = A0;
int bomba = 8;
int zumbador = 11;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(bomba, OUTPUT);
}

void loop() {
  int humedad = analogRead(sensorPin);
  lcd.print("Humedad:");
  lcd.print(100 - humedad / 10.23);
  lcd.print("%");
  lcd.setCursor(0, 1);

  if (humedad >= 500) {
    ultrasonico.read();
    lcd.print("Suelo seco");
    lcd.setCursor(10, 1);
    ultrasonico.read();

    if (ultrasonico.read() > 6) {
      digitalWrite(bomba, LOW);
      digitalWrite(zumbador, HIGH);
    } else {
      digitalWrite(bomba, HIGH);
      digitalWrite(zumbador, LOW);
    }
  }

  else if (humedad < 500 && humedad > 300) {
    lcd.print("Suelo poco humedo");
    lcd.setCursor(10, 1);
  } else {
    lcd.print("Suelo humedo");
    lcd.setCursor(10, 1);
  }

  Serial.println(humedad);
  delay(1000);
  lcd.clear();
}
