// TWELITE SPOT Router Example

// Arduino / ESP libraries
#include <Arduino.h>
#include <WiFi.h>

// Third-party libraries
#include <WebSocketsClient.h>

// Mono Wireless TWELITE Wings API for 32-bit Arduinos
#include <MWings.h>

// Pin defs
const uint8_t TWE_RST = 5;
const uint8_t TWE_PRG = 4;
const uint8_t LED = 18;
const uint8_t ESP_RXD1 = 16;
const uint8_t ESP_TXD1 = 17;

// TWELITE defs
const uint8_t TWE_CH = 18;
const uint32_t TWE_APPID = 0x67720102;
const uint8_t TWE_RETRY = 2;
const uint8_t TWE_POWER = 3;

// Wi-Fi defs
const char* WIFI_SSID = "YOUR SSID";
const char* WIFI_PASSWORD = "YOUR PASSWORD";

// WebSocket defs
const char* WS_SERVER_IP = "YOUR ADDRESS";
const int WS_SERVER_PORT = 8080;
const char* WS_SERVER_PATH = "/";

// Global objects
WebSocketsClient webSocket;

// Function prototypes
String createPacketStringFrom(const BarePacket& packet);

// Setup procedure
void setup() {
    // Init USB serial
    Serial.begin(115200);
    Serial.println("Hello, this is TWELITE SPOT.");

    // Init TWELITE
    Serial2.begin(115200, SERIAL_8N1, ESP_RXD1, ESP_TXD1);
    if (Twelite.begin(Serial2,
                      LED, TWE_RST, TWE_PRG,
                      TWE_CH, TWE_APPID, TWE_RETRY, TWE_POWER)) {
        Serial.println("Started TWELITE.");
    }
    //// Any
    Twelite.on([](const BarePacket& packet) {
        String packetStr = createPacketStringFrom(packet);
        if (not (packetStr.length() <= 0)) {
            webSocket.sendTXT(packetStr.c_str());
        }
    });

    // Init Wi-Fi
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.'); delay(500);
    }
    Serial.print("\nConnected. IP: ");
    Serial.println(WiFi.localIP().toString().c_str());

    // Init WebSocket
    webSocket.begin(WS_SERVER_IP, WS_SERVER_PORT, WS_SERVER_PATH);
    webSocket.setReconnectInterval(5000);
    webSocket.onEvent([](WStype_t type, uint8_t* payload, size_t length) {
        switch(type) {
        case WStype_DISCONNECTED: {
            Serial.printf("Disconnected!\n");
            break;
        }
        case WStype_CONNECTED: {
            Serial.printf("Connected to url: %s\n", payload);
            webSocket.sendTXT("This is TWELITE SPOT to ground control");
            break;
        }
        case WStype_TEXT: {
            Serial.printf("Got text: %s\n", payload);
            break;
        }
        default: break;
        }
    });
}

// Loop procedure
void loop() {
    Twelite.update();
    webSocket.loop();
}

// Create packet data string in App_Wings format from bare packets
String createPacketStringFrom(const BarePacket& packet) {
    if (packet.u16PayloadSize < (1024 - 3)) {
        String str = ":";
        for (int i = 0; i < packet.u16PayloadSize; i++) {
            const uint8_t bit74 = ((packet.u8Payload[i] >> 4) & 0xF);
            const uint8_t bit30 = ((packet.u8Payload[i] >> 0) & 0xF);
            str.concat(static_cast<char>((bit74 < 0xA) ? ('0' + bit74) : ('A' + bit74 - 0xA)));
            str.concat(static_cast<char>((bit30 < 0xA) ? ('0' + bit30) : ('A' + bit30 - 0xA)));
        }
        const uint8_t bit74 = ((packet.u8Checksum >> 4) & 0xF);
        const uint8_t bit30 = ((packet.u8Checksum >> 0) & 0xF);
        str.concat(static_cast<char>((bit74 < 0xA) ? ('0' + bit74) : ('A' + bit74 - 0xA)));
        str.concat(static_cast<char>((bit30 < 0xA) ? ('0' + bit30) : ('A' + bit30 - 0xA)));
        str.concat("\r\n");
        return str;
    }
    return String("");
}

/*
 * Copyright (C) 2023 Mono Wireless Inc. All Rights Reserved.
 * Released under MW-OSSLA-1J,1E (MONO WIRELESS OPEN SOURCE SOFTWARE LICENSE AGREEMENT).
 */
