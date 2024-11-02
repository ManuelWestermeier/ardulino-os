#ifndef APP_RENDERER_HPP
#define APP_RENDERER_HPP

#include <map>
#include "./globals.hpp"
#include "./utils/structs/pos.hpp"
#include "./cursor.hpp"
#include "./utils/index.hpp"

namespace AppRender
{
    String appOpened = "home";

    void UpdateView();
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

struct AppPrototype
{
    String name;
    byte (*Start)(const String &) = nullptr;
    void (*Update)() = nullptr;
    void (*Scroll)(signed char direction) = nullptr;
    void (*OnExit)() = nullptr;
    void (*OnClick)(Pos clickPos) = nullptr;
    void (*Submit)() = nullptr;
};

std::map<String, AppPrototype> registeredApps;

void RegisterApp(AppPrototype app)
{
    registeredApps[app.name] = app;
}

#include "./init-apps.hpp"

bool AppRender::RenderSubmit()
{
    return registeredApps[appOpened].Submit != nullptr;
}

void AppRender::UpdateCurrentApp()
{
    if (!isLoggedIn)
    {
        LoginApp::Update();
        return;
    }

    if (registeredApps[appOpened].Update)
    {
        registeredApps[appOpened].Update();
    }
}

void AppRender::ExitCurrentApp()
{
    ClearAppScreen();
    if (!isLoggedIn || appOpened == "login")
    {
        utils::cantExitApp();
        return;
    }

    if (registeredApps[appOpened].OnExit)
    {
        registeredApps[appOpened].OnExit();
    }

    if (appOpened == "home")
    {
        isLoggedIn = false;
        Auth();
    }
    else
    {
        appOpened = "home";
    }
}

void AppRender::ClickCurrentApp(Pos *pos)
{
    if (!isLoggedIn)
    {
        LoginApp::OnClick(*pos);
        return;
    }

    if (registeredApps[appOpened].OnClick)
    {
        registeredApps[appOpened].OnClick(*pos);
    }
}

void AppRender::ScrollCurrentApp(signed char direction)
{
    if (!isLoggedIn)
    {
        LoginApp::Scroll(direction);
        return;
    }

    if (registeredApps[appOpened].Scroll)
    {
        registeredApps[appOpened].Scroll(direction);
    }
}

void AppRender::SubmitCurrentApp()
{
    if (registeredApps[appOpened].Submit)
    {
        registeredApps[appOpened].Submit();
    }
}

char AppRender::GetCursorPosChar()
{
    if (Cursor::pos.x < 19 && Cursor::pos.y > 0)
    {
        char charUnderCursor = appScreenData[Cursor::pos.x][Cursor::pos.y - 1];
        return charUnderCursor == ' ' ? '-' : charUnderCursor;
    }
    if (Cursor::pos.x < 16 && Cursor::pos.y == 0)
    {
        char charUnderCursor = appTitle[Cursor::pos.x];
        return charUnderCursor == ' ' ? '-' : charUnderCursor;
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

void AppRender::UpdateView()
{
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
}

void AppRender::UpdateLoop(Pos pos, byte)
{
    UpdateCurrentApp();
    lcd.home();
    for (int i = 0; i < 16; i++)
    {
        if (!Cursor::pos.collidesWith({i, 0}))
        {
            lcd.setCursor(i, 0);
            lcd.write(appTitle[i]);
        }
    }
    if (!Cursor::pos.collidesWith({16, 0}))
        lcd.setCursor(16, 0), lcd.write(' ');
    if (!Cursor::pos.collidesWith({17, 0}))
        lcd.setCursor(17, 0), lcd.write(GetCursorPosChar());
    if (!Cursor::pos.collidesWith({18, 0}))
        lcd.setCursor(18, 0), lcd.write(' ');
    if (!Cursor::pos.collidesWith({19, 0}))
        lcd.setCursor(19, 0), lcd.write('x');

    UpdateView();
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
    while (digitalRead(swPin) == LOW)
        ;

    if (cursorPos.x < 19 && cursorPos.y > 0)
    {
        ClickCurrentApp(&cursorPos);
    }
    else if (cursorPos.collidesWith({19, 0}))
    {
        ExitCurrentApp();
    }
    else if (cursorPos.collidesWith({19, 1}))
    {
        SubmitCurrentApp();
    }
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