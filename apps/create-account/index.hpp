namespace CreateAccountApp
{
    void Update()
    {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("create new account");
        lcd.setCursor(3, 1);
        lcd.print("input password");
        lcd.setCursor(2, 3);
        lcd.print("(press joystick)");
    getPassword:
        utils::waitForRelease();
        lcd.clear();
        lcd.setCursor(5, 1);
        lcd.print("password");
        lcd.setCursor(0, 2);
        lcd.print("(6 characters long)");
        utils::waitForRelease();
        lcd.clear();
        String prompt = "";
        String *password = input::ReadString(DrawKeyBoardMetaData{0, &prompt});
        if (password->length() != 6)
        {
            goto getPassword;
        }
        utils::waitForRelease();
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("rewrite password");
        utils::waitForRelease();
        lcd.clear();
        String *password2 = input::ReadString(DrawKeyBoardMetaData{0, &prompt});
        if (*password != *password2)
        {
            goto getPassword;
        }
        data::auth::createAccount(password);
    }
};