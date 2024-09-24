#ifndef APPS_CLOCK_INDEX_HPP
#define APPS_CLOCK_INDEX_HPP

#include "../../utils/structs/pos.hpp"
#include "../../globals.hpp"

enum ClockState
{
    Time,
    Delay,
};

namespace ClockApp
{
    ClockState state = Time;

    void Update()
    {
        SetAppTitle("Clock", 5);
    }

    void Scroll(unsigned char direction)
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