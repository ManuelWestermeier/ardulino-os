#ifndef UTILS_STRUCTS_STORED_MAP
#define UTILS_STRUCTS_STORED_MAP

#include "../../globals.hpp"
#include <base64.h> // Include Base64 library (you may need to install it)

struct FlashHashMap
{
    String root;

    // Constructor to initialize the root directory with the escaped map ID
    FlashHashMap(const String &mapId)
    {
        root = "/maps/" + base64Encode(mapId) + "/"; // Set the root directory based on Base64 encoded map ID
        createDirectory();                           // Create the directory if it doesn't exist
    }

    // Method to begin LittleFS
    static void begin()
    {
        LittleFS.begin();
    }

    // Method to Base64 encode keys and map IDs
    String base64Encode(const String &key)
    {
        String encoded = base64::encode((const uint8_t *)key.c_str(), key.length());
        encoded.replace("=", "_"); // Replace padding character
        encoded.replace("/", "_"); // Replace with underscore or any other safe character
        encoded.replace("+", "-"); // Replace with a hyphen or any other safe character
        return encoded;
    }

    // Method to create the root directory if it doesn't exist
    void createDirectory()
    {
        if (!LittleFS.exists("/maps/"))
        {
            LittleFS.mkdir("/maps/");
        }

        if (!LittleFS.exists(root))
        {
            LittleFS.mkdir(root);
        }
    }

    // Check if a file exists
    bool fileExists(const String &filePath)
    {
        return LittleFS.exists(filePath);
    }

    // Method to set a key-value pair
    void set(const String &key, const String &value)
    {
        String escapedKey = base64Encode(key);      // Base64 encode the key to make it valid
        String filePath = root + escapedKey + ".v"; // Construct the full file path with ".v"

        // Create the file
        File file = LittleFS.open(filePath, fileExists(filePath) ? "w" : "w+", !fileExists(filePath));
        file.print(value); // Write to the file
        file.close();
    }

    // Method to get a value by key
    String get(const String &key)
    {
        String escapedKey = base64Encode(key);      // Base64 encode the key to make it valid
        String filePath = root + escapedKey + ".v"; // Construct the full file path

        File file = LittleFS.open(filePath, "r");
        String value = file.readString();
        file.close();

        return value;
    }

    // Method to check if a key exists
    bool has(const String &key)
    {
        String escapedKey = base64Encode(key);      // Base64 encode the key
        String filePath = root + escapedKey + ".v"; // Construct the full file path
        return fileExists(filePath);                // Use the fileExists method
    }

    // Method to delete a key-value pair
    void remove(const String &key)
    {
        String escapedKey = base64Encode(key);      // Base64 encode the key
        String filePath = root + escapedKey + ".v"; // Construct the full file path
        LittleFS.remove(filePath);
    }
};

#endif
