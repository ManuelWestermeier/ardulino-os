#ifndef APP_RENDERER_HPP
#define APP_RENDERER_HPP

// globals
#include "./globals.hpp"
#include "./utils/structs/pos.hpp"
#include "./cursor.hpp"
#include "./utils/index.hpp"

namespace AppRender
{
    String appOpened = "home";

    void UpdateCurrentApp();
    void ExitCurrentApp();
    void ClickCurrentApp(Pos *pos);
    void ScrollCurrentApp(signed char direction);
    char GetCursorPosChar();
    void UpdateLoop(Pos pos, byte _);
    void Update();
    void SubmitCurrentApp();
    bool RenderSubmit();
};

// apps
#include "./apps/browser/index.hpp"
#include "./apps/login/index.hpp"
#include "./apps/home/index.hpp"
#include "./apps/eeprom-editor/index.hpp"

bool AppRender::RenderSubmit()
{
    if (appOpened == "home")
        return true;
    if (appOpened == "eeprom-editor")
        return true;
    return false;
}

void AppRender::UpdateCurrentApp()
{
    if (appOpened == "browser")
    {
        BrowserApp::Update();
    }
    else if (appOpened == "login")
    {
        LoginApp::Update();
    }
    else if (appOpened == "eeprom-editor")
    {
        EEPROMEditor::Update();
    }
    else
    {
        HomeApp::Update();
    }
}

void AppRender::ExitCurrentApp()
{
    ClearAppScreen();
    if (!isLoggedIn || appOpened == "login")
    {
        utils::cantExitApp();
    }
    else if (appOpened == "home")
    {
        utils::cantExitApp();
    }
    else if (appOpened == "browser")
    {
        BrowserApp::OnExit();
        appOpened = "home";
    }
    else
    {
        appOpened = "home";
    }
}

void AppRender::ClickCurrentApp(Pos *pos)
{
    if (appOpened == "login" || !isLoggedIn)
    {
        LoginApp::OnClick(*pos);
    }
    else if (appOpened == "browser")
    {
        BrowserApp::OnClick(*pos);
    }
    else if (appOpened == "eeprom-editor")
    {
        EEPROMEditor::OnClick(*pos);
    }

    else
    {
        HomeApp::OnClick(*pos);
    }
}

void AppRender::ScrollCurrentApp(signed char direction)
{
    if (appOpened == "login" || !isLoggedIn)
    {
        LoginApp::Scroll(direction);
    }
    else if (appOpened == "browser")
    {
        BrowserApp::Scroll(direction);
    }
    else if (appOpened == "eeprom-editor")
    {
        EEPROMEditor::Scroll(direction);
    }
    else
    {
        HomeApp::Scroll(direction);
    }
}

void AppRender::SubmitCurrentApp()
{
    if (appOpened == "home")
    {
        HomeApp::Submit();
    }
    else if (appOpened == "eeprom-editor")
    {
        EEPROMEditor::Submit();
    }
}

char AppRender::GetCursorPosChar()
{
    if (Cursor::pos.x < 19 && Cursor::pos.y > 0)
    {
        char charUnderCursor = appScreenData[Cursor::pos.x][Cursor::pos.y - 1];
        if (charUnderCursor == ' ')
            return '-';
        else
            return charUnderCursor;
    }
    if (Cursor::pos.x < 16 && Cursor::pos.y == 0)
    {
        char charUnderCursor = appTitle[Cursor::pos.x];
        if (charUnderCursor == ' ')
            return '-';
        else
            return charUnderCursor;
    }
    if (Cursor::pos.collidesWith({19, 0}))
        return 'x';
    if (Cursor::pos.collidesWith({19, 1}))
        return RenderSubmit() ? confirm_charcode : ' ';
    if (Cursor::pos.collidesWith({19, 2}))
        return upArrowChar;
    if (Cursor::pos.collidesWith({19, 3}))
        return downArrowChar;
    return '-';
}

void AppRender::UpdateLoop(Pos pos, byte _)
{
    // app title
    lcd.home();
    for (int i = 0; i < 16; i++)
    {
        if (!Cursor::pos.collidesWith({i, 0}))
        {
            lcd.setCursor(i, 0);
            lcd.write(appTitle[i]);
        }
    }
    // space aufter title
    if (!Cursor::pos.collidesWith({16, 0}))
    {
        lcd.setCursor(16, 0);
        lcd.write(' ');
    }
    // draw hovered char
    if (!Cursor::pos.collidesWith({17, 0}))
    {
        lcd.setCursor(17, 0);
        lcd.write(GetCursorPosChar());
    }
    // space after hovered char
    if (!Cursor::pos.collidesWith({18, 0}))
    {
        lcd.setCursor(18, 0);
        lcd.write(' ');
    }
    // exit
    if (!Cursor::pos.collidesWith({19, 0}))
    {
        lcd.setCursor(19, 0);
        lcd.write('x');
    }

    // app view
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 19; x++)
        {
            if (!Cursor::pos.collidesWith({x, y + 1}))
            {
                lcd.setCursor(x, y + 1);
                lcd.write(appScreenData[x][y]);
            }
        }
    }

    // scrolls
    lcd.setCursor(19, 1);
    lcd.write(RenderSubmit() ? confirm_charcode : ' ');
    lcd.setCursor(19, 2);
    lcd.write(upArrowChar);
    lcd.setCursor(19, 3);
    lcd.write(downArrowChar);
}

void AppRender::Update()
{
    Pos cursorPos = Cursor::Get<byte>(UpdateLoop, 0);

    // wait for release
    while (digitalRead(swPin) == LOW)
        ;

    // app click
    if (cursorPos.x < 19 && cursorPos.y > 0)
    {
        ClickCurrentApp(&cursorPos);
    }
    // exit
    else if (cursorPos.collidesWith({19, 0}))
    {
        ExitCurrentApp();
    }
    // submit
    else if (cursorPos.collidesWith({19, 1}))
    {
        SubmitCurrentApp();
    }
    // scrolling (up, down)
    else if (cursorPos.collidesWith({19, 2}))
    {
        ScrollCurrentApp(1);
    }
    else if (cursorPos.collidesWith({19, 3}))
    {
        ScrollCurrentApp(-1);
    }
}

#endif