#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <PxMatrix.h>
#include <RTClib.h>
#include <Ticker.h>
#include <WiFiUdp.h>

#define TIMEZONE 7
#define P_LAT 0
#define P_OE 3
#define P_A 1
#define P_B 2
#define P_C 15
#define P_D 12

const char *ssid = "P08";
const char *password = "1234567890";

Ticker display_ticker;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D);
RTC_DS1307 rtc;

unsigned long task1 = 0;
boolean updated = false;

void display_updater() { display.display(70); }

void setup() {
    Serial.begin(115200);
    rtc.begin();
    display.begin(16);
    display_ticker.attach(0.004, display_updater);
    WiFi.begin(ssid, password);
    timeClient.begin();
    timeClient.setTimeOffset(TIMEZONE * 3600);
    task1 = millis();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED && updated == false) {
        timeClient.update();
        rtc.adjust(DateTime(timeClient.getYear(),
                            timeClient.getMonth(),
                            timeClient.getDate(),
                            timeClient.getHours(),
                            timeClient.getMinutes(),
                            timeClient.getSeconds()));
        updated = true;
    }
    if ((unsigned long)(millis() - task1) > 1000) {
        DateTime now = rtc.now();
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
        display.printf("%02d", now.hour());
        display.setTextColor(display.color565(255, 255, 255));
        display.print(":");
        display.setTextColor(display.color565(255, 0, 255));
        display.printf("%02d", now.minute());
        display.setTextColor(display.color565(255, 255, 255));
        display.print(":");
        display.setTextColor(display.color565(255, 255, 0));
        display.printf("%02d", now.second());
        task1 = millis();
    }
}
