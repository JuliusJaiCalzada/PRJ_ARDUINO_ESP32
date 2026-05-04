/*
Project: PRJ_ARDUINO_ESP32
Description: BLE (Bluetooth Low Energy) Template Implementation
*/

#include "BLETemplate.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// BLE Server and Service objects
BLEServer *pServer = nullptr;
BLECharacteristic *pCharacteristic = nullptr;
bool deviceConnected = false;

// BLE Service UUID
#define SERVICE_UUID        "180A"
#define CHARACTERISTIC_UUID "2A29"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
        BLEOnConnect();
    };

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        BLEOnDisconnect();
    }
};

void BLEInit(const char *deviceName)
{
    // Create the BLE Device
    BLEDevice::init(deviceName);

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ   |
        BLECharacteristic::PROPERTY_WRITE  |
        BLECharacteristic::PROPERTY_NOTIFY |
        BLECharacteristic::PROPERTY_INDICATE
    );

    // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
    pCharacteristic->addDescriptor(new BLE2902());

    pCharacteristic->setValue("ESP32 BLE");

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
    BLEDevice::startAdvertising();
}

void BLEOnConnect(void)
{
    // Called when a BLE client connects
}

void BLEOnDisconnect(void)
{
    // Called when a BLE client disconnects
    // Restart advertising
    delay(500);
    BLEDevice::getAdvertising()->start();
}

void BLEOnRead(void)
{
    // Called when a BLE client reads a characteristic
}

void BLEOnWrite(const char *value)
{
    // Called when a BLE client writes to a characteristic
}

bool BLEIsConnected(void)
{
    return deviceConnected;
}
