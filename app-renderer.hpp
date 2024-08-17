namespace AppRender
{
    String appOpened = "home";
    String lastRenderingApp = appOpened;

    void UpdateCurrentApp()
    {
        if (appOpened == "browser")
        {
            BrowserApp::Update();
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

    void ExitCurrentApp()
    {
        if (!isLoggedIn)
        {
            lcd.clear();
            lcd.setCursor(3, 1);
            lcd.print("Can't Exit App");
            delay(2000);
            lcd.clear();
            return;
        }

        if (appOpened == "browser")
        {
            BrowserApp::OnExit();
            appOpened = "home";
        }
    }

    void ClickCurrentApp(Pos *pos)
    {
        if (appOpened == "login" || !isLoggedIn)
        {
            LoginApp::OnClick(*pos);
        }
        else if (appOpened == "browser")
        {
            BrowserApp::OnClick(*pos);
        }
        else
        {
            HomeApp::OnClick(*pos);
        }
    }

    void ScrollCurrentApp(signed char direction)
    {
        if (appOpened == "browser")
        {
            BrowserApp::Scroll(direction);
        }
        else if (appOpened == "login")
        {
            LoginApp::Scroll(direction);
        }
    }

    char GetCursorPosChar()
    {
        if (Cursor::pos.x < 19 && Cursor::pos.y > 0)
        {
            char charUnderCursor = appScreenData[Cursor::pos.x][Cursor::pos.y - 1];
            if (charUnderCursor == ' ')
                return '-';
            else
                return charUnderCursor;
        }
        if (Cursor::pos.x < 16 && Cursor::pos.y == 0)
        {
            char charUnderCursor = appTitle[Cursor::pos.x];
            if (charUnderCursor == ' ')
                return '-';
            else
                return charUnderCursor;
        }
        if (Cursor::pos.collidesWith({19, 0}))
            return 'x';
        if (Cursor::pos.collidesWith({19, 2}))
            return '<';
        if (Cursor::pos.collidesWith({19, 3}))
            return '>';
        return '-';
    }

    void UpdateLoop(Pos pos, byte _)
    {
        if (lastRenderingApp != appOpened)
            ClearAppScreen();

        lastRenderingApp = appOpened;

        // app title
        lcd.home();
        for (int i = 0; i < 16; i++)
        {
            if (!Cursor::pos.collidesWith({i, 0}))
            {
                lcd.setCursor(i, 0);
                lcd.write(appTitle[i]);
            }
        }
        // space aufter title
        if (!Cursor::pos.collidesWith({16, 0}))
        {
            lcd.setCursor(16, 0);
            lcd.write(' ');
        }
        // draw hovered char
        if (!Cursor::pos.collidesWith({17, 0}))
        {
            lcd.setCursor(17, 0);
            lcd.write(GetCursorPosChar());
        }
        // space after hovered char
        if (!Cursor::pos.collidesWith({18, 0}))
        {
            lcd.setCursor(18, 0);
            lcd.write(' ');
        }
        // exit
        if (!Cursor::pos.collidesWith({19, 0}))
        {
            lcd.setCursor(19, 0);
            lcd.write('x');
        }

        // app view
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

        // scrolls
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

        // wait for release
        while (digitalRead(swPin) == LOW)
            ;

        // app click
        if (cursorPos.x < 19 && cursorPos.y > 0)
        {
            ClickCurrentApp(&cursorPos);
        }
        // exit
        else if (cursorPos.collidesWith({19, 0}))
        {
            ExitCurrentApp();
        }
        // scrolling (up, down)
        else if (cursorPos.collidesWith({19, 2}))
        {
            ScrollCurrentApp(1);
        }
        else if (cursorPos.collidesWith({19, 3}))
        {
            ScrollCurrentApp(-1);
        }
    }
};