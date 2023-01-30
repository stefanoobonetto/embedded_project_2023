#include "ESP32_Servo.h"
// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
#include <HardwareSerial.h>

Servo myservo;  // create servo object to control a servo
 
int servoPin = 2; // Servo motor pin
int isDritto = 1; //Boolean for know the position




void servoDX(){
  myservo.write(0);       // tell servo to go to position in variable 'pos'
  delay(1000);                   // waits 15ms for the servo to reach the position
}

void servoDRITTO(){
  myservo.write(80);       // tell servo to go to position in variable 'pos'
  delay(1000);                   // waits 15ms for the servo to reach the position
}

// Define a data structure
typedef struct struct_message {
  uint8_t a;
} struct_message;

// Create a structured object
struct_message myData;


// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  //Set servo position
  if(myData.a==201){
    if(isDritto){
      servoDX();
      isDritto=0;
    }
  }
  else{
    if(!isDritto){
      servoDRITTO();
      isDritto=1;
    }
  }

  Serial_1.print(myData.a);
}

HardwareSerial Serial_1(2); // use UART2
 
void setup() {  
 //Set UART COMMUNICATION
  Serial_1.begin(115200, SERIAL_8N1, 17, 16);
  // Set up Serial Monitor
  Serial.begin(115200);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
  
  //SETUP SERVO
  myservo.attach(servoPin, 500, 2500);  // attaches the servo on servoPin to the servo object
}
void loop() {

}




