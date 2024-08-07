#include <ctype.h>
String keyBoardLayout[2] = {
  "abcdefghij0123456789",
  "klmnopqrstuvwxyz .?!"
};

struct DrawKeyBoardMetaData {
  unsigned int writePos;
  String* prompt;
};

bool currentCharUpperCase = false;

void DrawKeyBoard(Pos cursorPos, DrawKeyBoardMetaData* drawKeyBoardMetaData) {
  //promt layout
  if (!cursorPos.collidesWith({ 0, 0 })) {
    lcd.home();
    lcd.write('<');
  }
  if (!cursorPos.collidesWith({ 19, 0 })) {
    lcd.setCursor(19, 0);
    lcd.write('>');
  }

  // Assuming drawKeyBoardMetaData and lcd are properly initialized and available
  int promptLength = drawKeyBoardMetaData->prompt->length();

  for (int i = 1; i < 18; i++) {
    int writeCharindex = i - 5 + drawKeyBoardMetaData->writePos;

    if (i < 5) {
      if (!cursorPos.collidesWith({ i, 0 })) {
        lcd.setCursor(i, 0);

        if (writeCharindex < promptLength && writeCharindex > -1)
          lcd.write(drawKeyBoardMetaData->prompt->charAt(writeCharindex));
        else lcd.write(' ');
      }
    } else {
      if (!cursorPos.collidesWith({ i + 1, 0 })) {
        lcd.setCursor(i + 1, 0);

        if (writeCharindex < promptLength && writeCharindex > -1)
          lcd.write(drawKeyBoardMetaData->prompt->charAt(writeCharindex));
        else lcd.write(' ');
      }
    }
  }

  if (!cursorPos.collidesWith({ 5, 0 })) {
    lcd.setCursor(5, 0);
    lcd.write(cursor.cursorFrameState ? 'I' : '|');
  }

  //draw alphabetics layout
  for (int i = 0; i < 20; i++) {
    if (!cursorPos.collidesWith({ i, 1 })) {
      lcd.setCursor(i, 1);
      lcd.write(currentCharUpperCase ? toupper(keyBoardLayout[0][i]) : keyBoardLayout[0][i]);
    }
    if (!cursorPos.collidesWith({ i, 2 })) {
      lcd.setCursor(i, 2);
      lcd.write(currentCharUpperCase ? toupper(keyBoardLayout[1][i]) : keyBoardLayout[1][i]);
    }
  }

  //clear last row
  for (int i = 1; i < 19; i++) {
    if (!cursorPos.collidesWith({ i, 3 })) {
      lcd.setCursor(i, 3);
      lcd.write(' ');
    }
  }

  //Uppercase and Lowercase
  lcd.setCursor(15, 3);
  lcd.write('x');

  //Uppercase and Lowercase
  lcd.setCursor(17, 3);
  lcd.write(currentCharUpperCase ? 'a' : 'A');

  //confirm
  lcd.setCursor(19, 3);
  lcd.write(confirm_charcode);

  //selected
  lcd.setCursor(0, 3);
  if (cursorPos.y == 1 || cursorPos.y == 2) {
    lcd.setCursor(0, 3);
    lcd.write(currentCharUpperCase ? toupper(keyBoardLayout[cursorPos.y - 1].charAt(cursorPos.x)) : keyBoardLayout[cursorPos.y - 1].charAt(cursorPos.x));
  } else if (cursorPos.y == 0) {
    lcd.write(cursorPos.x == 0 ? '<' : (cursorPos.x == 19 ? '>' : '-'));
  } else if (cursorPos.collidesWith({ 15, 3 })) {
    lcd.write('x');
  } else if (cursorPos.collidesWith({ 17, 3 })) {
    lcd.write(currentCharUpperCase ? 'a' : 'A');
  } else if (cursorPos.collidesWith({ 19, 3 })) {
    lcd.write(confirm_charcode);
  } else lcd.write('-');
}

char ReadChar(DrawKeyBoardMetaData* drawKeyBoardMetaData) {
  Pos cursorPos = cursor.Get<DrawKeyBoardMetaData*>(DrawKeyBoard, drawKeyBoardMetaData);

  while (digitalRead(swPin) == LOW);

  //characters
  if (cursorPos.y == 1 || cursorPos.y == 2) {
    char currentChar = keyBoardLayout[cursorPos.y - 1].charAt(cursorPos.x);
    return currentCharUpperCase ? toupper(currentChar) : currentChar;
  }

  //left scroll
  if (cursorPos.x == 0 && cursorPos.y == 0) {
    return GET_CHAR_LEFT_SHIFT;
  }

  //right scroll
  if (cursorPos.x == 19 && cursorPos.y == 0) {
    return GET_CHAR_RIGHT_SHIFT;
  }

  //backspace
  if (cursorPos.collidesWith({ 15, 3 })) {
    return GET_CHAR_BACKSPACE;
  }

  //uppercase and lowercase
  if (cursorPos.collidesWith({ 17, 3 })) {
    currentCharUpperCase = !currentCharUpperCase;
    DrawKeyBoard(cursorPos, drawKeyBoardMetaData);
    delay(RENDERING_FRAME);
    return ReadChar(drawKeyBoardMetaData);
  }

  //submit
  if (cursorPos.collidesWith({ 19, 3 })) return GET_CHAR_SUBMIT;

  return ReadChar(drawKeyBoardMetaData);
}

String* ReadString(DrawKeyBoardMetaData drawKeyBoardMetaData) {
  lcd.clear();
  char out;

  while (true) {
    out = ReadChar(&drawKeyBoardMetaData);

    if (out == GET_CHAR_LEFT_SHIFT && drawKeyBoardMetaData.writePos > 0) {
      drawKeyBoardMetaData.writePos--;
    } else if (out == GET_CHAR_RIGHT_SHIFT && drawKeyBoardMetaData.writePos < drawKeyBoardMetaData.prompt->length()) {
      drawKeyBoardMetaData.writePos++;
    } else if (out == GET_CHAR_BACKSPACE) {
      drawKeyBoardMetaData.prompt->remove(drawKeyBoardMetaData.writePos - 1, 1);
      drawKeyBoardMetaData.writePos--;
    } else if (out == GET_CHAR_SUBMIT) {
      break;
    } else if (isascii(out)) {
      *drawKeyBoardMetaData.prompt = drawKeyBoardMetaData.prompt->substring(0, drawKeyBoardMetaData.writePos) + out + drawKeyBoardMetaData.prompt->substring(drawKeyBoardMetaData.writePos);
      drawKeyBoardMetaData.writePos++;
    };

    delay(RENDERING_FRAME);

    // delay(RENDERING_FRAME * 10);

    // lcd.clear();
    // lcd.home();
    // lcd.print(drawKeyBoardMetaData.writePos);

    // delay(RENDERING_FRAME * 10);
    // lcd.clear();
  }

  delay(RENDERING_FRAME * 10);
  lcd.clear();

  lcd.print(drawKeyBoardMetaData.prompt->c_str());

  delay(RENDERING_FRAME * 10);
  lcd.clear();

  return drawKeyBoardMetaData.prompt;
}