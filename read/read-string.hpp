#ifndef READ_READ_STRING_HPP
#define READ_READ_STRING_HPP

#include "../utils/structs/pos.hpp"
#include "../utils/structs/draw-keybord-meta-data.hpp"
#include "../globals.hpp"
#include "../cursor.hpp"
#include "./read-char.hpp"

String *ReadString(DrawKeyBoardMetaData drawKeyBoardMetaData)
{
  lcd.clear();
  char out;

  while (true)
  {
    out = ReadChar(&drawKeyBoardMetaData);

    if (out == GET_CHAR_LEFT_SHIFT && drawKeyBoardMetaData.writePos > 0)
    {
      drawKeyBoardMetaData.writePos--;
    }
    else if (out == GET_CHAR_RIGHT_SHIFT && drawKeyBoardMetaData.writePos < drawKeyBoardMetaData.prompt->length())
    {
      drawKeyBoardMetaData.writePos++;
    }
    else if (out == GET_CHAR_BACKSPACE)
    {
      drawKeyBoardMetaData.prompt->remove(drawKeyBoardMetaData.writePos - 1, 1);
      drawKeyBoardMetaData.writePos--;
    }
    else if (out == GET_CHAR_SUBMIT)
    {
      break;
    }
    else if (out == GET_CHAR_DELETE_ALL)
    {
      *drawKeyBoardMetaData.prompt = "";
      drawKeyBoardMetaData.writePos = 0;
    }
    else if (isascii(out))
    {
      *drawKeyBoardMetaData.prompt = drawKeyBoardMetaData.prompt->substring(0, drawKeyBoardMetaData.writePos) + out + drawKeyBoardMetaData.prompt->substring(drawKeyBoardMetaData.writePos);
      drawKeyBoardMetaData.writePos++;
    };

    delay(RENDERING_FRAME);
  }

  lcd.clear();
  lcd.print(drawKeyBoardMetaData.prompt->c_str());

  delay(1000);
  lcd.clear();

  return drawKeyBoardMetaData.prompt;
}

#endif