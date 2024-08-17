namespace BrowserApp
{
    String state;

    void Update()
    {
    }

    void Scroll(signed char direction) {}
    void OnExit()
    {
        lcd.print("exit");
    }
    void OnClick(Pos clickPos);
};