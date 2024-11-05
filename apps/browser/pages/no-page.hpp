#pragma once

#include "../index.hpp"
#include "../../../utils/structs/app-state-menager.hpp"
#include "../../../utils/structs/text.hpp"
#include "../../../utils/structs/clickable.hpp"

void BrowserApp::Pages::NoPage(Location loc)
{
    Text(1, 1, "Page Not Found").Draw();
    Button(2, 0, "Home").Draw();
    currentOnclickHandler = ([](Pos clickPos) { //
        if (Button(2, 0, "Home").collidesWith(clickPos))
            pages.Navigate({RoutePart("home")});
    });
}