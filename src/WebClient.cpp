#include "WebClient.hpp"
#include <Esp.h>
#include <ESP8266HTTPClient.h>

Message WebClient::readMessage() {
    Message message;
    
    HTTPClient client;
    client.begin("https://nodemcu.azurewebsites.net/api/nodemcu");
    if (client.GET() == HTTP_CODE_OK) {
        client.getString();
    }

    return message;
}