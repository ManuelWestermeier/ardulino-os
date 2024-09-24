#ifndef READ_GET_BYTE_HPP
#define READ_GET_BYTE_HPP

#include "../globals.hpp"
#include "../utils/index.hpp"

unsigned char getByte(char *msg, unsigned char byteNum, int msgPos = 6)
{
    lcd.clear();
    while (digitalRead(swPin) != LOW)
    {
        // new val text
        lcd.setCursor(msgPos, 1);
        lcd.print(msg);
        lcd.setCursor(9, 2);
        // current number
        lcd.print("   ");
        lcd.print(byteNum);
        // char
        lcd.setCursor(7, 2);
        lcd.write(byteNum);
        // increase or decrease bytenum
        auto verticalJoystick = utils::normalizeJoystick(yPin);
        //no positive overflow
        if ((byteNum == 253 && verticalJoystick == 2) || (byteNum == 254 && verticalJoystick == 1))
        {
            byteNum = 0;
        }
        //no negative overflow
        if ((byteNum == 3 && verticalJoystick == -2) || (byteNum == 2 && verticalJoystick == -1))
        {
            byteNum = 255;
        }
        else
        {
            byteNum += verticalJoystick;
        }

        delay(RENDERING_FRAME);
    }

    while ((digitalRead(swPin) == LOW))
        ;
    lcd.clear();
    return byteNum;
}

#endif