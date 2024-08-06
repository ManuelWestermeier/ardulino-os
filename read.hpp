String keyBoardLayout[2] = {
  "abcdefghij0123456789",
  "klmnopqrstuvwxyz .?!"
};

struct DrawKeyBoardMetaData {
  int writePos;
  String* prompt;
};

bool currentCharUpperCase = false;

// "\\.\COM3"
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

  //prompt
  // int promptLength = drawKeyBoardMetaData->prompt->length();
  // for (int i = 1; i < 19; i++) {
  //   lcd.setCursor(i, 0);
  //   if (i - 1 == drawKeyBoardMetaData->writePos) {
  //     lcd.write('_');
  //   } else {
  //     lcd.write(i - 1 < promptLength ? drawKeyBoardMetaData->prompt->charAt(i - 1) : ' ');
  //   }
  // }

  int promptLength = drawKeyBoardMetaData->prompt->length();
  for (int i = 1; i < 19; i++) {
    if (!cursorPos.collidesWith({ i, 0 })) {
      lcd.setCursor(i, 0);
      int promptPos = i - 5 - drawKeyBoardMetaData->writePos;
      lcd.write(promptPos < promptLength && promptPos > -1 ? drawKeyBoardMetaData->prompt->charAt(promptPos) : ' ');
    }
  }

  if (!cursorPos.collidesWith({ 5, 0 })) {
    //string edit cursor pos
    lcd.setCursor(5, 0);
    lcd.write('_');
  }

  //draw alphabetics layout
  // lcd.setCursor(0, 1);
  // lcd.print(keyBoardLayout[0]);
  // lcd.setCursor(0, 2);
  // lcd.print(keyBoardLayout[1]);
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

  //Uppercase
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
  } else if (cursorPos.collidesWith({ 17, 3 })) {
    lcd.write(currentCharUpperCase ? 'a' : 'A');
  } else if (cursorPos.collidesWith({ 19, 3 })) {
    lcd.write(confirm_charcode);
  } else lcd.write('-');
}

char ReadChar(DrawKeyBoardMetaData* drawKeyBoardMetaData) {
  Pos cursorPos = cursor.Get<DrawKeyBoardMetaData*>(DrawKeyBoard, drawKeyBoardMetaData);

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

  //uppercase and lowercase
  if (cursorPos.collidesWith({ 17, 3 })) {
    currentCharUpperCase = !currentCharUpperCase;
    DrawKeyBoard(cursorPos, drawKeyBoardMetaData);
    delay(RENDERING_FRAME);
    return ReadChar(drawKeyBoardMetaData);
  }

  //submit
  if (cursorPos.collidesWith({ 19, 3 })) return GET_CHAR_SUBMIT;

  return GET_CHAR_NO_CHAR;
}

String* ReadString(DrawKeyBoardMetaData drawKeyBoardMetaData) {
  char out;

  while (true) {
    out = ReadChar(&drawKeyBoardMetaData);

    if (out == GET_CHAR_LEFT_SHIFT && drawKeyBoardMetaData.writePos > 0) {
      drawKeyBoardMetaData.writePos++;
    } else if (out == GET_CHAR_RIGHT_SHIFT && drawKeyBoardMetaData.writePos < drawKeyBoardMetaData.prompt->length()) {
      drawKeyBoardMetaData.writePos--;
    } else if (out == GET_CHAR_SUBMIT) {
      break;
    } else lcd.write(out);

    delay(RENDERING_FRAME);
  }

  lcd.clear();

  return drawKeyBoardMetaData.prompt;
}