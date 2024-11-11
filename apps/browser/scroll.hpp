#ifndef APPS_BROWSER_SCROLL_HPP
#define APPS_BROWSER_SCROLL_HPP

#include "../../globals.hpp"
#include "./index.hpp"

void BrowserApp::Scroll(signed char direction)
{
  if (currentOnScrollHandler != nullptr)
    currentOnScrollHandler(direction);
}

#endif