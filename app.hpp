namespace AppRender
{
    String appOpened = "home";

    void UpdateCurrentApp()
    {
        if (appOpened == "browser")
        {
            BrowserApp::Update();
        }
        else if (appOpened == "create-account")
        {
            CreateAccountApp::Update();
        }
        else if (appOpened == "login")
        {
            LoginApp::Update();
        }
        else
        {
            HomeApp::Update();
        }
    }

    void UpdateLoop(Pos pos, byte _)
    {
        UpdateCurrentApp();

        lcd.home();
        for (int i = 0; i < 16; i++)
        {
            if (!Cursor::pos.collidesWith({i, 0}))
            {
                lcd.setCursor(i, 0);
                lcd.write(appTitel[i]);
            }
        }
        if (!(Cursor::pos.y == 0 && Cursor::pos.x > 16 && Cursor::pos.x < 20))
        {
            lcd.setCursor(16, 0);
            lcd.print(" - x");
        }
        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 19; x++)
            {
                lcd.setCursor(x, y + 1);
                lcd.write(appScreenData[x][y]);
            }
        }
        lcd.setCursor(19, 1);
        lcd.write(' ');
        lcd.setCursor(19, 2);
        lcd.write('<');
        lcd.setCursor(19, 3);
        lcd.write('>');
    }

    void Update()
    {
        Pos cursorPos = Cursor::Get<byte>(UpdateLoop, 0);
    }
};