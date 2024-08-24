#ifndef APPS_BROWSER_INDEX_HPP
#define APPS_BROWSER_INDEX_HPP

#include "../../utils/structs/pos.hpp"
#include "../../globals.hpp"

namespace BrowserApp
{
    String state;

    void Update()
    {
        SetAppTitle("Browser", 7);
    }

    void Scroll(signed char direction)
    {
    }
    void OnExit()
    {
    }
    void OnClick(Pos clickPos)
    {
    }
};

#endif