#ifndef DATA_CHARACTERS_HPP
#define DATA_CHARACTERS_HPP

// predefined character codes
#define cursor_charcode 0
#define confirm_charcode 1
#define upArrowChar 2
#define downArrowChar 3

// custum characters
uint8_t cursorChar[2][8] = {
    {
        B00000,
        B00100,
        B01110,
        B11111,
        B00100,
        B00100,
        B00100,
        B00000,
    },
    {
        B00000,
        B00100,
        B01110,
        B10101,
        B00100,
        B00100,
        B00100,
        B00000,
    }};

uint8_t confirmChar[8] = {
    B00000,
    B00001,
    B00001,
    B00010,
    B00010,
    B10100,
    B01100,
    B00000,
};

// Define custom characters for up and down arrows
byte upArrow[8] = {
    B00000,
    B00100,
    B01010,
    B10001,
    B00000,
    B00000,
    B00000,
    B00000,
};

byte downArrow[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B10001,
    B01010,
    B00100,
    B00000,
};

#endif