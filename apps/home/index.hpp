#ifndef APPS_HOME_HPP
#define APPS_HOME_HPP

#include "../../globals.hpp"
#include "../../auth.hpp"
#include "../../utils/structs/pos.hpp"
#include "../../utils/structs/select.hpp"
#include "../../app-renderer.hpp"

// apps
#include "../create-account/index.hpp"

namespace HomeApp
{
    String state;

    String appOptions[8]{
        "Browser",
        "Flash Light",
        "Clock",
        "Login",
        "Pin Menager",
        "EEPROM Editor",
        "Memory Editor",
        "Create Account",
    };

    Select appSelect{appOptions, 8, 0};

    void Update()
    {
        SetAppTitle("Home", 4);
        appSelect.Update();
    }

    void Scroll(signed char direction)
    {
        appSelect.Scroll(direction);
    }

    void SwitchApp()
    {
        int clickedApp = appSelect.OnClick();
        ClearAppScreen();

        if (appOptions[clickedApp] == "Browser")
        {
            AppRender::appOpened = "browser";
        }
        else if (appOptions[clickedApp] == "Flash Light")
        {
            AppRender::appOpened = "flash-light";
        }
        else if (appOptions[clickedApp] == "Clock")
        {
            AppRender::appOpened = "clock";
        }
        else if (appOptions[clickedApp] == "Pin Menager")
        {
            AppRender::appOpened = "pin-menager";
        }
        else if (appOptions[clickedApp] == "EEPROM Editor")
        {
            AppRender::appOpened = "eeprom-editor";
        }
        else if (appOptions[clickedApp] == "Memory Editor")
        {
            AppRender::appOpened = "memory-editor";
        }
        else if (appOptions[clickedApp] == "Create Account")
        {
            isLoggedIn = false;
            CreateAccountApp::Create();
        }
        else if (appOptions[clickedApp] == "Login")
        {
            isLoggedIn = false;
            Auth();
        }
    }

    void OnClick(Pos)
    {
        SwitchApp();
    }

    void Submit()
    {
        SwitchApp();
    }
};

#endif