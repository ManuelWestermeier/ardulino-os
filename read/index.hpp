#include <ctype.h>
String keyBoardLayout[2] = {
    "abcdefghij0123456789",
    "klmnopqrstuvwxyz .?!"};

struct DrawKeyBoardMetaData
{
  unsigned int writePos;
  String *prompt;
};

bool currentCharUpperCase = false;

#include "./draw-key-board.hpp"
#include "./read-char.hpp"
#include "./read-string.hpp"