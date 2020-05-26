#include <Arduino.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include "Settings.hpp"

bool Settings::readFromEEPROM()
{
    EEPROM.begin(512);

    char buffer[512];
    int i;
    for (i = 0; i < 511; i++)
    {
        char c = EEPROM.read(i);
        if (c == 0)
            break;
        buffer[i] = c;
    }
    buffer[i] = 0;

    EEPROM.end();

    StaticJsonBuffer<512> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buffer);
    if (!root.success())
    {
        _ssid = nullptr;
        _password = nullptr;
        return false;
    }

    const char *ssid = root["ssid"];
    if (ssid != nullptr)
        _ssid = strdup(ssid);
    else
        _ssid = nullptr;
    const char *password = root["password"];
    if (password != nullptr)
        _password = strdup(password);
    else
        _password = nullptr;

    Serial.printf("SSID = %s\n", _ssid);
    Serial.printf("Password = %s\n", _password);

    if (_ssid == nullptr || _password == nullptr || strlen(_ssid) == 0 || strlen(_password) == 0)
    {
        _ssid = nullptr;
        _password = nullptr;
        return false;
    }

    return true;
}

void Settings::clearEEPROM()
{
    int i;
    EEPROM.begin(512);

    for (i = 0; i < 512; i++)
    {
        EEPROM.write(i, 0);
    }

    EEPROM.end();
}

void Settings::saveToEEPROM()
{
    char buffer2[512];
    EEPROM.begin(512);
    StaticJsonBuffer<512> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["ssid"] = ssid();
    root["password"] = password();
    root.printTo(buffer2);
    unsigned int i;
    for (i = 0; i < 512 && i < strlen(buffer2); i++)
    {
        EEPROM.write(i, buffer2[i]);
    }
    if (i < 512)
    {
        EEPROM.write(i, 0);
    }
    EEPROM.end();
}