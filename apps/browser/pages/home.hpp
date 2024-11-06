#pragma once

#include "../index.hpp"
#include "../../../globals.hpp"
#include "../../../utils/structs/app-state-menager.hpp"
#include "../../../utils/structs/text.hpp"
#include "../../../utils/structs/clickable.hpp"
#include "../../../utils/structs/input.hpp"

// create the elements
Input goToViewInput(0, 0, 19, "website ip:port...", "192.168.178.33");
Btn openTabsButton = Button(1, 2, "tabs");
Btn openTabButton = Button(2, 2, "open tab");

void BrowserApp::Pages::Home(std::map<std::string, std::string>)
{
    ClearAppScreen();
    // render the elements
    openTabsButton.Draw();
    openTabButton.Draw();
    goToViewInput.Draw();

    // Onclick
    currentOnclickHandler = [&](Pos clickPos) { //
        goToViewInput.OnClick(clickPos);
    };
}