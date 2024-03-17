/*
 *@brief Serial communication using poll() instead of read()
 * Basic simple send and recieve data over serial with poll to get data from 
 * the character device whenever it is available.
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <poll.h> 

#define MAX_RESPONSE_SIZE 10000

void printReceivedData(unsigned char *data, int length) {
    std::cout << "Received data: ";
    for (int i = 0; i < length - 1; i++) {
        std::cout << data[i];
    }
    std::cout << std::endl;
}

unsigned char calculate_xor(unsigned char *data, int length) {
    int stx_index = -1;
    int etx_index = -1;
    for (int i = 0; i < length; i++) {
        if (data[i] == 0x02) {
            stx_index = i;
        } else if (data[i] == 0x03 && stx_index != -1) {
            etx_index = i;
            break; 
        }
    }

    if (stx_index == -1 || etx_index == -1) {
        std::cerr << "Error: STX or ETX not found in the data." << std::endl;
        return 0;
    }
    // calcule XOR from ETX to STX including
    unsigned char xor_result = 0;
    for (int i = stx_index; i <= etx_index; i++) {
        xor_result ^= data[i];
    }

    return xor_result;
}

int main() {
    const char *port = "/dev/ttyS3";
    int fd;
    fd = open(port, O_RDWR);
    if (fd == -1) {
        perror("Failed to open serial port");
        return 1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error in tcgetattr");
        close(fd);
        return 1;
    }
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cc[VMIN] = 0; 
    tty.c_cc[VTIME] = 1;  
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error in tcsetattr");
        close(fd);
        return 1;
    }
i
    std::map<std::string, std::vector<unsigned char>> commands = {
        {"CMD_STATUS", {0x16, 0x16, 0x16, 0x01, 0x00, 0x08, 0x02, 0x30, 0x30, 0x30, 0x30, 0x03, 0x01, 0x04}},
        {"CMD_DEVICE_INFO", {0x16, 0x16, 0x16, 0x01, 0x00, 0x08, 0x02, 0x30, 0x33, 0x30, 0x30, 0x03, 0x02, 0x04}},
        {"CMD_AUTOREJECTION", {0x16, 0x16, 0x16, 0x01, 0x00, 0x08, 0x02, 0x30, 0x30, 0x33, 0x34, 0x03, 0x06, 0x04}},
        {"CMD_EJECT", {0x16, 0x16, 0x16, 0x01, 0x00, 0x08, 0x02,  0x31, 0x31, 0x36, 0x30, 0x30, 0x30, 0x03, 0x07, 0x04}} 
    };

    std::string selectedCommand = "CMD_EJECT";
    auto it = commands.find(selectedCommand);
    if (it != commands.end()) {
        std::cout << "Sending command: " << selectedCommand << std::endl;
        std::vector<unsigned char>& command = it->second;
        std::cout << "Command to send (" << command.size() << " bytes in hexadecimal):" << std::endl;
        for (int i = 0; i < command.size(); i++) {
            std::cout << std::hex << static_cast<int>(command[i]) << " ";
        }
        std::cout << std::endl;

        // XOR for LRC of the command
        unsigned char xor_result = calculate_xor(command.data(), command.size());
        printf("XOR Result: 0x%02X\n", xor_result);
        // Append XOR to the command
        // command.push_back(xor_result);  // with the 0x04 at the end and the 0x03 before the xor value!

        if (write(fd, command.data(), command.size()) < 0) {
            perror("Error writing to serial port");
            close(fd);
            return 1;
        }

        std::cout << "Waiting for response..." << std::endl;

        unsigned char response[MAX_RESPONSE_SIZE];
        int responseIndex = 0;
        //reading data in non-blocking mode using poll
        struct pollfd fds[1];
        fds[0].fd = fd;
        fds[0].events = POLLIN; // Check for data to read
        int timeout = 100; // Timeout in milliseconds
        int ret = poll(fds, 1, timeout);
        if (ret == -1) {
            perror("poll() failed");
            close(fd);
            return 1;
        } else if (ret == 0) {
            std::cout << "Timeout reached. No data available." << std::endl;
            close(fd);
            return 1;
        } else {
            if (fds[0].revents & POLLIN) {
                std::cout << "Data is available for reading." << std::endl;
                int bytesRead = read(fd, response + responseIndex, MAX_RESPONSE_SIZE - responseIndex);
                if (bytesRead > 0) {
                    std::cout << "Bytes read: " << bytesRead << std::endl;
                    responseIndex += bytesRead;
                } else if (bytesRead == 0) {
                    std::cout << "No more data available. Closing connection." << std::endl;
                } else {
                    perror("Error reading from serial port");
                    std::cout << "Error code: " << errno << std::endl;
                    close(fd);
                    return 1;
                }
            }
        }

        std::cout << "Received data: ";
        for (int j = 0; j < responseIndex; j++) {
            std::cout << std::hex << static_cast<int>(response[j]) << " ";
        }
        std::cout << std::endl;

        printReceivedData(response, responseIndex);

    } else {
        std::cout << "Command not found: " << selectedCommand << std::endl;
    }

    close(fd);

    return 0;
}

