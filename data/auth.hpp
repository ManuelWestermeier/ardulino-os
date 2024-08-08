namespace auth
{
    bool accountExists()
    {
        return EEPROM.read(0) == 1;
    }

    String *getPassword()
    {
        return strings::readStoredString(1, 6);
    }

    void createAccount(String *password)
    {
        strings::storeString(1, password, 6);
        EEPROM.write(0, 1);
        isLoggedIn = true;
    }

    bool isRightPassword(String *password)
    {
        return *getPassword() == (*password);
    }
};