#include <WiFi.h>
#include <Arduino.h>

#include "joystick.h"

uint32_t io   = 0;
uint16_t ac   = 0;
uint16_t dev  = 0;

//*********************************************************************
//please insert your data here
//*********************************************************************
// WiFi Configuration
const char* ssid = "YourSsidHere";
const char* password = "YourPassHere";
//insert the correct ip of your pidp1
const char* pdp1_host = "192.168.178.187";  // pidp1 virtual console (laptop)
const uint16_t pdp1_port = 7700;

//from this point you must nothing change
//*********************************************************************
//
//*********************************************************************

WiFiClient client;

// Packet structure
#define PACKET_SIZE 8
#define DIR_INPUT  0x00
#define DIR_OUTPUT 0x80


void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("PDP-1 Joystick-controller");
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Connect to PDP-1
  connectToPDP1();
}

void connectToPDP1() {
  Serial.print("Connecting to PDP-1 at ");
  Serial.print(pdp1_host);
  Serial.print(":");
  Serial.println(pdp1_port);
  
  while(!client.connect(pdp1_host, pdp1_port)) {
    Serial.println("Connection failed, retrying...");
    delay(1000);
  }
  
  Serial.println("Connected to PDP-1!");
}

void loop() {
  // Check if still connected
  if(!client.connected()) {
    Serial.println("Disconnected from PDP-1, reconnecting...");
    connectToPDP1();
    return;
  }
  
  // Check for incoming packets
  if(client.available() >= PACKET_SIZE) {
    handlePacket();
  }
  
  delay(1);  // Small delay to prevent watchdog issues
}

void handlePacket() {
  uint8_t packet[PACKET_SIZE];
  
  // Read packet
  int bytesRead = client.readBytes(packet, PACKET_SIZE);
  if(bytesRead != PACKET_SIZE) {
    Serial.println("Incomplete packet received");
    return;
  }
  
  // Parse packet
  uint8_t device_id = packet[0] & 0x3F;
  bool is_output = (packet[0] & DIR_OUTPUT) != 0;
  
  //device octal 15 from the pidp1 - here we are 13 as integer 
  if(device_id == 13){
    handleInputDevice(device_id, packet);
  }

}

void handleInputDevice(uint8_t device_id, uint8_t* packet) {
  Serial.print("Input Device (");
  Serial.print(device_id);
  Serial.println(") requested");
  
  // Read joystick values 
  uint8_t joyA_value = JoystickA_read();
  uint8_t joyB_value = JoystickB_read();
  
  uint32_t io_value = 0;
  //joystick A from bit 0-7
  io_value |= joyA_value;
  //joystick B from bit 8-15
  io_value |= ((uint32_t)joyB_value << 8);
  //debug output displays both joystick values in io_value
  Serial.print("Joysticks ");
  for (int i = 15; i >= 0; i--) {
    Serial.print((io_value >> i) & 1);
    if (i == 8) Serial.print(" "); // Trennung zwischen den beiden Joysticks
  }
  Serial.println();

  // Send response packet
  uint8_t response[PACKET_SIZE];
  memset(response, 0, PACKET_SIZE);
  
  // Byte 0: Device ID | Direction (input)
  response[0] = device_id & 0x3F;
  
  // Bytes 1-3: IO value (18 bits)
  response[1] = (io_value >> 12) & 0x3F;
  response[2] = (io_value >> 6) & 0x3F;
  response[3] = io_value & 0x3F;
  
  // Bytes 4-7: Reserved
  response[4] = 0;
  response[5] = 0;
  response[6] = 0;
  response[7] = 0;
  
  client.write(response, PACKET_SIZE);
  
  Serial.print("Sent IO value: ");
  Serial.println(io_value, OCT);
}


