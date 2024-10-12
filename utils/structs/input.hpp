#ifndef UTILS_STRUCTS_INPUT_HPP
#define UTILS_STRUCTS_INPUT_HPP

#include "./../../globals.hpp"
#include "./../../read/index.hpp"
#include "./../../utils/index.hpp"

struct Input
{
    byte y;
    byte start;        // Start position (X coordinate) of the input field
    byte end;          // End position (X coordinate) of the input field
    char *placeholder; // Placeholder text when the input is empty
    String value;      // User input value

    // Constructor to initialize the input field
    Input(byte _y, byte _start, byte _end, const char *_placeholder, String _value = "")
    {
        y = _y;
        start = _start;
        end = _end;
        placeholder = new char[strlen(_placeholder) + 1];
        strcpy(placeholder, _placeholder);
        value = _value;
    }

    // Draw the input field
    void Draw()
    {
        String toDisplay = value.isEmpty() ? String(placeholder) : value;

        // Adjust the size of the string based on available space between start and end
        toDisplay = utils::setStringSize(toDisplay, end - start - 2);

        // Draw the input field with <value> markers
        appScreenData[start][y] = '<';
        for (byte i = start + 1; i < end - 1; i++)
        {
            appScreenData[i][y] = i - start - 1 < toDisplay.length() ? toDisplay[i - start - 1] : ' ';
        }
        appScreenData[end - 1][y] = '>';
    }

    // Handle clicks, directly open input for typing
    void OnClick(const Pos &clickPosition)
    {
        if (clickPosition.y - 1 == y && clickPosition.x >= start && clickPosition.x <= end)
        {
            // Open the input method and update the value
            value = *input::ReadString(DrawKeyBoardMetaData{value.length(), &value});
        }
    }
};

#endif
