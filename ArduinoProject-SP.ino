#include <LiquidCrystal_I2C.h>
#include "Sensor.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Sensor CO(A0, 7, 400);
Sensor CO2(A1, 2, 400);
Sensor sensoritos[2] = {CO2, CO};

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print(A0);
  lcd.print(A1);

  for (int i = 0; i < 2; i++) {
    pinMode(sensoritos[i].getLedPin(), OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 2; i++) {
    if (sensoritos[i].Monitor() == true) {
      tone(5, 330, 100);
      digitalWrite(sensoritos[i].getLedPin(), HIGH);
      delay(1000);
      digitalWrite(sensoritos[i].getLedPin(), LOW);
      delay(1000);
    }

    lcd.setCursor(0, i * 3);
    lcd.print(sensoritos[i].readData());
    lcd.print("/");
    lcd.print(sensoritos[i].getSensorLimit());
  }

  Serial.println();
}

class Sensor {
private:
  int sensorPin;
  int ledPin;
  int sensorCurrentValue;
  int sensorLimit;

public:
  Sensor(int _spin, int _lpin, int _limit) {
    sensorPin = _spin;
    ledPin = _lpin;
    sensorLimit = _limit;
  }

  int getPinvalue() {
    return sensorPin;
  }

  int getLedPin() {
    return ledPin;
  }

  int getSensorLimit() {
    return sensorLimit;
  }

  bool Monitor() {
    sensorCurrentValue = analogRead(sensorPin);
    if (sensorCurrentValue > sensorLimit) {
      return true;
    } else {
      return false;
    }
  }

  int readData() {
    return analogRead(sensorPin);
  }
};

