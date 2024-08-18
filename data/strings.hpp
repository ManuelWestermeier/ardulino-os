namespace strings
{
  char *readStoredString(int adress, int length)
  {
    char out[length];

    for (int i = 0; i < length; i++)
    {
      out[i] = EEPROM.read(adress + i);
    }

    return out;
  }

  void storeString(int adress, String *str, int length)
  {
    for (int i = 0; i < length; i++)
    {
      EEPROM.write(adress + i, str->charAt(i));
    }
  }
};