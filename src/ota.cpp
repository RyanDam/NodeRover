
#include "main.h"

/** Flag if OTA is enabled */
boolean otaStarted = false;

/** Limit the progress output on serial */
unsigned int lastProgress = 0;

/**
 * Initialize OTA server
 * and start waiting for OTA requests
 */
void startOTA()
{
	ArduinoOTA.onStart([]() {
		// Serial.println("Start");
	});
	ArduinoOTA.onEnd([]() {
		// Serial.println("\nEnd");
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		// Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
	});
	ArduinoOTA.onError([](ota_error_t error) {
		// Serial.printf("Error[%u]: ", error);
		// if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
		// else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
		// else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
		// else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
		// else if (error == OTA_END_ERROR) Serial.println("End Failed");
	});
	ArduinoOTA.begin();
	// Serial.println("Ready");
	// Serial.print("IP address: ");
	// Serial.println(WiFi.localIP());
}

/**
 * Stop the OTA server
 */
void stopOTA()
{
	ArduinoOTA.end();
}

void updateOTA() {
	if (otaStarted)
	{
		ArduinoOTA.handle();
	}
}

void enableOTA() {
	// If OTA is not enabled
	if (!otaStarted)
	{
		delay(100);
		// Serial.println("OTA enabled");
		// Start the OTA server2
		startOTA();
		otaStarted = true;
	}
	else
	{
		// If OTA was enabled
		otaStarted = false;
		// Stop the OTA server2
		stopOTA();
		// Restart the camera server2s
  }
}