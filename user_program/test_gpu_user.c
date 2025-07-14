#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(){
	int  fd = open("/dev/mini_gpu", O_RDWR);
	if (fd < 0){
		perror("Failed to open device");
		return 1;
	}

	printf("Successfully opened /dev/mini_gpu\n");
	//example write
	const char *msg = "Hello GPU!";
	write(fd, msg, strlen(msg));

	//example read (adjust buffer size)
	char buffer[128];
	read(fd, buffer, sizeof(buffer));
	printf("Read from device: %s\n", buffer);

	close(fd);
	return 0;
}
