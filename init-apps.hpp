#ifndef INIT_APPS_HPP
#define INIT_APPS_HPP

#include "./globals.hpp"
#include "./app-renderer.hpp"

#include "./apps/browser/index.hpp"
#include "./apps/wifi/index.hpp"
#include "./apps/login/index.hpp"
#include "./apps/home/index.hpp"
#include "./apps/eeprom-editor/index.hpp"
#include "./apps/memory-editor/index.hpp"
#include "./apps/flash-light/index.hpp"
#include "./apps/pin-menager/index.hpp"
#include "./apps/clock/index.hpp"

// Define prototypes for each app
AppPrototype homeApp = {
    "home",
    nullptr, // Start
    HomeApp::Update,
    HomeApp::Scroll,  // Scroll
    nullptr,          // OnExit
    HomeApp::OnClick, // OnClick
    HomeApp::Submit,
};

AppPrototype browserApp = {
    "browser",
    BrowserApp::Start, // Start
    BrowserApp::Update,
    BrowserApp::Scroll, // Scroll
    BrowserApp::OnExit,
    BrowserApp::OnClick,
    BrowserApp::Submit, // Submit
};

AppPrototype wifiApp = {
    "wifi",
    nullptr, // Start
    WifiApp::Update,
    WifiApp::Scroll,
    nullptr, // OnExit
    WifiApp::OnClick,
    WifiApp::Submit,
};

AppPrototype loginApp = {
    "login",
    nullptr, // Start
    LoginApp::Update,
    LoginApp::Scroll,
    nullptr, // OnExit
    LoginApp::OnClick,
    nullptr, // Submit
};

AppPrototype eepromEditorApp = {
    "eeprom-editor",
    nullptr, // Start
    EEPROMEditor::Update,
    EEPROMEditor::Scroll,
    nullptr, // OnExit
    nullptr, // OnClick
    EEPROMEditor::Submit,
};

AppPrototype memoryEditorApp = {
    "memory-editor",
    nullptr, // Start
    MemoryEditor::Update,
    MemoryEditor::Scroll,
    nullptr, // OnExit
    nullptr, // OnClick
    MemoryEditor::Submit,
};

AppPrototype flashLightApp = {
    "flash-light",
    nullptr, // Start
    FlashLightApp::Update,
    nullptr,                // Scroll
    nullptr,                // OnExit
    FlashLightApp::OnClick, // OnClick
    FlashLightApp::Submit,
};

AppPrototype pinManagerApp = {
    "pin-menager",
    nullptr, // Start
    PinMengerApp::Update,
    PinMengerApp::Scroll,
    nullptr,               // OnExit
    PinMengerApp::OnClick, // OnClick
    PinMengerApp::Submit,
};

AppPrototype clockApp = {
    "clock",
    nullptr, // Start
    ClockApp::Update,
    ClockApp::Scroll,
    nullptr,           // OnExit
    ClockApp::OnClick, // OnClick
    ClockApp::Submit,
};

// Register all app prototypes at initialization
void InitializeApps()
{
    RegisterApp(homeApp);
    RegisterApp(browserApp);
    RegisterApp(wifiApp);
    RegisterApp(loginApp);
    RegisterApp(eepromEditorApp);
    RegisterApp(memoryEditorApp);
    RegisterApp(flashLightApp);
    RegisterApp(pinManagerApp);
    RegisterApp(clockApp);
}

#endif
