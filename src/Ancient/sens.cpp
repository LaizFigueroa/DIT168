#include <unistd.h>						
#include <linux/i2c-dev.h>	
#include <fcntl.h>				
#include <sys/ioctl.h>	
#include <stdio.h>	

int file;
int bytes;
unsigned char data[100] = {0};

int main(){

	char *to_open = (char*)"/dev/i2c-1";
	int check1 = file = open(to_open, O_RDWR);

	int sensor = 0x70;

	int check2 = ioctl(file, I2C_SLAVE, sensor);

	data[0] = 0x51; //set to centimeters

	bytes = 2;			
	int check3 = write(file, data, bytes);
	
	bytes=4;
        int check4 = read(file, data, bytes); //read data from sensor
	
	printf("1:%d,2:%d,3:%d,4:%d",check1,check2,check3,check4);

}
