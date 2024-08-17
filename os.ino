#include "./utils/structs/pos.hpp"
#include "./utils/structs/draw-keybord-meta-data.hpp"
#include "./globals.hpp"
#include "./data/index.hpp"
#include "./cursor.hpp"
#include "./read/index.hpp"
#include "./utils/index.hpp"
#include "./apps/create-account/index.hpp"
#include "./apps/login/index.hpp"
#include "./apps/home/index.hpp"
#include "./apps/browser/index.hpp"
#include "./app-renderer.hpp"
#include "./auth.hpp"

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

  InitData();
  Auth();
}

void loop()
{
  AppRender::UpdateCurrentApp();
  AppRender::Update();
}