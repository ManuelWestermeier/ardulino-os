namespace LoginApp
{
    String state;

    void Update()
    {
        SetAppTitle("login", 5);
        char *text = "[password]";
        for (int i = 0; i < 10; i++)
        {
            appScreenData[i + 4][1] = text[i];
        }
    }

    void Scroll(signed char direction)
    {
    }
    void OnClick(Pos clickPos)
    {
        // password button clicked
        if (clickPos.y == 2 && clickPos.x > 3 && clickPos.x < 14)
        {
            CURSOR_OFFSET = 6;
            // right password
            bool isAuth = data::auth::isRightPassword(input::ReadString(DrawKeyBoardMetaData{0, &String("")}));
            if (isAuth)
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
        }
    }
};