#ifndef APPS_BROWSER_INDEX_HPP
#define APPS_BROWSER_INDEX_HPP

#include "../../utils/structs/pos.hpp"
#include "../../globals.hpp"

namespace BrowserApp
{
    namespace State
    {

    }

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