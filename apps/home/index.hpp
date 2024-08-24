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

    String appOptions[4]{
        "Browser",
        "EEPROM Editor",
        "Login",
        "Create Account",
    };

    Select appSelect{appOptions, 4, 0};

    void Update()
    {
        SetAppTitle("Home", 4);
        appSelect.Update();
    }

    void Scroll(signed char direction)
    {
        appSelect.Scroll(direction);
    }

    void OnClick(Pos _)
    {
        int clickedApp = appSelect.OnClick();
        ClearAppScreen();

        if (appOptions[clickedApp] == "Create Account")
        {
            isLoggedIn = false;
            CreateAccountApp::Create();
        }
        else if (appOptions[clickedApp] == "Login")
        {
            isLoggedIn = false;
            Auth();
        }
        else if (appOptions[clickedApp] == "Browser")
        {
            AppRender::appOpened = "browser";
        }
        else if (appOptions[clickedApp] == "EEPROM Editor")
        {
            AppRender::appOpened = "eeprom-editor";
        }
    }

    void Submit()
    {
        OnClick({19, 1});
    }
};

#endif