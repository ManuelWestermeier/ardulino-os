#pragma once

#include "../index.hpp"
#include "../../../globals.hpp"
#include "../../../utils/structs/app-state-menager.hpp"
#include "../../../utils/structs/text.hpp"
#include "../../../utils/structs/clickable.hpp"
#include "../../../utils/structs/input.hpp"

// create the elements
Btn tabsButton = Button(0, 2, "tabs");
Btn newTabButton = Button(1, 2, "new tab");
Btn settingsButton = Button(2, 2, "settings");

void BrowserApp::Pages::Home(std::map<String, String>)
{
    ClearAppScreen();
    // render the elements
    tabsButton.Draw();
    newTabButton.Draw();
    settingsButton.Draw();

    // Onclick
    currentOnclickHandler = [&](Pos clickPos) { //
        if (tabsButton.collidesWith(clickPos))
        {
            pages.Navigate({RoutePart("tabs", false)});
        }
        else if (newTabButton.collidesWith(clickPos))
        {
            NewTab();
        }
        else if (settingsButton.collidesWith(clickPos))
        {
            pages.Navigate({RoutePart("settings", false)});
        }
    };
}