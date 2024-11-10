#pragma once

#include "../../utils/structs/mwpl.hpp"
#include "../../read/index.hpp"
#include <LittleFS.h>

String *getDefaultSite()
{
    // Open the file in read mode
    File file = LittleFS.open("/default-site.txt", "r");
    if (!file)
    {
        Serial.println("File /default-site.txt does not exist");
        return new String("192.168.178.33:61680");
    }

    // Read the file content into a string
    String content = file.readString();
    file.close();

    // Check if content is empty, and return the default if so
    if (content.length() == 0)
    {
        return new String("192.168.178.33:61680");
    }

    // Return the file content
    return new String(content);
}

void BrowserApp::NewTab()
{
    auto placeholder = getDefaultSite();

    WebviewData newWebview(*input::ReadString({
        0,
        placeholder,
    }));

    State::webviews.push_back(newWebview);
}