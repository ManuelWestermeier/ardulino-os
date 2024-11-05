#ifndef APPS_BROWSER_INDEX_HPP
#define APPS_BROWSER_INDEX_HPP

#include <functional>
#include "../../utils/structs/pos.hpp"
#include "../../globals.hpp"
#include "../../utils/structs/text.hpp"
#include "../../utils/structs/clickable.hpp"
#include "../../utils/structs/input.hpp"
#include "../../utils/structs/stored-map.hpp"
#include "../../utils/structs/app-state-menager.hpp"

namespace BrowserApp
{
    namespace Pages
    {
        void NoPage(Location loc);
        void Home(std::map<std::string, std::string>);
    };

    std::function<void(Pos)> currentOnclickHandler = nullptr;

    std::vector<Route> routes = {
        // all routes
        Route({RoutePart("home")}, Pages::Home),
    };
    AppStateManager pages({RoutePart("home")}, routes, Pages::NoPage);

    namespace State
    {
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

#include "./pages/no-page.hpp"
#include "./pages/home.hpp"

#include "./update.hpp"
#include "./scroll.hpp"
#include "./on-exit.hpp"
#include "./on-click.hpp"

#endif
