#ifndef UTILS_STRUCTS_CLICKABLE_HPP
#define UTILS_STRUCTS_CLICKABLE_HPP

#include "../../ardulino-os/globals.hpp"
#include "./pos.hpp"

struct Clickable
{
    int y;
    int start;
    int end;
    char *text;
    int stringLength;

    void Draw()
    {
        appScreenData[start][y] = '[';

        for (int i = start + 1; i < end - 1; i++)
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