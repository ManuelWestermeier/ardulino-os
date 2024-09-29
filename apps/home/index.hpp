#ifndef APPS_HOME_HPP
#define APPS_HOME_HPP

#include "../../globals.hpp"
#include "../../cursor.hpp"
#include "../../auth.hpp"
#include "../../utils/structs/pos.hpp"
#include "../../utils/structs/select.hpp"
#include "../../app-renderer.hpp"

// apps
#include "../create-account/index.hpp"

namespace HomeApp
{
    String state;

    String appOptions[9] = {
        "Flash Light",
        "Browser",
        "Clock",
        "Wifi",
        "Login",
        "Pin Menager",
        "EEPROM Editor",
        "Memory Editor",
        "Create Account",
    };

    Select appSelect{appOptions, 9, 1};

    void Update()
    {
        SetAppTitle("Home", 4);
        // update select
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
        else if (appOptions[clickedApp] == "Wifi")
        {
            AppRender::appOpened = "wifi";
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
            AppRender::appOpened = "login";
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