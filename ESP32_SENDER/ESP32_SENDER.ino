#include <esp_now.h>
#include <WiFi.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include "BluetoothSerial.h"

//ESP A

HardwareSerial SerialPort(2); // use UART2

// Variables for test data
int int_value;
float float_value;
bool bool_value = true;

// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0xC0, 0x49, 0xEF, 0xCD, 0x16, 0xE8};

// Define a data structure
typedef struct struct_message {
  uint8_t a;
} struct_message;

// Create a structured object
struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  //Serial.print("\r\nLast Packet Send Status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  
  // Set up Serial Monitor
  Serial.begin(115200);
 
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  //SET UART
  SerialPort.begin(115200, SERIAL_8N1, 17, 16); //17 rx 16 tx
}

void loop() {
  esp_err_t result;
  
  if(SerialPort.available())
  {
      //take data via UART
      myData.a = SerialPort.read();

      
      // Send message via ESP-NOW
      result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  }
}
