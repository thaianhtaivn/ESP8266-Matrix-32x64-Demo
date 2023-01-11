#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <PxMatrix.h>
#include <Ticker.h>
#include <WiFiUdp.h>

#define P_LAT 0
#define P_OE 3
#define P_A 1
#define P_B 2
#define P_C 15
#define P_D 12

#define TIMEZONE 7
const char *ssid = "P08";
const char *password = "1234567890";

Ticker display_ticker;
PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void display_updater() { display.display(70); }

unsigned long task01 = 0;

void setup() {
    Serial.begin(115200);

    display.begin(16);
    display_ticker.attach(0.004, display_updater);
    display.setCursor(2, 0);
    display.setTextColor(display.color565(255, 0, 0));
    display.print("P");
    display.setTextColor(display.color565(0, 255, 0));
    display.print("i");
    display.setTextColor(display.color565(0, 0, 255));
    display.print("x");
    display.setTextColor(display.color565(0, 255, 255));
    display.print("e");
    display.setTextColor(display.color565(255, 255, 255));
    display.print("l");

    WiFi.begin(ssid, password);

    display.setCursor(0, 10);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        display.print(".");
    }
    timeClient.begin();
    timeClient.setTimeOffset(TIMEZONE * 3600);

    task01 = millis();
}

void loop() {
    if ((unsigned long)(millis() - task01) > 1000) {
        timeClient.update();
        display.clearDisplay();

        display.setCursor(2, 0);
        display.setTextColor(display.color565(255, 0, 0));
        display.print("P");
        display.setTextColor(display.color565(0, 255, 0));
        display.print("i");
        display.setTextColor(display.color565(0, 0, 255));
        display.print("x");
        display.setTextColor(display.color565(0, 255, 255));
        display.print("e");
        display.setTextColor(display.color565(255, 255, 255));
        display.print("l");

        display.setCursor(2, 10);
        display.setTextColor(display.color565(0, 255, 255));
        display.printf("%02d", timeClient.getHours());
        display.setTextColor(display.color565(255, 255, 255));
        display.print(":");
        display.setTextColor(display.color565(255, 0, 255));
        display.printf("%02d", timeClient.getMinutes());
        display.setTextColor(display.color565(255, 255, 255));
        display.print(":");
        display.setTextColor(display.color565(255, 255, 0));
        display.printf("%02d", timeClient.getSeconds());

        task01 = millis();
    }
}
