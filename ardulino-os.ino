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
  Auth();
}

void loop() {
  AppRender::UpdateCurrentApp();
  AppRender::Update();
}