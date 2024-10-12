#ifndef APPS_BROWSER_INDEX_HPP
#define APPS_BROWSER_INDEX_HPP

#include "../../utils/structs/pos.hpp"
#include "../../globals.hpp"
#include "../../utils/structs/text.hpp"
#include "../../utils/structs/clickable.hpp"
#include "../../utils/structs/input.hpp"
#include "../../utils/structs/stored-map.hpp"

enum AppPage {
    Home,
    Settings,
    Search,
    History,
    Bookmarks,
};

namespace BrowserApp
{
    Text noWifiText(1, 1, "No Wifi");
    Btn connectToWifiButton = Button(2, 0, "Connect");  // Fixed typo here
    Input goToViewInput(1, 0, 19, "website ip:port...");

    namespace State
    {
        AppPage appPage = Home;  // Use 'appPage' not 'appState'
        String currentWebsite = "";
        FlashHashMap webSiteData("web-site-data");
    }

    // helpers
    bool WaitForConnected();

    // functions
    void Update();
    void Scroll(signed char direction);
    void OnExit();
    void OnClick(Pos clickPos);
};

#include "./update.hpp"
#include "./scroll.hpp"
#include "./on-exit.hpp"
#include "./on-click.hpp"

#endif
