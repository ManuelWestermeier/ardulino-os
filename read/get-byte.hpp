#ifndef READ_GET_BYTE_HPP
#define READ_GET_BYTE_HPP

#include "../globals.hpp"
#include "../utils/index.hpp"

uint8_t getByte(char *msg, uint8_t byteNum)
{
    while (digitalRead(swPin) != LOW)
    {
        // new val text
        lcd.setCursor(6, 1);
        lcd.print(msg);
        lcd.setCursor(9, 2);
        // current number
        lcd.print("   ");
        lcd.print(byteNum);
        // char
        lcd.setCursor(7, 2);
        lcd.write(byteNum);
        // increase or decrease bytenum
        byteNum += utils::normalizeJoystick(yPin);
        delay(RENDERING_FRAME);
    }

    while ((digitalRead(swPin) == LOW))
        ;

    return byteNum;
}

#endif