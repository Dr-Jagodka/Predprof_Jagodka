#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define COEFFK 14.17393
#define COEFFB 1901.29571

int tara = 0;
float alpha = 0.03, smoothedMass = 134, output;

void setup() {
  pinMode(A1, INPUT);
  lcd.init();           
  lcd.backlight();        
  lcd.setCursor(1, 0); 
}

int makemass(int input) {
  return input * COEFFK - COEFFB;
}

void loop() {
  float rawMass = (float)(analogRead(1));
  smoothedMass = alpha * rawMass + (1 - alpha) * smoothedMass;
  if (digitalRead(2) == 1) {
    tara = makemass(smoothedMass);
    delay(1000);
  }
  output = (makemass(smoothedMass) - tara) / 1000.;
  lcd.print(output);
  delay(50);
  lcd.clear();              
}