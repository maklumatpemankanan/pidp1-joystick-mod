#ifndef PDP1_JOYSTICK_H
#define PDP1_JOYSTICK_H

typedef struct PDP1 PDP1;

// ESP32 Communication Protocol
// Packet format for output devices (PDP-1 -> ESP32):
//   Byte 0:    Device ID (6 bits) | Direction bit (1=output, 0=input) | Reserved
//   Byte 1-3:  IO value (18 bits, 3 bytes)
//   Byte 4-5:  AC value (12 bits, 2 bytes) - only bits 0-11 from 18-bit AC
//   Byte 6-7:  Reserved for future use
//
// Packet format for input devices (ESP32 -> PDP-1):
//   Byte 0:    Device ID (6 bits) | Direction bit (0=input) | Reserved  
//   Byte 1-3:  IO value (18 bits, 3 bytes)
//   Byte 4-7:  Reserved
//
// Packet format for pseudo device 99 (esp32 -> PDP-1) sends only Programflags
//   Byte 0:    progranflags1-6 (6 bits)



#define ESP32_PACKET_SIZE 8

// Initialize ESP32 connection (called when ESP32 connects to server)
void pdp1_joy_init(PDP1 *pdp, int fd);

// Send data to ESP32 for output device
void pdp1_joy_output(PDP1 *pdp, int device_id);

// Request data from ESP32 for input device (returns 1 if data received, 0 otherwise)
int pdp1_joy_input(PDP1 *pdp, int device_id);

// Cleanup (called on shutdown)
void pdp1_joy_cleanup(PDP1 *pdp);

#endif // PDP1_JOYSTICK_H
