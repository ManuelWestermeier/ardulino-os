#ifndef CURSOR_HPP
#define CURSOR_HPP

#include "./globals.hpp"
#include "./utils/structs/pos.hpp"
#include "./utils/index.hpp"

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
    int h = utils::normalizeJoystick(xPin); // get the horizontal joystick input
    int v = utils::normalizeJoystick(yPin); // get the vertical joystick input

    // move cursor
    if (h > 0 && pos.x < 19)
      pos.x++;

    if (h < 0 && pos.x > 0)
      pos.x--;

    if (v < 0 && pos.y < 3)
      pos.y++;

    if (v > 0 && pos.y > 0)
      pos.y--;

    // move cursor fast
    if (h > 1 && pos.x < 19)
      pos.x++;

    if (h < -1 && pos.x > 0)
      pos.x--;

    Draw();
  }

  template <typename BypassedType>
  Pos Get(void (*bevorUpdate)(Pos, BypassedType), BypassedType bypassed)
  {
    // static int round = 0;
    while (digitalRead(swPin) != LOW)
    {
      bevorUpdate(pos, bypassed);
      Update();
      delay(RENDERING_FRAME);
    }
    while (digitalRead(swPin) != HIGH);
    return pos;
  }
};

#endif