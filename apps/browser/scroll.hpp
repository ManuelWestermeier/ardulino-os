#ifndef APPS_BROWSER_SCROLL_HPP
#define APPS_BROWSER_SCROLL_HPP

#include "../../globals.hpp"
#include "./index.hpp"

void BrowserApp::Scroll(signed char direction) {
  Serial.print(direction > 0 ? "Scroll UP" : "Scroll Down");
}

#endif