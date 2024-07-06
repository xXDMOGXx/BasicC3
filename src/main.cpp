#ifndef BOT_MAIN_CPP
#define BOT_MAIN_CPP

#include "Arduino.h"
#include "logging.h"
#include "accessPoint.h"
#include "connection.h"
#include "timer.h"
#include "motor.h"
#include "status.h"

using namespace Bot;

void setup() {
  if (getLoggingStatus) {
    // Serial port for debugging purposes
    Serial.begin(115200);
    delay(3000);
  }

  // Any setup needed to get motors ready
  setupMotors();

  // Create a WiFi network for the laptop to connect to
  createAccessPoint();
}

void loop() {
	if (getConnectionStatus()) {
		connectionTest();
		acceptData();
	}

  	delay(10);
  	timerStep();
}

#endif
