#ifndef CHESSBOT_MAIN_CPP
#define CHESSBOT_MAIN_CPP

#include "Arduino.h"
#include "logging.h"
#include "wireless.h"
#include "connection.h"
#include "timer.h"
#include "control.h"
#include "status.h"

using namespace ChessBot;

void setup() {
  if (getLoggingStatus) {
    // Serial port for debugging purposes
    Serial.begin(115200);
  }

  // Any setup needed to get bot ready
  setupBot();
  // Create a WiFi network for the laptop to connect to
  connectWiFI();
}

void loop() {
	if (getConnectionStatus()) {
		//connectionTest();
		acceptData();
	}

    std::array<int, 4> lightValues = returnLightLevels();

    log((char*)"Light Levels: ");
    log(lightValues[0]);
    log((char*)" ");
    log(lightValues[1]);
    log((char*)" ");
    log(lightValues[2]);
    log((char*)" ");
    logln(lightValues[3]);

  	delay(100);
  	timerStep();
}

#endif
