namespace utils
{
    void waitForRelease()
    {
        while (digitalRead(swPin) != LOW)
            ;
        lcd.clear();
        lcd.setCursor(4, 1);
        lcd.print("release key");
        digitalWrite(LED_BUILTIN, HIGH);
        while (digitalRead(swPin) == LOW)
            ;
        digitalWrite(LED_BUILTIN, LOW);
        lcd.clear();
    }
};