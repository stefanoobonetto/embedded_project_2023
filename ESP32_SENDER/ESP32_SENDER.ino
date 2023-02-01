#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <HardwareSerial.h>

HardwareSerial SerialPort(2); // use UART2

// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0xC0, 0x49, 0xEF, 0xCD, 0x16, 0xE8};

// Define a data structure for WIFI
typedef struct struct_message {
  uint8_t a;
} struct_message;

struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

void initWIFI(){
   // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Initilize ESP-NOW
  esp_now_init();
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // Add peer        
  esp_now_add_peer(&peerInfo);
}

void setup() {
  
  // Set up Serial Monitor
  Serial.begin(115200);
  // Init wifi
  initWIFI();
  //SET UART
  SerialPort.begin(115200, SERIAL_8N1, 17, 16); //17 rx 16 tx
}

void loop() {
  if(SerialPort.available())
  {
      //take data via UART
      myData.a = SerialPort.read();
      // Send message via ESP-NOW
      esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  }
}
