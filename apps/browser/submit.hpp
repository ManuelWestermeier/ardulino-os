#ifndef APPS_BROWSER_SUBMIT_HPP
#define APPS_BROWSER_SUBMIT_HPP

#include "../../globals.hpp"
#include "./index.hpp"

void BrowserApp::Submit()
{
    pages.Navigate({RoutePart("home")});
}

#endif