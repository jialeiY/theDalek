#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

using namespace std;

int main() {
	cout << "hello wrold" << endl;
	int ttyFd = open("/dev/ttyS3", O_RDWR | O_NOCTTY | O_NDELAY);

	if (ttyFd <= 0) {
		printf("open file error\r\n");
	} else {
		printf("open file success\r\n");
	}
	termios options;
	tcgetattr(ttyFd, &options);
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB;//8N1
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CRTSCTS; //disable hardware control
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //turn off canonical input, choosing raw input
	options.c_iflag &= ~(IXON | IXOFF | IXANY);	//disable software flow control
	options.c_oflag &= ~OPOST;	//raw output
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	tcsetattr(ttyFd, TCSANOW, &options);
	
	// Set Block read
	fcntl(ttyFd, F_SETFL, 0);

	char buffer[256];

	while (true) {
		int lenRead = read(ttyFd, buffer, 256);
		for (int i=0; i<lenRead; ++i) {
			printf("%c", buffer[i]);
		}
	}
	


	close(ttyFd);

	
}