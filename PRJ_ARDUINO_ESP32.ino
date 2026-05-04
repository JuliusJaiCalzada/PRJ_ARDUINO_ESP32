// PRJ_ARDUINO_ESP32
// ESP32 Blink Sketch with BLE Support

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define LED_PIN 2  // ESP32 built-in LED pin
#define BLE_DEVICE_NAME "ESP32_BLE"

// BLE Server and Service objects
BLEServer *pServer = nullptr;
bool deviceConnected = false;

// BLE Service and Characteristic UUID
#define SERVICE_UUID        "180A"
#define CHARACTERISTIC_UUID "2A29"

// BLE Server Callbacks
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
    };
    
    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
    }
};

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  
  // Create the BLE Device
  BLEDevice::init(BLE_DEVICE_NAME);
  
  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  
  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);
  
  // Create a BLE Characteristic
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ   |
    BLECharacteristic::PROPERTY_WRITE  |
    BLECharacteristic::PROPERTY_NOTIFY |
    BLECharacteristic::PROPERTY_INDICATE
  );
  
  // Add descriptor for notifications
  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setValue("ESP32 BLE");
  
  // Start the service
  pService->start();
  
  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);
  BLEDevice::startAdvertising();
  
  Serial.println("BLE initialized successfully");
}

void loop() {
  // Turn the LED on
  digitalWrite(LED_PIN, HIGH);
  delay(1000);  // Wait for 1 second

  // Turn the LED off
  digitalWrite(LED_PIN, LOW);
  delay(1000);  // Wait for 1 second
}