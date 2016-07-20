#include <stdio.h>
#include "buffer.h"


void initialize_ring_buffer(BUFFER * buffer)
{	
	int i,j;
	buffer->last=0;
	buffer->noItems=0;
	for (i=0;i<MAX_ELEMENTS;i++){
			buffer->recBuff[i].free = 1;
			memset(buffer->recBuff[i].repData,0,sizeof(buffer->recBuff[i].repData));
	}
	
}

int isEmpty (BUFFER * buffer)
{
	return (buffer->noItems == 0);
}

int isFull(BUFFER * buffer)
{
	return (buffer->noItems == MAX_ELEMENTS);
}

int getBuffer(BUFFER *buffer)
{
	int index;
	if(isFull(buffer)){
		printf("Queue is full, no buffer can be alloted \n");
		return -1;
	}
	
	while(!buffer->recBuff[buffer->last].free)
	    buffer->last = (buffer->last+1)%MAX_ELEMENTS;
    
	buffer->noItems++;
	index = buffer->last;
	buffer->recBuff[index].free = 0;
	

  return index;
}

int returnBuffer(BUFFER *buffer,int index)
{
	if(isEmpty(buffer)){
		printf("Ring buffer completely available \n");
		return -1;
	}
	buffer->noItems--;
    buffer->recBuff[index].free = 1;
	
 return 0;	

}

int main()
{
	int index;
	buffer buffer;
	initialize_ring_buffer(&buffer);
	
	index = get_ring_buff(&buffer);
	if(index>=0){
	buffer.recBuff[index].repData[0]=1;
	buffer.recBuff[index].repData[1]=1;
	buffer.recBuff[index].repData[2]=1;
	printf("ring buffer at index % is %d %d %d\n",index,buffer.recBuff[index].repData[0],buffer.recBuff[index].repData[1],buffer.recBuff[index].repData[2]);
	}
	index = get_ring_buff(&buffer);
	if(index>0){
	buffer.recBuff[index].repData[0]=2;
	buffer.recBuff[index].repData[1]=2;
	buffer.recBuff[index].repData[2]=2;
	printf("ring buffer at index % is %d %d %d\n",index,buffer.recBuff[index].repData[0],buffer.recBuff[index].repData[1],buffer.recBuff[index].repData[2]);
	}
	index = get_ring_buff(&buffer);
	if(index>0){
	buffer.recBuff[index].repData[0]=3;
	buffer.recBuff[index].repData[1]=3;
	buffer.recBuff[index].repData[2]=3;
	printf("ring buffer at index % is %d %d %d\n",index,buffer.recBuff[index].repData[0],buffer.recBuff[index].repData[1],buffer.recBuff[index].repData[2]);
	}
	index = get_ring_buff(&buffer);
	if(index>0){

	buffer.recBuff[index].repData[0]=4;
	buffer.recBuff[index].repData[1]=4;
	buffer.recBuff[index].repData[2]=4;
	printf("ring buffer at index % is %d %d %d\n",index,buffer.recBuff[index].repData[0],buffer.recBuff[index].repData[1],buffer.recBuff[index].repData[2]);
	}
	printf("Return buffer %d\n",return_ring_buffer(&buffer,0));
	printf("ring buffer at index % is %d %d %d\n",index,buffer.recBuff[index].repData[0],buffer.recBuff[index].repData[1],buffer.recBuff[index].repData[2]);
	index = get_ring_buff(&buffer);
	if(index>0){

	buffer.recBuff[index].repData[0]=4;
	buffer.recBuff[index].repData[1]=4;
	buffer.recBuff[index].repData[2]=4;
	}
	printf("ring buffer at index % is %d %d %d\n",index,buffer.recBuff[index].repData[0],buffer.recBuff[index].repData[1],buffer.recBuff[index].repData[2]);
 return 0;
}
