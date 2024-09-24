#ifndef DATA_AUTH_HPP
#define DATA_AUTH_HPP

#include "../globals.hpp"
#include "./strings.hpp"
#include "./index.hpp"

namespace auth
{
#define IS_AUTH_BYTE 10

    bool accountExists()
    {
        return readFromEEPROM(HAS_ACCOUNT_ADRESS) == byte(IS_AUTH_BYTE);
    }

    char *getPassword()
    {
        return strings::readStoredString(PASSWORD_ADRESS, 6);
    }

    void createAccount(String *password)
    {
        strings::storeString(PASSWORD_ADRESS, password, 6);
        writeToEEPROM(HAS_ACCOUNT_ADRESS, byte(IS_AUTH_BYTE));
        isLoggedIn = true;
    }

    bool isRightPassword(const char *password)
    {
#if IS_IN_DEBUG_LOGGED_IN
        return true;
#endif
        for (int i = 0; i < 6; i++)
        {
            if (password[i] != readFromEEPROM(PASSWORD_ADRESS + i))
                return false;
        }
        return true;
    }
};

#endif