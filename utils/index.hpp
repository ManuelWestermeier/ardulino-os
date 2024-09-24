#ifndef UTILS_INDEX_HPP
#define UTILS_INDEX_HPP

#include "../globals.hpp"

namespace utils
{
  void waitForRelease()
  {
    while (digitalRead(swPin) != LOW)
      ;
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print("release key");
    digitalWrite(LED_BUILTIN, HIGH);
    while (digitalRead(swPin) == LOW)
      ;
    digitalWrite(LED_BUILTIN, LOW);
    lcd.clear();
  }

  void print(int x, int y, char *text, int length)
  {
    for (int i = 0; i < length; i++)
    {
      appScreenData[i + x][y] = text[i];
    }
  }

  void cantExitApp()
  {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("Can't Exit App");
    delay(2000);
    lcd.clear();
  }

  char *sizeString(char *inp, byte length)
  {
    char out[length];
    for (byte i = 0; i < length; i++)
      out[i] = inp[i];
    return out;
  }

  int8_t normalizeJoystick(uint8_t pin)
  {
    int val = analogRead(pin);
    if (val > 4090) // Close to the maximum for a 12-bit ADC
      return 2;
    if (val < 5) // Close to the minimum
      return -2;
    if (val > 3500) // Close to the upper range
      return 1;
    if (val < 500) // Close to the lower range
      return -1;
    return 0;
  }

};

#endif