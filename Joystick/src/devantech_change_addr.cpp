#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <assert.h>
#include <chrono>
#include <thread>

using namespace std;

int main (int argc, char *argv[]) 
{
    if (argc != 4) {
        cout << "Invalid number of arguments. " << argc << endl;
        return -1;
    }
    char *end;
    unsigned long bus = strtol(argv[1], &end, 0);
    unsigned long device_addr = strtol(argv[2], &end, 0);
    uint8_t command = 0x00;
    unsigned long new_addr = strtol(argv[3], &end, 0);
    const int delay = 100;

    char filename[50];
    snprintf(filename, sizeof(filename), "/dev/i2c-%d", bus);
    filename[sizeof(filename) - 1] = '\0';
    
    new_addr = new_addr << 1;
    
    if (new_addr < 0xE0 || new_addr > 0xEE) {
        cout << "Unsupported new address." << endl;
        return -1;
    }
    int file = open(filename, O_RDWR);
    if (file < 0) {
        cout << "Failed to open the i2c bus: " << filename << "." << endl;
        return -1;
    }
    if (ioctl(file, I2C_SLAVE, device_addr) < 0) {
        cout << "Failed to acquire bus access or talk to device. Addr: " << device_addr << endl;
        return -1;
    }
    uint8_t buffer[2];
    buffer[0] = command;
    buffer[1] = 0xA0;
    if (write(file, buffer, 2) != 2) {
        cout << "Failed to send 0xA0 to device." << endl;
        return -1;
    }
    buffer[1] = 0xAA;
    this_thread::sleep_for(chrono::milliseconds(delay));
    if (write(file, buffer, 2) != 2) {
        cout << "Failed to send 0xAA to device." << endl;
        return -1;
    }
    buffer[1] = 0xA5;
    this_thread::sleep_for(chrono::milliseconds(delay));
    if (write(file, buffer, 2) != 2) {
        cout << "Failed to send 0xA5 to device." << endl;
        return -1;
    }
    buffer[1] = new_addr;
    this_thread::sleep_for(std::chrono::milliseconds(delay));
    if (write(file, buffer, 2) != 2) {
        cout << "Failed to change addr." << endl;
        return -1;
    }
    cout << "Successfully changed addr." << endl;
    return 0;
}
