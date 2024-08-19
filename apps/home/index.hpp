#ifndef APPS_HOME_HPP
#define APPS_HOME_HPP

#include "../../globals.hpp"
#include "../../utils/structs/pos.hpp"

namespace HomeApp
{
    String state;

    void Update()
    {
        SetAppTitle("Home", 4);
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