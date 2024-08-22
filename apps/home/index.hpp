#ifndef APPS_HOME_HPP
#define APPS_HOME_HPP

#include "../../globals.hpp"
#include "../../utils/structs/pos.hpp"
#include "../../utils/structs/select.hpp"
#include "../../app-renderer.hpp"

// apps
#include "../create-account/index.hpp"

namespace HomeApp
{
    String state;

    String appOptions[3]{
        "Browser",
        "Login",
        "Create Account",
    };

    Select appSelect{appOptions, 3, 0};

    void Update()
    {
        SetAppTitle("Home", 4);
        appSelect.Update();
    }

    void Scroll(signed char direction)
    {
        appSelect.Scroll(direction);
    }

    void OnClick(Pos clickPos)
    {
        int clickedApp = appSelect.OnClick(clickPos.y);

        if (clickedApp == -1)
            return;

        if (appOptions[clickedApp] == "Create Account")
            return CreateAccountApp::Create();

        appOptions[clickedApp].toLowerCase();
        AppRender::appOpened = appOptions[clickedApp];
    }
};

#endif