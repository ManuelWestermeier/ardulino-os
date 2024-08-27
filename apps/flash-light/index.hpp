#ifndef APPS_FLASH_LIGHT_INDEX_HPP
#define APPS_FLASH_LIGHT_INDEX_HPP

#include "../../utils/structs/pos.hpp"
#include "../../utils/structs/clickable.hpp"
#include "../../globals.hpp"

namespace FlashLightApp
{
    Clickable toggleButton{2, 7, 11, "ON", 2};
    bool isOn = false;

    void Update()
    {
        for (byte i = 0; i < 11; i++)
        {
            appScreenData[i + 4][1] = "Flash Light"[i];
        }
        toggleButton.Draw();
    }

    void UpdateUI()
    {
        // set ui
        if (isOn)
        {
            toggleButton.text = "OFF";
            toggleButton.end = 12;
            toggleButton.stringLength = 3;
        }
        else
        {
            toggleButton.text = "ON";
            toggleButton.end = 11;
            toggleButton.stringLength = 2;
            appScreenData[11][2] = ' ';
        }
    }

    void Toggle()
    {
        // toggle
        isOn = !isOn;
        digitalWrite(ledPin, isOn ? HIGH : LOW);
        UpdateUI();
    }

    void Submit()
    {
        Toggle();
    }

    void OnClick(Pos pos)
    {
        if (toggleButton.collidesWith(pos))
            Toggle();
    }
}

#endif