#ifndef UTILS_STRUCTS_TEXT_HPP
#define UTILS_STRUCTS_TEXT_HPP

#include "../../globals.hpp"
#include "./pos.hpp"

struct Text
{
    byte y;
    byte x;
    String text;

    Text(byte _y, byte _x, String _text)
    {
        y = _y;
        x = _x;
        text = _text;
    }

    void Draw()
    {
        for (byte i = 0; i < x + text.length() - 1; i++)
        {
            appScreenData[i + x][y] = text.charAt(i);
        }
    }

    bool collidesWith(const Pos &other) const
    {
        return (other.y - 1) == y && other.x >= x && other.x <= x + text.length() - 1;
    }
};

#endif