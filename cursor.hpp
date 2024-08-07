struct Cursor
{
  Pos pos = {10, 2};

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

  Update()
  {
    int h = analogRead(xPin); // get the horizontal joystick input
    int v = analogRead(yPin); // get the vertical joystick input

    // move cursor
    if (h > 900 && pos.x < 19)
      pos.x++;

    if (h < 100 && pos.x > 0)
      pos.x--;

    if (v < 100 && pos.y < 3)
      pos.y++;

    if (v > 900 && pos.y > 0)
      pos.y--;

    Draw();
  }

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
};

Cursor cursor;