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

#define cursor_charcode 0
#define confirm_charcode 1
#define RENDERING_FRAME 100

#define GET_CHAR_NO_CHAR 0
#define GET_CHAR_LEFT_SHIFT 1
#define GET_CHAR_RIGHT_SHIFT 2
#define GET_CHAR_SUBMIT 3
#define GET_CHAR_BACKSPACE 4
#define GET_CHAR_DELETE_ALL 5

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
  }
};

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