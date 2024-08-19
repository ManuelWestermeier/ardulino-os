#ifndef CURSOR_HPP

#define CURSOR_HPP

#include "./globals.hpp"
#include "./utils/structs/pos.hpp"

namespace Cursor
{
  Pos pos = {10, 2};

  int last = 3;
  bool cursorFrameState = 0;

  void UpdateCursorFrameState()
  {
    if (last-- == 0)
    {
      cursorFrameState = !cursorFrameState;
      lcd.createChar(cursor_charcode, cursorChar[cursorFrameState]);
      last = 3;
    }
  }

  void Draw()
  {
    UpdateCursorFrameState();
    lcd.setCursor(pos.x, pos.y);
    lcd.write(0);
  }

  void Update()
  {
    int h = analogRead(xPin); // get the horizontal joystick input
    int v = analogRead(yPin); // get the vertical joystick input

    // move cursor
    if (h > 700 && pos.x < 19)
      pos.x++;

    if (h < 300 && pos.x > 0)
      pos.x--;

    if (v < 300 && pos.y < 3)
      pos.y++;

    if (v > 700 && pos.y > 0)
      pos.y--;

    // move cursor fast
    if (h > 1015 && pos.x < 19)
      pos.x++;

    if (h < 9 && pos.x > 0)
      pos.x--;

    Draw();
  }

  template <typename BypassedType>
  Pos Get(void (*bevorUpdate)(Pos, BypassedType), BypassedType bypassed)
  {
    static int round = 0;
    while (digitalRead(swPin) != LOW)
    {
      bevorUpdate(pos, bypassed);
      Update();
      delay(RENDERING_FRAME);
    }
    return pos;
  }
};

#endif