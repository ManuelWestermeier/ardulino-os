#ifndef APPS_CLOCK_INDEX_HPP
#define APPS_CLOCK_INDEX_HPP

#include "../../utils/structs/pos.hpp"
#include "../../globals.hpp"
#include "../../time.hpp"

namespace ClockApp
{
    void Update()
    {
        SetAppTitle("Clock", 5);
    }

    void Scroll(signed char direction)
    {
    }

    void OnClick(Pos clickPos)
    {
    }

    void Submit()
    {
    }
};

#endif