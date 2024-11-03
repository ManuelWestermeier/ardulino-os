#ifndef INIT_HPP
#define INIT_HPP

#include "./globals.hpp"

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
    // init the time
    Time::Init();
    // init home app (get home links from fs...)
    HomeApp::Init();
}

#endif