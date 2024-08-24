#ifndef APPS_EEPROM_EDITOR_INDEX_HPP
#define APPS_EEPROM_EDITOR_INDEX_HPP

#include "../../utils/structs/pos.hpp"
#include "../../globals.hpp"
#include "../../data/index.hpp"

namespace EEPROMEditor
{
    int pos = 98;

    void Scroll(signed char direction)
    {
        if (direction > 0 && pos < 512)
        {
            pos++;
        }
        else if (direction < 0 && pos > 0)
        {
            pos--;
        }
    }

    void Update()
    {
        SetAppTitle("EEPROM Editor", 13);

        // render the data on the top line
        for (int i = 0; i < 19; i++)
        {
            int readPos = pos + i - 10;

            if (readPos < 0 || readPos > 512)
            {
                appScreenData[i][1] = ' ';
                continue;
            }

            appScreenData[i][1] = EEPROM.read(readPos);
        }

        // cursor
        appScreenData[10][2] = '^';

        // clear number digits
        appScreenData[9][0] = ' ';
        appScreenData[10][0] = ' ';
        appScreenData[11][0] = ' ';
        // Render pos number
        if (pos < 10)
        {
            appScreenData[11][0] = 48 + pos;
        }
        else if (pos < 100)
        {
            appScreenData[10][0] = 48 + (pos / 10); // Tens place
            appScreenData[11][0] = 48 + (pos % 10); // Units place
        }
        else if (pos < 1000)
        {
            appScreenData[9][0] = 48 + ((pos / 100));      // Hundreds place
            appScreenData[10][0] = 48 + ((pos / 10) % 10); // Tens place
            appScreenData[11][0] = 48 + (pos % 10);        // Units place
        }
    }

    void OnClick(Pos pos)
    {
    }
};

#endif