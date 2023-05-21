#include "main.h"

void initWifi() {
  // Serial.print("Connecting to ");

  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  wifiManager.setDebugOutput(false);

  // Uncomment and run it once, if you want to erase all the stored information
  // wifiManager.resetSettings();

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("ESP_Robot", "12345678");
  
  // if you get here you have connected to the WiFi
  // Serial.println("Connected.");

  // Serial.println("Server started");
  // Serial.print("Use this URL to connect: ");
  // Serial.print("http://");    //URL IP to be typed in mobile/desktop browser
  // Serial.print(WiFi.localIP());
  // Serial.println("/");
}

void setup() {
  // INIT LED
  // Serial.println("Init LED");
  pinMode(LED_BUILTIN, OUTPUT);

  // INIT MOTORS
  // Serial.println("Init Motors");
  initRobotMotors();

  // INIT SERVO
  // Serial.println("Init Servos");
  initArmServos();

  // INIT WEB CONTROLLER
  // Serial.println("Init Wifi");
  initWifi();

  flashNoti();

  initWebServer();

  // connection to Camera
  initSerial();

  // digitalWrite(LED_BUILTIN, );
}

void loop() {
  updateSerial();
  updateWebServer();
  updateRobotMotors();
  updateArmServors();
  updateOTA();
}

void flashNoti(int num) {
  for(int i = 0; i < num; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
  }
}