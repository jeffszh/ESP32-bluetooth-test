#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEUtils.h>

#include "main.h"

constexpr int scanTime = 5; //In seconds
static BLEScan *pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
	void onResult(BLEAdvertisedDevice advertisedDevice) {
		Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
	}
};

static void blueToothLoop() {
	Serial.println("Scanning...");
	BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
	Serial.print("Devices found: ");
	Serial.println(foundDevices.getCount());
	Serial.println("Scan done!");
	pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
	// delay(2000);
}

void blueToothSetup() {
	BLEDevice::init("");
	pBLEScan = BLEDevice::getScan(); //create new scan
	pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
	pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
	pBLEScan->setInterval(100);
	pBLEScan->setWindow(99); // less or equal setInterval value

	static Thread blueToothTask;
	blueToothTask.enabled = true;
	blueToothTask.onRun(blueToothLoop);
	blueToothTask.setInterval(2000);
	allTask.add(&blueToothTask);
}
