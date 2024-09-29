#ifndef UTILS_STRUCTS_SELECT_HPP
#define UTILS_STRUCTS_SELECT_HPP

#include "../../globals.hpp"
#include "../../cursor.hpp"

#include "./pos.hpp"

struct Select
{
    String *options;
    byte optionsLength;
    byte pos;

    void Scroll(signed char direction)
    {
        if (direction < 0 && pos + 1 < optionsLength - 1 && pos - 1 < optionsLength - 1)
            pos++;
        else if (direction > 0 && pos + 1 > 0 && pos - 1 > 0)
            pos--;
    }

    byte cursorPos = 1;
    void Update()
    {
        // set the cursor pos only if the cursor is on screen data 0-3
        cursorPos = Cursor::pos.y == 0 || Cursor::pos.x == 19 ? cursorPos : Cursor::pos.y - 1;
        // add the select
        appScreenData[0][0] = ' ';
        appScreenData[0][1] = ' ';
        appScreenData[0][2] = ' ';
        // set the pointer
        appScreenData[0][cursorPos] = '>';

        // draw the options
        for (int optionIndex = 0; optionIndex < 3; optionIndex++)
        {
            for (int charIndex = 0; charIndex < 18; charIndex++)
            {
                byte optionPos = optionIndex + pos - 1;

                bool isOutOfOptionBound = optionPos < 0 || optionPos > optionsLength - 1;
                bool charIsntInStringBounds = options[optionPos].length() < charIndex + 1;

                if (isOutOfOptionBound || charIsntInStringBounds)
                {
                    appScreenData[charIndex + 1][optionIndex] = ' ';
                }
                else
                {
                    appScreenData[charIndex + 1][optionIndex] = options[optionPos].charAt(charIndex);
                }
            }
        }
    }

    byte OnClick()
    {
        byte returnPos = pos + cursorPos - 1;

        if (returnPos < 0 || returnPos > optionsLength - 1)
            return -1;

        return returnPos;
    }
};

#endif