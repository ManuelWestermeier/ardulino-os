char keyBoardLayout[2][20] = {
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't'},
    {'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N'}
};

struct DrawKeyBoardMetaData {
  unsigned int writePos;
  String* prompt;
};

bool currentCharUpperCase = false;

#include "./draw-key-board.hpp"
#include "./read-char.hpp"
#include "./read-string.hpp"