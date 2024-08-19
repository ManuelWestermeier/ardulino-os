#ifndef UTILS_STRUCTS_SELECT_HPP
#define UTILS_STRUCTS_SELECT_HPP

#include "../../globals.hpp"

int Select(String *selections, int selectionsLength, int pos = 0)
{
    lcd.clear();
    // loop while the joystick isnt klicked
    while (digitalRead(swPin) != LOW)
    {
        int v = analogRead(yPin);

        // move cursor up and down
        if (v > 900 && pos < selectionsLength)
            pos++;

        if (v < 100 && pos > 0)
            pos--;

        // draw options
        for (int i = 0; i < (4 < selectionsLength ? 4 : selectionsLength); i++)
        {
            for (int charPos = 0; charPos < 18; charPos++)
            {
                lcd.setCursor(charPos + 2, i);
                lcd.write(selections[pos + i].length() > charPos ? selections[i].charAt(i) : ' ');
            }
        }

        lcd.setCursor(0, 1);
        lcd.write('>');

        delay(100);
    }

    // waitb for release
    while (digitalRead(swPin) == LOW)
        ;

    lcd.clear();

    return pos;
}

#endif