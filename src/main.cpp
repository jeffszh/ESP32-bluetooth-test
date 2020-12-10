#include "main.h"
#include "blink.h"
#include "blueTooth.h"

ThreadController allTask;

void setup() {
	Serial.begin(115200);
	blinkSetup();
	blueToothSetup();
}

void loop() {
	allTask.run();
}
