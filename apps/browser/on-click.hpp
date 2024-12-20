#ifndef APPS_BROWSER_ON_CLICK_HPP
#define APPS_BROWSER_ON_CLICK_HPP

#include "../../globals.hpp"
#include "../../app-renderer.hpp"
#include "../../utils/structs/pos.hpp"
#include "./index.hpp"

void BrowserApp::OnClick(Pos clickPos)
{
#ifndef DEBUG_HAS_WIFI
    if (WiFi.status() != WL_CONNECTED)
    {
        if (Button(2, 0, "Connect").collidesWith(clickPos))
            AppRender::appOpened = "wifi";

        return;
    }
#endif

    if (currentOnclickHandler != nullptr)
        currentOnclickHandler(clickPos);
}

#endif