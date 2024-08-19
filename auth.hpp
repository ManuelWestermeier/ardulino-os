#ifndef AUTH_HPP
#define AUTH_HPP

#include "./globals.hpp"

#include "./apps/create-account/index.hpp"
#include "./apps/login/index.hpp"

#include "./data/index.hpp"
#include "./app-renderer.hpp"

void Auth()
{
    while (!isLoggedIn)
    {
        if (!data::auth::accountExists())
        {
            CreateAccountApp::Create();
        }
        else
        {
            LoginApp::Update();
            AppRender::Update();
        }
    }
    ClearAppScreen();
}

#endif