#include <Arduino.h>

// static volatile SemaphoreHandle_t sem = xSemaphoreCreateBinary();
static portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
static volatile uint32_t timeTick = 0;

uint32_t getTimeTick() {
	portENTER_CRITICAL(&timerMux);
	uint32_t result = timeTick;
	portEXIT_CRITICAL(&timerMux);
	return result;
}

static void IRAM_ATTR onTimer() {
	portENTER_CRITICAL_ISR(&timerMux);
	timeTick++;
	portEXIT_CRITICAL_ISR(&timerMux);
}

void timerTestSetup() {
	hw_timer_t *timer = timerBegin(0, 80, true);
	timerAttachInterrupt(timer, onTimer, true);
	timerAlarmWrite(timer, 10000, true);
	timerAlarmEnable(timer);
}
