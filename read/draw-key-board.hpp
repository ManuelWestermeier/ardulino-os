#ifndef READ_DRAW_KEY_BOARD_HPP
#define READ_DRAW_KEY_BOARD_HPP

#include "../utils/structs/pos.hpp"
#include "../utils/structs/draw-keybord-meta-data.hpp"
#include "../globals.hpp"
#include "../cursor.hpp"
#include "./index.hpp"

void DrawKeyBoard(Pos cursorPos, DrawKeyBoardMetaData *drawKeyBoardMetaData)
{
  // promt layout
  if (!cursorPos.collidesWith({0, 0}))
  {
    lcd.home();
    lcd.write('<');
  }
  if (!cursorPos.collidesWith({19, 0}))
  {
    lcd.setCursor(19, 0);
    lcd.write('>');
  }

  // Assuming drawKeyBoardMetaData and lcd are properly initialized and available
  int promptLength = drawKeyBoardMetaData->prompt->length();

  for (int i = 1; i < 18; i++)
  {
    int writeCharindex = i - (CURSOR_OFFSET + 1) + drawKeyBoardMetaData->writePos;

    if (i < (CURSOR_OFFSET + 1))
    {
      if (!cursorPos.collidesWith({i, 0}))
      {
        lcd.setCursor(i, 0);

        if (writeCharindex < promptLength && writeCharindex > -1)
          lcd.write(drawKeyBoardMetaData->prompt->charAt(writeCharindex));
        else
          lcd.write(' ');
      }
    }
    else
    {
      if (!cursorPos.collidesWith({i + 1, 0}))
      {
        lcd.setCursor(i + 1, 0);

        if (writeCharindex < promptLength && writeCharindex > -1)
          lcd.write(drawKeyBoardMetaData->prompt->charAt(writeCharindex));
        else
          lcd.write(' ');
      }
    }
  }

  // text cursor
  if (!cursorPos.collidesWith({(CURSOR_OFFSET + 1), 0}))
  {
    lcd.setCursor((CURSOR_OFFSET + 1), 0);
    lcd.write(Cursor::cursorFrameState ? 'I' : '|');
  }

  // draw alphabetics layout
  for (int i = 0; i < 20; i++)
  {
    if (!cursorPos.collidesWith({i, 1}))
    {
      lcd.setCursor(i, 1);
      lcd.write(currentCharUpperCase ? toupper(keyBoardLayout[0][i]) : keyBoardLayout[0][i]);
    }
    if (!cursorPos.collidesWith({i, 2}))
    {
      lcd.setCursor(i, 2);
      lcd.write(currentCharUpperCase ? toupper(keyBoardLayout[1][i]) : keyBoardLayout[1][i]);
    }
  }

  // clear last row
  // clear part bevore buttons
  for (int i = 1; i < 11; i++)
  {
    if (!cursorPos.collidesWith({i, 3}))
    {
      lcd.setCursor(i, 3);
      lcd.write(' ');
    }
  }
  // clear between buttons
  for (int i = 11; i < 19; i++)
  {
    // only draw if the cursor isnt on the pos and its every fist of 2
    if (!cursorPos.collidesWith({i, 3}) && i % 2 == 0)
    {
      lcd.setCursor(i, 3);
      lcd.write(' ');
    }
  }

  // non alfabetic characters
  if (!cursorPos.collidesWith({11, 3}))
  {
    lcd.setCursor(11, 3);
    lcd.write('#');
  }

  // Delete all
  if (!cursorPos.collidesWith({13, 3}))
  {
    lcd.setCursor(13, 3);
    lcd.write('X');
  }

  // Uppercase and Lowercase
  if (!cursorPos.collidesWith({15, 3}))
  {
    lcd.setCursor(15, 3);
    lcd.write('x');
  }

  // Uppercase and Lowercase
  if (!cursorPos.collidesWith({17, 3}))
  {
    lcd.setCursor(17, 3);
    lcd.write(currentCharUpperCase ? 'a' : 'A');
  }

  // confirm
  if (!cursorPos.collidesWith({19, 3}))
  {
    lcd.setCursor(19, 3);
    lcd.write(confirm_charcode);
  }

  // selected
  lcd.setCursor(0, 3);
  if (cursorPos.y == 1 || cursorPos.y == 2)
  {
    lcd.setCursor(0, 3);
    lcd.write(currentCharUpperCase ? toupper(keyBoardLayout[cursorPos.y - 1].charAt(cursorPos.x)) : keyBoardLayout[cursorPos.y - 1].charAt(cursorPos.x));
  }
  else if (cursorPos.y == 0)
  {
    lcd.write(cursorPos.x == 0 ? '<' : (cursorPos.x == 19 ? '>' : '-'));
  }
  else if (cursorPos.collidesWith({11, 3}))
  {
    lcd.write('#');
  }
  else if (cursorPos.collidesWith({15, 3}))
  {
    lcd.write('x');
  }
  else if (cursorPos.collidesWith({13, 3}))
  {
    lcd.write('X');
  }
  else if (cursorPos.collidesWith({17, 3}))
  {
    lcd.write(currentCharUpperCase ? 'a' : 'A');
  }
  else if (cursorPos.collidesWith({19, 3}))
  {
    lcd.write(confirm_charcode);
  }
  else
  {
    lcd.write('-');
  }
}

#endif