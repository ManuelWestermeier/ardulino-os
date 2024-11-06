#ifndef APPS_BROWSER_ON_EXIT_HPP
#define APPS_BROWSER_ON_EXIT_HPP

#include "../../globals.hpp"
#include "./index.hpp"

void BrowserApp::OnExit()
{
  Serial.print("Exit");
}

#endif