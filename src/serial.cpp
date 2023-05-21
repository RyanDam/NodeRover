#include "main.h"
#include <ArduinoJson.h>

#define SERIAL_BAUDRATE 9600
#define BATTERY_PIN A0 

char buff[4];
long last_report_stamp_ = 0;
long report_duration_ = 1000;

Bencher battery;

void initSerial(uint32_t timeoutms) {
    Serial.begin(SERIAL_BAUDRATE);
    // uint32_t wait_start = millis();
    // int startupCharCount = 0;
    // while (startupCharCount < 3) {
    //     if (Serial.available()) {
    //         Serial.readBytes(buff, 1);
    //         if (buff[0] == '\n') startupCharCount++;
    //         continue;
    //     } 
    //     else if (millis() - wait_start > timeoutms) return;
    //     else {
    //         flashNoti(1);
    //         delay(1000);
    //     }
    // }
    flashNoti();
}

// int parseCmd() {
//     int cmd = int(buff[1]) - 48;
//     int sub = int(buff[2]) - 48;

//     if (sub == 9) return 999; // stop cmd
//     else return cmd;
// }

void updateSerial() {
    // Check if the other Arduino is transmitting
    if (Serial.available()) {
        // Allocate the JSON document
        // This one must be bigger than the sender's because it must store the strings
        StaticJsonDocument<256> command;

        // Read the JSON document from the "link" serial port
        DeserializationError err = deserializeJson(command, Serial);

        if (err == DeserializationError::Ok) {
            if (command["mode"] == "c") {
                // camera command
                handleCamCmd(command["cmd"].as<int>());
            } else if (command["mode"] == "r") {
                // robot command
                handleRobotCmd(command["cmd"].as<int>());
            }
        } else {
            // ERR
            // Flush all bytes in the "link" serial port buffer
            while (Serial.available() > 0) Serial.read();
        }
    } else {
        delay(10);
    }

    long now = millis();
    if (now - last_report_stamp_ > report_duration_) {
        last_report_stamp_ = now;
        
        int batRaw = analogRead(BATTERY_PIN);
        float bat = ((float)batRaw / 1024) * 3.3f * 2.0f;
        battery.push(bat);

        StaticJsonDocument<256> report;

        report["batt"] = battery.avg();

        uint32_t fh, mh;
        uint8_t frh;
        ESP.getHeapStats(&fh, &mh, &frh);

        report["heap_free"] = fh;
        report["heap_max"] = mh;
        report["heap_frag"] = frh;

        serializeJson(report, Serial);
    }
}
