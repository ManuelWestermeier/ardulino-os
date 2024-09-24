#ifndef READ_READ_CHAR_HPP
#define READ_READ_CHAR_HPP

#include "./draw-key-board.hpp"
#include "../read/index.hpp"

char ReadChar(DrawKeyBoardMetaData *drawKeyBoardMetaData)
{
  Pos cursorPos = Cursor::Get<DrawKeyBoardMetaData *>(DrawKeyBoard, drawKeyBoardMetaData);

  digitalWrite(LED_BUILTIN, HIGH);
  while (digitalRead(swPin) == LOW)
    ;
  digitalWrite(LED_BUILTIN, LOW);

  // characters
  if (cursorPos.y == 1 || cursorPos.y == 2)
  {
    char currentChar = keyBoardLayout[cursorPos.y - 1].charAt(cursorPos.x);
    return currentCharUpperCase ? toupper(currentChar) : currentChar;
  }

  // left scroll
  if (cursorPos.collidesWith({0, 0}))
  {
    return GET_CHAR_LEFT_SHIFT;
  }

  // right scroll
  if (cursorPos.collidesWith({19, 0}))
  {
    return GET_CHAR_RIGHT_SHIFT;
  }

  //
  if (cursorPos.collidesWith({11, 3}))
  {
    return input::getByte("special char:", '#', 3);
  }

  // backspace
  if (cursorPos.collidesWith({15, 3}))
  {
    return GET_CHAR_BACKSPACE;
  }

  // uppercase and lowercase
  if (cursorPos.collidesWith({17, 3}))
  {
    currentCharUpperCase = !currentCharUpperCase;
    DrawKeyBoard(cursorPos, drawKeyBoardMetaData);
    delay(RENDERING_FRAME);
    return ReadChar(drawKeyBoardMetaData);
  }

  // submit
  if (cursorPos.collidesWith({19, 3}))
    return GET_CHAR_SUBMIT;

  //
  if (cursorPos.collidesWith({13, 3}))
    return GET_CHAR_DELETE_ALL;

  return ReadChar(drawKeyBoardMetaData);
}

#endif