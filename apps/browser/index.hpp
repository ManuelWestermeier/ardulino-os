#ifndef APPS_BROWSER_INDEX_HPP
#define APPS_BROWSER_INDEX_HPP

#include <functional>
#include "../../utils/structs/pos.hpp"
#include "../../globals.hpp"
#include "../../utils/structs/text.hpp"
#include "../../utils/structs/clickable.hpp"
#include "../../utils/structs/input.hpp"
#include "../../utils/structs/webview-data.hpp"
#include "../../utils/structs/stored-map.hpp"
#include "../../utils/structs/app-state-menager.hpp"

namespace BrowserApp
{
    namespace Pages
    {
        void NoPage(Location loc);
        void Home(std::map<String, String>);
        void BrowserView(std::map<String, String>);
        void Tabs(std::map<String, String>);
    };

    std::function<void(Pos)> currentOnclickHandler = nullptr;

    std::vector<Route> routes = {
        // all routes
        Route({RoutePart("home", false)}, Pages::Home),
        Route({RoutePart("tabs", false)}, Pages::Tabs),
        Route({
                  RoutePart("browser-view", false), // Static "browser-view" as a variable part
                  RoutePart("secure", true),        // Variable for secure/unsecure
                  RoutePart("version", true),       // Variable for version
                  RoutePart("host", true),          // Variable for host
                  RoutePart("port", true),          // Variable for port
                  RoutePart("route", true)          // Variable for route
              },
              Pages::BrowserView // the callback function
              ),
    };

    AppStateManager pages({RoutePart("home")}, routes, Pages::NoPage);

    namespace State
    {
        FlashHashMap webSiteData("web-site-data");
        std::vector<WebviewData> webviews;
    }

    // helpers
    bool WaitForConnected();
    void NewTab();

    // functions
    void Update();
    void Scroll(signed char direction);
    void OnExit();
    void OnClick(Pos clickPos);
    void Submit();
    byte Start(const String &);
};

#include "./pages/no-page.hpp"
#include "./pages/home.hpp"
#include "./pages/tabs.hpp"
#include "./pages/browser-view.hpp"

#include "./update.hpp"
#include "./scroll.hpp"
#include "./submit.hpp"
#include "./start.hpp"
#include "./on-exit.hpp"
#include "./on-click.hpp"

#include "./new-tab.hpp" 

#endif
