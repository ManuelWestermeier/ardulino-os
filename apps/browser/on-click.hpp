#ifndef APPS_BROWSER_ON_CLICK_HPP
#define APPS_BROWSER_ON_CLICK_HPP

#include "../../globals.hpp"
#include "../../app-renderer.hpp"
#include "../../utils/structs/pos.hpp"
#include "./index.hpp"

void BrowserApp::OnClick(Pos clickPos)
{
    if (WiFi.status() != WL_CONNECTED) // Fixed typo here
    {
        if (Button(2, 0, "Connect").collidesWith(clickPos))
            AppRender::appOpened = "wifi";

        return;
    }

    if (currentOnclickHandler != nullptr)
        currentOnclickHandler(clickPos);
}

#endif