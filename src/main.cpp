#include "main.h"
#include "blink.h"
#include "blueTooth.h"
#include "timerTest.h"

ThreadController allTask;

void setup() {
	Serial.begin(115200);
	blinkSetup();
	blueToothSetup();
	timerTestSetup();
}

void loop() {
	allTask.run();
}
