#ifndef UTILS_STRUCTS_POS_HPP
#define UTILS_STRUCTS_POS_HPP

struct Pos
{
  byte x = 0;
  byte y = 0;

  Pos(byte cx, byte cy)
  {
    x = cx;
    y = cy;
  }

  bool canDraw()
  {
    // is in screen
    return x > -1 && x < 20 && y < 4 && y > -1;
  }

  bool collidesWith(const Pos &other)
  {
    return x == other.x && y == other.y;
  }
};

#endif