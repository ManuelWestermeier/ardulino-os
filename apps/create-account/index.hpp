namespace CreateAccountApp
{
    void Update()
    {
        // create new account ui
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("create new account");
        lcd.setCursor(3, 1);
        lcd.print("input password");
        lcd.setCursor(2, 3);
        lcd.print("(press joystick)");

        // get the password
    getPassword:
        utils::waitForRelease();
        lcd.setCursor(5, 1);
        lcd.print("password:");
        lcd.setCursor(0, 2);
        lcd.print("(6 characters long)");
        utils::waitForRelease();
        String prompt = "";
        String *password = input::ReadString(DrawKeyBoardMetaData{0, &prompt});
        if (password->length() != 6) // check length
        {
            lcd.clear();
            lcd.setCursor(1, 1);
            lcd.print("Password isn't 6");
            lcd.setCursor(2, 2);
            lcd.print("characters long");
            goto getPassword;
        }
        // rewrite password
        utils::waitForRelease();
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("rewrite password");
        utils::waitForRelease();
        String *password2 = input::ReadString(DrawKeyBoardMetaData{0, &prompt});
        if (*password != *password2) // if they arent the same retry
        {
            lcd.clear();
            lcd.setCursor(1, 1);
            lcd.print("Passwords aren't");
            lcd.setCursor(5, 2);
            lcd.print("the same");
            goto getPassword;
        }
        data::auth::createAccount(password);
    }
};