#ifndef DATA_STRINGS_HPP
#define DATA_STRINGS_HPP

#include "./index.hpp"

namespace strings
{
  char *readStoredString(int adress, int length)
  {
    char out[length];

    for (int i = 0; i < length; i++)
    {
      out[i] = readFromEEPROM(adress + i);
    }

    return out;
  }

  void writeStringInBuffer(char *buffer, int adress, int length)
  {
    for (int i = 0; i < length; i++)
    {
      buffer[i] = readFromEEPROM(adress + i);
    }
  }

  void storeString(int adress, String *str, int length)
  {
    for (int i = 0; i < length; i++)
    {
      writeToEEPROM(adress + i, str->charAt(i));
    }
  }
};

#endif