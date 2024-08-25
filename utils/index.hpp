#ifndef UTILS_INDEX_HPP
#define UTILS_INDEX_HPP

#include "../globals.hpp"

namespace utils
{
    void waitForRelease()
    {
        while (digitalRead(swPin) != LOW)
            ;
        lcd.clear();
        lcd.setCursor(4, 1);
        lcd.print("release key");
        digitalWrite(LED_BUILTIN, HIGH);
        while (digitalRead(swPin) == LOW)
            ;
        digitalWrite(LED_BUILTIN, LOW);
        lcd.clear();
    }

    void print(int x, int y, char *text, int length)
    {
        for (int i = 0; i < length; i++)
        {
            appScreenData[i + x][y] = text[i];
        }
    }

    void cantExitApp()
    {
        lcd.clear();
        lcd.setCursor(3, 1);
        lcd.print("Can't Exit App");
        delay(2000);
        lcd.clear();
    }

    char *sizeString(char *inp, byte length)
    {
        char out[length];
        for (byte i = 0; i < length; i++)
            out[i] = inp[i];
        return out;
    }

    signed char normalizeJoystick(uint8_t pin)
    {
        int val = analogRead(pin);
        if (val > 700)
            return 1;
        if (val < 300)
            return -1;
        if (val > 1015)
            return 2;
        if (val < 9)
            return -2;
        return 0;
    }
};

#endif