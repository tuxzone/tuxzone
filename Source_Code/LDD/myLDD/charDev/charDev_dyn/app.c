#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int fd,ret;
	char ubuff[20];
	memset((char*)ubuff,0,20);
	fd=open("/dev/myCharDev",O_RDWR,0777);
	if(fd<0){
		printf("Failed to open the device\n");
		return -1;
	}
	else{
		ret=read(fd,ubuff,sizeof(ubuff));
		printf("The data from kernel: %s\n",ubuff);
		strcpy(ubuff,"keel");
		write(fd,ubuff,sizeof(ubuff));
    	}
   close(fd);
return 0;
}
