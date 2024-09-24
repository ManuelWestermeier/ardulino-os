#ifndef DATA_INDEX_HPP
#define DATA_INDEX_HPP

namespace data
{
    void writeToEEPROM(int address, byte value)
    {
        EEPROM.write(address, value);
        EEPROM.commit();
    }

    byte readFromEEPROM(int address)
    {
        return EEPROM.read(address);
    }

#include "./strings.hpp"
#include "./auth.hpp"
};

#endif