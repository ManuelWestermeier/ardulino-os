#pragma once

#include "../index.hpp"
#include "../../../globals.hpp"
#include "../../../utils/structs/app-state-menager.hpp"
#include "../../../utils/structs/text.hpp"
#include "../../../utils/structs/clickable.hpp"
#include "../../../utils/structs/input.hpp"
#include "../../../utils/structs/select.hpp"
#include "../../../utils/structs/pos.hpp"

Select tabSelect{{}, 0, 0};

void BrowserApp::Pages::Tabs(std::map<String, String>)
{
    ClearAppScreen();

    if (tabSelect.options != nullptr)
        delete[] tabSelect.options;

    tabSelect.optionsLength = State::webviews.size();
    tabSelect.options = new String[tabSelect.optionsLength]();

    for (int i = 0; i < tabSelect.optionsLength; i++)
    {
        tabSelect.options[i] = State::webviews[i].title;
    }

    // Onclick
    currentOnclickHandler = [&](Pos)
    {
        byte clickIndex = tabSelect.OnClick();
        Serial.println(clickIndex);
        if (clickIndex < 0)
            return;
        if (clickIndex > State::webviews.size())
            return;

        MWPL mwpl = State::webviews[clickIndex].mwpl;
        pages.Navigate({
            RoutePart("browser-view", false),           // browser-fiew
            RoutePart(mwpl.secure ? "s" : "us", false), // is secure
            RoutePart(String(mwpl.version), false),     // protocol version
            RoutePart(mwpl.host, false),                // host
            RoutePart(String(mwpl.port), false),        // port
            RoutePart(mwpl.route, false),               // route
        });
    };

    currentOnScrollHandler = [&](signed char direction)
    {
        tabSelect.Scroll(direction);
    };

    tabSelect.Update();
}