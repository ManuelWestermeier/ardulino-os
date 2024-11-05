#pragma once

#include "../index.hpp"
#include "../../../utils/structs/app-state-menager.hpp"
#include "../../../utils/structs/text.hpp"
#include "../../../utils/structs/clickable.hpp"
#include "../../../utils/structs/input.hpp"

void BrowserApp::Pages::Home(std::map<std::string, std::string>)
{
    Input goToViewInput(1, 0, 19, "website ip:port...", "192.168.178.33");
    // With Internet
    currentOnclickHandler = [&](Pos clickPos) { //
        goToViewInput.OnClick(clickPos);
    };
}