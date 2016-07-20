#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;

#define MAX_ELEMENTS 3

typedef struct recieveBuffer{
	uint8_t repData[20];
	uint8_t free;
}RECBUFF;

typedef struct Buffer{
	RECBUFF recBuff[MAX_ELEMENTS];
	char  last;
	char first;
	uint8_t noItems;
}BUFFER;

	
