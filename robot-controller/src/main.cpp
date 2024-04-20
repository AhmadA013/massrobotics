#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "robot-wifi";
const char *password = "123456789";

IPAddress serverIp(192,168,4,2);
uint serverPort = 8080;

WiFiClient client;


void setup()
{
    Serial.begin(9600);
    Serial.println("Hello world");

    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

  while (!client.connect(serverIp, serverPort)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected!");

}

void loop() {
    if (client.connected()) {
    // Check if data is available to read
        if (client.available()) {
      // Read 5 bytes from the server
            char buffer[6]; // 5 bytes + null terminator
            int bytesRead = client.readBytes(buffer, 5);
            if (bytesRead == 5) {
                buffer[5] = '\0'; // null terminator
                Serial.print("Received: ");
                Serial.println(buffer);
      }
    }
  } 
}
