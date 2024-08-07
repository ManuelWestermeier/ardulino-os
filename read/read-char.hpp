char ReadChar(DrawKeyBoardMetaData* drawKeyBoardMetaData) {
  Pos cursorPos = cursor.Get<DrawKeyBoardMetaData*>(DrawKeyBoard, drawKeyBoardMetaData);

  // wait for key up
  while (digitalRead(swPin) == LOW)
    ;

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

  //delete all
  if (cursorPos.collidesWith({ 13, 3 })) return GET_CHAR_DELETE_ALL;

  return ReadChar(drawKeyBoardMetaData);
}