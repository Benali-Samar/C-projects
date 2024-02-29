#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

int main() {
    const char *port = "/dev/ttyS1";
    int fd;
    // Open serial port
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
    cfsetospeed(&tty, B115200); // Set baud rate
    cfsetispeed(&tty, B115200);
    tty.c_cflag |= (CLOCAL | CREAD); // Enable receiver and set local mode
    tty.c_cflag &= ~PARENB; // No parity bit
    tty.c_cflag &= ~CSTOPB; // One stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; // 8 bits per byte
    tty.c_cc[VMIN] = 0; // Minimum number of characters to read
    tty.c_cc[VTIME] = 10; // Timeout in deciseconds
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error in tcsetattr");
        close(fd);
        return 1;
    }
   //unsigned char command[] = {00010110 00010110 00010110 00000001 00000000 00001000 00000010 00110000 00110000 00110000 00110000 00000011 00000001 00000100}; // Get_Device_info
   //unsigned char command[] = {0b00010110, 0b00010110, 0b00010110, 0b00000001, 0b00000000, 0b00001000, 0b00000010, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00000011, 0b00000001, 0b00000100}; // status of the device
   unsigned char command[] = {0b00010110, 0b00010110, 0b00010110, 0b00000001, 0b00000000, 0b00001000, 0b00000010, 0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00000011, 0b00000001, 0b00000100}; //get device info

    if (write(fd, command, sizeof(command)) < 0) {
        perror("Error writing to serial port");
        close(fd);
        return 1;
    }
    	char response[255];
	int bytesRead = read(fd,response,sizeof(response));
	printf("recieved response size readed %d\n", bytesRead);
	if(bytesRead > 0){
		for (int i = 0; i < bytesRead; i++) {
        printf("%02X ", response[i]);
    }
    printf("\n");
 printf("Response in hexadecimal string format:\n");
        for (int i = 0; i < bytesRead; i++) {
            printf("%02X", response[i]);
        }
	} else {
		 perror("Error reading from serial port");
	}
    close(fd);
    printf("Serial port closed.\n");

    return 0;
}
