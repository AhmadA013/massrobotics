#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "robot-wifi";
const char *password = "123456789";

const uint SERVER_PORT = 22;
WiFiServer server(SERVER_PORT);

void setup()
{
    Serial.begin(9600);
    Serial.println("Hello world");

    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    server.begin();
}

void loop()
{
    WiFiClient client = server.available(); 

    if (client) {
        Serial.println("New Client."); 
        Serial.println(client.localIP());
        while (client.connected()) {            // loop while the client's connected
            if (client.available()) { 
                String msg = client.readString();
                Serial.print(msg);
            }
        }
    }
}