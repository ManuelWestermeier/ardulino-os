#ifndef APPS_HOME_HPP
#define APPS_HOME_HPP

#include "../../globals.hpp"
#include "../../cursor.hpp"
#include "../../auth.hpp"
#include "../../utils/structs/pos.hpp"
#include "../../utils/structs/select.hpp"
#include "../../app-renderer.hpp"

// apps
#include "../create-account/index.hpp"

struct HomeLink
{
    String name;
    String appId;
    bool isApp;
    String startArgument;

    HomeLink(String _name, String _appId, bool _isApp = true, String _startArgument = "")
        : name(_name), appId(_appId), isApp(_isApp), startArgument(_startArgument) {}
};

namespace HomeApp
{
    String state;
    std::vector<HomeLink> homeLinks;
    Select appSelect{nullptr, 0, 1};

    void SetAppSelect()
    {
        if (appSelect.options != nullptr)
        {
            delete[] appSelect.options;
        }

        appSelect.options = new String[homeLinks.size()];
        for (size_t i = 0; i < homeLinks.size(); i++)
        {
            appSelect.options[i] = homeLinks[i].name;
        }
        appSelect.optionsLength = homeLinks.size();
    }

    String EscapeString(const String &input)
    {
        String escaped = input;
        escaped.replace("\\", "\\\\"); // Escape backslashes
        escaped.replace("\n", "\\n");  // Escape newlines
        escaped.replace("|", "\\|");   // Escape pipes
        return escaped;
    }

    String DeescapeString(const String &input)
    {
        String deescaped = input;
        deescaped.replace("\\n", "\n");  // Deescape newlines
        deescaped.replace("\\|", "|");   // Deescape pipes
        deescaped.replace("\\\\", "\\"); // Deescape backslashes
        return deescaped;
    }

    bool IsHomeLinkUnique(const String &name)
    {
        for (const auto &link : homeLinks)
        {
            if (link.name == name)
            {
                return false;
            }
        }
        return true;
    }

    void LoadHomeLinksFromFile()
    {
        File file = LittleFS.open("/app-links.data", "r");
        if (!file)
        {
            Serial.println("Failed to open app-links.data");
            return;
        }

        while (file.available())
        {
            String line = file.readStringUntil('\n');
            line.replace("|", "\n"); // Convert the separator to a newline for processing

            String parts[3];
            int count = 0;

            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == '\n' || i == line.length() - 1)
                {
                    if (i == line.length() - 1)
                    {
                        parts[count++] += line[i];
                    }
                    count++;
                    if (count >= 3)
                        break;
                }
                else
                {
                    parts[count] += line[i];
                }
            }

            if (count == 3)
            {
                String name = DeescapeString(parts[0]);
                String appId = DeescapeString(parts[1]);
                String startArg = DeescapeString(parts[2]);

                if (IsHomeLinkUnique(name))
                {
                    homeLinks.push_back(HomeLink(name, appId, true, startArg));
                }
            }
        }

        file.close();
    }

    void Init()
    {
        // Load default home links
        homeLinks = {
            HomeLink("Wifi", "wifi"),
            HomeLink("Browser", "browser"),
            HomeLink("Clock", "clock"),
            HomeLink("Flash Light", "flash-light"),
            HomeLink("Pin Menager", "pin-menager"),
            HomeLink("EEPROM Editor", "eeprom-editor"),
            HomeLink("Memory Editor", "memory-editor"),
            HomeLink("Login", "login"),
            HomeLink("Create Account", "create-account"),
        };

        // Load links from file
        LoadHomeLinksFromFile();

        // Update appSelect after loading
        SetAppSelect();
    }

    void AddHomeLink(const HomeLink &link)
    {
        if (IsHomeLinkUnique(link.name))
        {
            homeLinks.push_back(link);
            SetAppSelect();
            // Append to the file
            File file = LittleFS.open("/app-links.data", "a");
            if (file)
            {
                file.print(EscapeString(link.name) + "|" + EscapeString(link.appId) + "|" + EscapeString(link.startArgument) + "\n");
                file.close();
            }
        }
    }

    void RemoveHomeLink(const String &name)
    {
        homeLinks.erase(
            std::remove_if(homeLinks.begin(), homeLinks.end(),
                           [&](const HomeLink &link)
                           { return link.name == name; }),
            homeLinks.end());

        SetAppSelect();
        // Update the file by rewriting all home links
        File file = LittleFS.open("/app-links.data", "w");
        if (file)
        {
            for (const auto &link : homeLinks)
            {
                file.print(EscapeString(link.name) + "|" + EscapeString(link.appId) + "|" + EscapeString(link.startArgument) + "\n");
            }
            file.close();
        }
    }

    void Update()
    {
        SetAppTitle("Home", 4);
        appSelect.Update();
    }

    void Scroll(signed char direction)
    {
        appSelect.Scroll(direction);
    }

    void SwitchApp()
    {
        int clickedApp = appSelect.OnClick();
        ClearAppScreen();

        const HomeLink &selectedLink = homeLinks[clickedApp];

        if (selectedLink.name == "Create Account")
        {
            isLoggedIn = false;
            CreateAccountApp::Create();
        }
        else
        {
            AppRender::appOpened = selectedLink.appId;

            if (selectedLink.isApp && registeredApps[AppRender::appOpened].Start)
            {
                registeredApps[AppRender::appOpened].Start(selectedLink.startArgument);
            }
        }
    }

    void OnClick(Pos)
    {
        SwitchApp();
    }

    void Submit()
    {
        SwitchApp();
    }
};

#endif