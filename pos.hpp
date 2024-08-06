struct Pos {
  int x = 0;
  int y = 0;

  Pos(int cx, int cy) {
    x = cx;
    y = cy;
  }

  bool canDraw() {
    // is in screen
    return x > -1 && x < 20 && y < 4 && y > -1;
  }

  bool collidesWith(const Pos& other) {
    return x == other.x && y == other.y;
  }
};