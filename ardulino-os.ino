#include "./config.hpp"

#include "./utils/index.hpp"
#include "./utils/structs/draw-keybord-meta-data.hpp"
#include "./globals.hpp"
#include "./wifi/on-wifi-change.hpp"
#include "./utils/structs/clickable.hpp"
#include "./data/index.hpp"
#include "./cursor.hpp"
#include "./read/index.hpp"
#include "./utils/index.hpp"
#include "./app-renderer.hpp"
#include "./auth.hpp"

void setup()
{
  InitializeApps();
  WifiMenager::Update();
  Init();
  Auth();
  WifiMenager::Update();
}

void loop()
{
  WifiMenager::Update();
  AppRender::UpdateCurrentApp();
  AppRender::Update();
}