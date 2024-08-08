namespace auth
{
    bool accountExists()
    {
        return EEPROM.read(HAS_ACCOUNT_ADRESS) == byte(10);
    }

    String *getPassword()
    {
        return strings::readStoredString(PASSWORD_ADRESS, 6);
    }

    void createAccount(String *password)
    {
        strings::storeString(PASSWORD_ADRESS, password, 6);
        EEPROM.write(HAS_ACCOUNT_ADRESS, byte(10));
        isLoggedIn = true;
    }

    bool isRightPassword(String *password)
    {
        return *getPassword() == (*password);
    }
};