#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

//Max memory pointer
#define MAX_MEM_PTR 2048
#define ESPROM_SIZE 512

// horizontal joystick pin
#define xPin 32
// vertical joystick pin
#define yPin 33
// joystick button pin
#define swPin 4
// LED pin
#define ledPin LED_BUILTIN

// input
#define cursor_charcode 0
#define confirm_charcode 1
#define upArrowChar 2
#define downArrowChar 3
#define RENDERING_FRAME 100

#define GET_CHAR_NO_CHAR 0
#define GET_CHAR_LEFT_SHIFT 1
#define GET_CHAR_RIGHT_SHIFT 2
#define GET_CHAR_SUBMIT 3
#define GET_CHAR_BACKSPACE 4
#define GET_CHAR_DELETE_ALL 5

String keyBoardLayout[2] = {
  "abcdefghij0123456789",
  "klmnopqrstuvwxyz .?!"
};

int CURSOR_OFFSET = 15;

// storage

#define HAS_ACCOUNT_ADRESS 0
#define PASSWORD_ADRESS 1

// app

char appScreenData[19][3];
char appTitle[16];

void SetAppTitle(char *title, int length) {
  for (int i = 0; i < 16; i++) {
    if (i < length)
      appTitle[i] = title[i];
    else
      appTitle[i] = ' ';
  }
}

void ClearAppScreen() {

  for (int y = 0; y < 3; y++)
    for (int x = 0; x < 19; x++)
      appScreenData[x][y] = ' ';
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

int testIndex = 0;
void test() {
  testIndex++;
  lcd.clear();
  lcd.home();
  lcd.print(testIndex);
  delay(1000);
}

void InitData() {
  for (int i = 0; i < 16; i++)
    appTitle[i] = ' ';

  ClearAppScreen();
}

void Init() {
  //lcd display
  lcd.init();
  lcd.backlight();
  //serial
  Serial.begin(9600);
  Serial.println("Starting");
  //eeprom
  EEPROM.begin(ESPROM_SIZE);
  //create characters
  lcd.createChar(cursor_charcode, cursorChar[0]);
  lcd.createChar(confirm_charcode, confirmChar);
  lcd.createChar(upArrowChar, upArrow);
  lcd.createChar(downArrowChar, downArrow);
  //pin modes
  pinMode(swPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  //init screen data
  InitData();
}

#endif