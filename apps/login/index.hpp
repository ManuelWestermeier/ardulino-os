#ifndef APPS_LOGIN_HPP
#define APPS_LOGIN_HPP

#include "../../globals.hpp"
#include "../../config.hpp"
#include "../../read/index.hpp"
#include "../../utils/structs/pos.hpp"
#include "../../utils/structs/clickable.hpp"
#include "../create-account/index.hpp"

namespace LoginApp
{
    String state;
    bool createAccountPage = false;
    Clickable passwordInput{1, 5, 15, "password", 8};
    Clickable createNewAccountButton{2, 3, 16, "new account", 11};

    void Update()
    {
        SetAppTitle("login", 5);

        if (createAccountPage)
        {
            for (int i = 0; i < 10; i++)
            {
                appScreenData[i + 5][0] = ("You forgot")[i];
            }
            for (int i = 0; i < 15; i++)
            {
                appScreenData[i + 2][1] = ("your password?!")[i];
            }
            createNewAccountButton.Draw();
        }
        else
        {
            passwordInput.Draw();
        }
    }

    void Scroll(signed char direction)
    {
        ClearAppScreen();
        createAccountPage = !createAccountPage;
    }

    void CheckPasswordInputClickedAndLogin(Pos clickPos)
    {
        // password button clicked
        if (passwordInput.collidesWith(clickPos))
        {
            CURSOR_OFFSET = 6;
            String *defaultInputStringPtr = new String("");
// no password in debug mode
#if IS_IN_DEBUG_LOGGED_IN
            if (true)
#else
            // get password input
            auto result = input::ReadString(DrawKeyBoardMetaData{0, defaultInputStringPtr})->c_str();
            // is right password
            if (data::auth::isRightPassword(result))
#endif
            {
                isLoggedIn = true;
                lcd.clear();
                lcd.setCursor(5, 1);
                lcd.print("Logged in");
                delay(1000);
                lcd.clear();
            }
            else
            {
                lcd.clear();
                lcd.setCursor(3, 1);
                lcd.print("wrong password");
                delay(1000);
                lcd.clear();
            }

            delete defaultInputStringPtr;
        }
    }

    void CheckChangePasswordButton(Pos clickPos)
    {
        // password button clicked
        if (createNewAccountButton.collidesWith(clickPos))
        {
            CreateAccountApp::Create();
        }
    }

    void OnClick(Pos clickPos)
    {
        if (createAccountPage)
            CheckChangePasswordButton(clickPos);
        else
            CheckPasswordInputClickedAndLogin(clickPos);
    }
};

#endif