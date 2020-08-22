// Include the library code:
#include <LiquidCrystal.h>

// Display
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte celsius[8] = {
  B00000,
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000
};

// Variables
int selector;

// Selector
const int pot = 1;

void setup() {
  // LCD's number of columns and rows & char:
  lcd.begin(16, 2);
  
  lcd.createChar(0,celsius);
  

  // Serial communication
  Serial.begin(9600);
}

void loop() {
  // Selector
  selector = constrain(map(analogRead(1), 0, 1024, 10, 61), 10, 60);
  /* Mostrar en pantalla
  lcd.clear();
  lcd.print(selector);
  lcd.write(byte(0));
  lcd.print("C");
  delay(33);
  */

  
}
