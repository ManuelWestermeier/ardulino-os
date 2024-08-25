// #define IS_IN_DEBUG_LOGGED_IN

#include "./utils/index.hpp"
#include "./utils/structs/draw-keybord-meta-data.hpp"
#include "./globals.hpp"
#include "./utils/structs/clickable.hpp"
#include "./data/index.hpp"
#include "./cursor.hpp"
#include "./read/index.hpp"
#include "./utils/index.hpp"
#include "./app-renderer.hpp"
#include "./auth.hpp"

void setup()
{
  lcd.init();
  lcd.backlight();

  lcd.createChar(cursor_charcode, cursorChar[0]);
  lcd.createChar(confirm_charcode, confirmChar);
  lcd.createChar(upArrowChar, upArrow);
  lcd.createChar(downArrowChar, downArrow);

  pinMode(swPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);

  InitData();
  Auth();
}

void loop()
{
  AppRender::UpdateCurrentApp();
  AppRender::Update();
}