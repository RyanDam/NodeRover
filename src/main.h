#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "bencher.h"

void flashNoti(int num = 2);

// web server
extern ESP8266WebServer server;   // instantiate server at port 80 (http port)

void initWebServer();
void updateWebServer();

// robot base
struct RobotMotors;
extern RobotMotors robot;

void initRobotMotors();
void updateRobotMotors();
void handleRobotCmd(int dirCode);

// camera arm
struct CamArmServo;
extern CamArmServo cameraArm;

void initArmServos();
void updateArmServors();
void handleCamCmd(int dirCode);

// ota
extern boolean otaStarted;
void startOTA();
void stopOTA();
void updateOTA();
void enableOTA();

// serial
extern char buff[];
void initSerial(uint32_t timeoutms = 15*1000); // 15 seconds
void updateSerial();
