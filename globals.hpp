#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "./extern.hpp"
#include "./utils/structs/stored-map.hpp"
#include "./wifi/async-connect.hpp"
#include "./data/characters.hpp"
#include "./time.hpp"

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Max memory pointer
#define MAX_MEM_PTR 2048
#define EEPROM_SIZE 512

// horizontal joystick pin
#define xPin 32
// vertical joystick pin
#define yPin 33
// joystick button pin
#define swPin 4
// LED pin
#define ledPin LED_BUILTIN

// input
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

int CURSOR_OFFSET = 15;

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

void ClearAppScreen()
{

  for (int y = 0; y < 3; y++)
    for (int x = 0; x < 19; x++)
      appScreenData[x][y] = ' ';
}

// auth

bool isLoggedIn = false;

// custum characters
#include "./data/characters.hpp"

int testIndex = 0;
void test(char *title = "")
{
  testIndex++;
  lcd.clear();
  lcd.home();
  lcd.print(title);
  lcd.setCursor(0, 1);
  lcd.print(testIndex);

  Serial.println(title);
  Serial.println(testIndex);
  delay(1000);
}

void InitData()
{
  for (int i = 0; i < 16; i++)
    appTitle[i] = ' ';

  ClearAppScreen();
}

void Init()
{
  // lcd display
  lcd.init();
  lcd.backlight();
  // serial
  Serial.begin(9600);
  Serial.println("Starting");
  // eeprom
  EEPROM.begin(EEPROM_SIZE);
  FlashHashMap::begin();
  // create characters
  lcd.createChar(cursor_charcode, cursorChar[0]);
  lcd.createChar(confirm_charcode, confirmChar);
  lcd.createChar(upArrowChar, upArrow);
  lcd.createChar(downArrowChar, downArrow);
  // pin modes
  pinMode(swPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  // init screen data
  InitData();
  AsyncWifiConnect();

  Time::Init();
}

#endif