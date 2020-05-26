#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>

#include "Settings.hpp"
#include "Matrix.hpp"
#include "WebClient.hpp"

// IP address for the ESP8266 is displayed on the scrolling display
// after startup initialisation and connected to the WiFi network.
//
// Connections for ESP8266 hardware SPI are:
// Vcc       3v3     LED matrices seem to work at 3.3V
// GND       GND     GND
// DIN        D8     HSPID or HMOSI
// CS or LD   D9     HSPICS or HCS
// CLK        D10    CLK or HCLK
//

// Cf. https://majicdesigns.github.io/MD_MAX72XX/index.html

Settings settings;
Matrix matrix;
WebClient webClient;

bool connectToWiFi(const Settings &settings)
{
  Serial.printf("SSID = %s\n", settings.ssid());
  Serial.printf("Password = %s\n", settings.password());
  WiFi.begin(settings.ssid(), settings.password());
  for (unsigned int i = 0; i < 10; i++)
  {
    delay(2000);
    if (WiFi.isConnected())
    {
      return true;
    }
  }
  Serial.print("Connect failed\n");
  return false;
}

void setup()
{
  matrix.begin();

  Serial.begin(9600);

  delay(1000);

  if (settings.readFromEEPROM())
  {
    if (connectToWiFi(settings))
    {
      Serial.print("Connected\n");
      matrix.scrollText("Connected");
    }
    else
    {
      settings.clearEEPROM();
      Serial.print("Restart\n");
      ESP.restart();
    }
  }
  else
  {
    Serial.print("No WLAN settings\n");
    Serial.print("Please enter SSID\n");
    Serial.setTimeout(60000);
    String data = Serial.readStringUntil('\n');
    data.trim();
    settings.ssid(data);
    Serial.print("Please enter password\n");
    data = Serial.readStringUntil('\n');
    data.trim();
    settings.password(data);
    Serial.printf("SSID = %s\n", settings.ssid());
    Serial.printf("Password = %s\n", settings.password());
    settings.saveToEEPROM();
    Serial.print("Restart");
    ESP.restart();
  }
}

void loop()
{
  Message message = webClient.readMessage();
  matrix.scrollText(message.text());
}

