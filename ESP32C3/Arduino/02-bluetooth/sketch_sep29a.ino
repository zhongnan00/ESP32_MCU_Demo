#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; // In seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");                      // Initialize BLE
  pBLEScan = BLEDevice::getScan();          // Create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);            // Active scan uses more power, but gets results faster
  pBLEScan->setInterval(100);               // How often the scan is performed
  pBLEScan->setWindow(99);                  // Must be <= setInterval
}

void loop() {
  BLEScanResults* foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices->getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();                 // Free memory from results
  delay(2000);
}
