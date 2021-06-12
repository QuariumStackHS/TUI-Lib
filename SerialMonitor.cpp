#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <errno.h>   // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

class SerialMonitor
{
public:
    SerialMonitor(char *Port)
    {
        int serial_port = open(Port, O_RDWR);

        // Check for errors
        if (serial_port < 0)
        {
            printf("Error %i from open: %s\n", errno, strerror(errno));
        }
        // Read in existing settings, and handle any error
        // NOTE: This is important! POSIX states that the struct passed to tcsetattr()
        // must have been initialized with a call to tcgetattr() overwise behaviour
        // is undefined
        tty.c_cflag &= ~PARENB;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;
        tty.c_lflag &= ~ICANON;
        cfsetispeed(&tty, B9600);
        cfsetospeed(&tty, B9600);

        if (tcgetattr(serial_port, &tty) != 0)
        {
            printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        }
    }
private:
        struct termios tty;
    
};