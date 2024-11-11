#pragma once

#include "../index.hpp"
#include "../../../globals.hpp"
#include "../../../utils/structs/app-state-menager.hpp"
#include "../../../utils/structs/text.hpp"
#include "../../../utils/structs/clickable.hpp"
#include "../../../utils/structs/input.hpp"

void BrowserApp::Pages::BrowserView(std::map<String, String>)
{
    ClearAppScreen();
    

    Text(1, 1, "Browser View").Draw();
}