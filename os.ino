#include "./pos.hpp"
#include "./globals.hpp"
#include "./data.hpp"
#include "./cursor.hpp"
#include "./read/index.hpp"

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.createChar(cursor_charcode, cursorChar[0]);
  lcd.createChar(confirm_charcode, confirmChar);

  pinMode(swPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

String x;

void loop() {
  String prompt = "Hello World ... Long String Overflow 0128282828";
  DrawKeyBoardMetaData drawKeyBoardMetaData = { prompt.length(), &prompt };

  lcd.print(*ReadString(drawKeyBoardMetaData));

  delay(RENDERING_FRAME * 100);
  lcd.clear();
}