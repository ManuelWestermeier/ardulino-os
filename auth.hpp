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