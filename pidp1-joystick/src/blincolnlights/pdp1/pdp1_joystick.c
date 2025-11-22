#include "common.h"
#include "pdp1.h"
#include "pdp1_joystick.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>


// Device direction bits
#define ESP32_DIR_INPUT  0x00
#define ESP32_DIR_OUTPUT 0x80

void
pdp1_joy_init(PDP1 *pdp, int fd)
{
    if(pdp->esp32_fd >= 0) {
        // Already connected, close old connection
        close(pdp->esp32_fd);
    }
    
    pdp->esp32_fd = fd;
    nodelay(fd);  // Non-blocking
    
    printf("ESP32 connected on fd %d\n", fd);
}

int
pdp1_joy_input(PDP1 *pdp, int device_id)
{
    if(pdp->esp32_fd < 0)
        return 0;  // Not connected
    
    if(device_id < 0 || device_id >= 64)
        return 0;  // Invalid device ID
    
    // Send request packet
    uint8_t request[ESP32_PACKET_SIZE];
    memset(request, 0, ESP32_PACKET_SIZE);
    
    // Byte 0: Device ID | Direction (0 = input request)
    request[0] = (device_id & 0x3F) | ESP32_DIR_INPUT;
    
    int n = write(pdp->esp32_fd, request, ESP32_PACKET_SIZE);
    if(n < ESP32_PACKET_SIZE) {
        fprintf(stderr, "ESP32 write request failed: %s\n", strerror(errno));
        close(pdp->esp32_fd);
        pdp->esp32_fd = -1;
        return 0;
    }
    
    // Read response packet
    uint8_t response[ESP32_PACKET_SIZE];
    
    // Try to read with a short timeout
    // Since socket is non-blocking, we need to poll for data
    fd_set readfds;
    struct timeval tv;
    FD_ZERO(&readfds);
    FD_SET(pdp->esp32_fd, &readfds);
    tv.tv_sec = 0;
    tv.tv_usec = 10000;  // 10ms timeout
    
    int ret = select(pdp->esp32_fd + 1, &readfds, NULL, NULL, &tv);
    if(ret <= 0) {
        // Timeout or error
        return 0;
    }
    
    n = read(pdp->esp32_fd, response, ESP32_PACKET_SIZE);
    if(n < ESP32_PACKET_SIZE) {
        if(n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
            fprintf(stderr, "ESP32 read failed: %s\n", strerror(errno));
            close(pdp->esp32_fd);
            pdp->esp32_fd = -1;
        }
        return 0;
    }
    
    // Verify device ID matches
    if((response[0] & 0x3F) != device_id) {
        fprintf(stderr, "ESP32 device ID mismatch: expected %d, got %d\n", 
                device_id, response[0] & 0x3F);
        return 0;
    }
    
    // Extract IO value (18 bits from bytes 1-3)
    Word io_value = 0;
    io_value |= ((Word)response[1] & 0x3F) << 12;  // Bits 12-17
    io_value |= ((Word)response[2] & 0x3F) << 6;   // Bits 6-11
    io_value |= ((Word)response[3] & 0x3F);        // Bits 0-5
    
    // Write to IO register
    IO = io_value & WORDMASK;  // Ensure it's 18 bits
    
    return 1;  // Success
}

void
pdp1_joy_cleanup(PDP1 *pdp)
{
    if(pdp->esp32_fd >= 0) {
        printf("Closing ESP32 connection\n");
        close(pdp->esp32_fd);
        pdp->esp32_fd = -1;
    }
}
