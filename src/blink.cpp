#include "blink.h"
#include "main.h"

static void blinkLoop() {
	static int phase = 0;
	switch (phase) {
	case 0:
	case 2:
	case 5:
		digitalWrite(BUILTIN_LED, HIGH);
		break;
	case 1:
	case 3:
	case 6:
		digitalWrite(BUILTIN_LED, LOW);
		break;
	case 7:
		Serial.println("很好！");
		break;
	default:
		break;
	}
	phase++;
	if (phase >= 10) {
		phase = 0;
	}
}

void blinkSetup() {
	pinMode(BUILTIN_LED, OUTPUT);

	static Thread blinkTask;
	blinkTask.enabled = true;
	blinkTask.onRun(blinkLoop);
	blinkTask.setInterval(200);
	allTask.add(&blinkTask);
}
