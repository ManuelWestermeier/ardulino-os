#include "./pos.hpp"
#include "./globals.hpp"
#include "./data.hpp"
#include "./cursor.hpp"
#include "./read/index.hpp"

void setup()
{
  lcd.init();
  lcd.backlight();

  lcd.createChar(cursor_charcode, cursorChar[0]);
  lcd.createChar(confirm_charcode, confirmChar);

  pinMode(swPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
}