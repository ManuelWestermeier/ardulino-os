void Auth()
{
    while (!isLoggedIn)
    {
        if (!data::auth::accountExists())
        {
            CreateAccountApp::Update();
        }
        else
        {
            LoginApp::Update();
            AppRender::Update();
        }
    }
}