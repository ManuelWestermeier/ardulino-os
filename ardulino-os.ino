#include "./config.hpp"

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

void setup() {
  Init();
  while (true) {
    lcd.clear();
    lcd.home();
    lcd.print(utils::normalizeJoystick(xPin));
    delay(100);
  }
  Auth();
}

void loop() {
  AppRender::UpdateCurrentApp();
  AppRender::Update();
}