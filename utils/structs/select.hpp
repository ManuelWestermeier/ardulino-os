#ifndef UTILS_STRUCTS_SELECT_HPP
#define UTILS_STRUCTS_SELECT_HPP

#include "../../globals.hpp"
#include "./pos.hpp"

struct Select
{
    String *selections;
    int selectionsLength;
    int pos;

    void Scroll(signed char direction)
    {
        if (direction > 0 && pos < selectionsLength - 1)
            pos++;
        else if (direction < 0 && pos > 0)
            pos--;
    }

    void Update()
    {
        int v = analogRead(yPin);
    }

    int OnClick(byte y)
    {
    }
};

#endif