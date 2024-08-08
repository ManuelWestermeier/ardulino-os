struct Apprender
{
    void Update()
    {
        lcd.home();
        for (int i = 0; i < 16; i++)
        {
            lcd.setCursor(i, 0);
            lcd.write(appTitel[i]);
        }
        lcd.setCursor(17, 0);
        lcd.print(" - x");
        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 19; x++)
            {
                lcd.setCursor(x, y + 1);
                lcd.write();
            }
        }
    }
};