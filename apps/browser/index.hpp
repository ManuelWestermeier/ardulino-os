#ifndef APPS_BROWSER_INDEX_HPP
#define APPS_BROWSER_INDEX_HPP

#include "../../utils/structs/pos.hpp"
#include "../../globals.hpp"
#include "../../utils/structs/text.hpp"
#include "../../utils/structs/clickable.hpp"
#include "../../utils/structs/stored-map.hpp"

namespace BrowserApp
{
    Text noWifiText(1, 1, "No Wifi");
    Btn connectToWfifButton = Button(2, 0, "Connect");

    namespace State
    {
        bool isOnHomePage = true;
        bool isOnWebSite = true;
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