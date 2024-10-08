#ifndef UTILS_STRUCTS_CLICKABLE_HPP
#define UTILS_STRUCTS_CLICKABLE_HPP

#include "../../globals.hpp"
#include "./pos.hpp"

struct Clickable
{
    byte y;
    byte start;
    byte end;
    char *text;
    byte stringLength;

    void Draw()
    {
        appScreenData[start][y] = '[';

        for (byte i = start + 1; i < end - 1; i++)
        {
            appScreenData[i][y] = i - start - 1 < stringLength ? text[i - start - 1] : ' ';
        }

        appScreenData[end - 1][y] = ']';
    }

    bool collidesWith(const Pos &other) const
    {
        return (other.y - 1) == y && other.x >= start && other.x <= end;
    }
};

#endif