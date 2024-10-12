#ifndef APPS_BROWSER_ON_CLICK_HPP
#define APPS_BROWSER_ON_CLICK_HPP

#include "../../globals.hpp"
#include "../../app-renderer.hpp"
#include "../../utils/structs/pos.hpp"
#include "./index.hpp"

void BrowserApp::OnClick(Pos clickPos)
{
    if (WiFi.status() != WL_CONNECTED && connectToWfifButton.collidesWith(clickPos))
    {
        AppRender::appOpened = "wifi";
    }
}

#endif