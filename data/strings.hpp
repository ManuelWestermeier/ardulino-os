namespace strings
{
  String *readStoredString(int adress, int length)
  {
    String out;

    for (int i = 0; i < length; i++)
    {
      out += EEPROM.read(adress + i);
    }

    return &out;
  }

  void storeString(int adress, String *str, int length)
  {
    for (int i = 0; i < length; i++)
    {
      EEPROM.write(adress + i, str->charAt(i));
    }
  }
};