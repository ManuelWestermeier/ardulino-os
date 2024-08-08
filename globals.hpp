#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// horizontal joystick pin
#define xPin A0
// vertical joystick pin
#define yPin A1
// joystick button pin
#define swPin 2
// Push-Button pin
#define buttonPin 3
// LED pin
#define ledPin 9

// input

#define cursor_charcode 0
#define confirm_charcode 1
#define RENDERING_FRAME 100

#define GET_CHAR_NO_CHAR 0
#define GET_CHAR_LEFT_SHIFT 1
#define GET_CHAR_RIGHT_SHIFT 2
#define GET_CHAR_SUBMIT 3
#define GET_CHAR_BACKSPACE 4
#define GET_CHAR_DELETE_ALL 5

String keyBoardLayout[2] = {
    "abcdefghij0123456789",
    "klmnopqrstuvwxyz .?!"};

// storage

#define HAS_ACCOUNT_ADRESS 0
#define PASSWORD_ADRESS 1

// app

char appScreenData[19][3];
char appTitle[16];

void SetAppTitle(char *title, int length)
{
    for (int i = 0; i < 16; i++)
    {
        if (i < length)
            appTitle[i] = title[i];
        else
            appTitle[i] = ' ';
    }
}

// auth

bool isLoggedIn = false;

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

void InitData()
{
    for (int i = 0; i < 16; i++)
        appTitle[i] = ' ';

    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 19; x++)
            appScreenData[x][y] = ' ';
}