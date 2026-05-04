/*
Project: PRJ_ARDUINO_ESP32
Description: BLE (Bluetooth Low Energy) Template Header
*/

#ifndef BLE_TEMPLATE_H
#define BLE_TEMPLATE_H

// BLE initialization
void BLEInit(const char *deviceName);

// BLE event handlers
void BLEOnConnect(void);
void BLEOnDisconnect(void);

// BLE characteristic read/write handlers
void BLEOnRead(void);
void BLEOnWrite(const char *value);

// BLE status check
bool BLEIsConnected(void);

#endif // BLE_TEMPLATE_H
