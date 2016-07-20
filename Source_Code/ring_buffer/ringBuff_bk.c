#include <stdio.h>
#include "ringBuff.h"


void initialize_ring_buffer(RINGBUFF * ringbuff)
{	
	int i,j;
	ringbuff->last=-1;
	ringbuff->first=-1;
	for (j=0;j<MAX_ELEMENTS;j++){
		ringbuff->recBuff->free = 1;
		for(i=0;i<20;i++)
			ringbuff->recBuff->repData[i]=0;
	}
	
}

int isEmpty (RINGBUFF * ringbuff)
{
	return (ringbuff->first == -1);
}

int isFull(RINGBUFF * ringbuff)
{
	return ((ringbuff->last+1)%MAX_ELEMENTS == ringbuff->first);
}

int get_ring_buff(RINGBUFF *ringbuff)
{
	int index=0;
	if(isFull(ringbuff)){
		printf("Queue is full, no buffer can be alloted \n");
		return -1;
	}
	ringbuff->last = (ringbuff->last+1)%MAX_ELEMENTS;
	index = ringbuff->last;
	ringbuff->recBuff[index].free = 0;
	if(ringbuff->first == -1)			// If first buffer is alloted
		ringbuff->first =ringbuff->last;

  return index;
}

int return_ring_buffer(RINGBUFF *ringbuff)
{
	if(isEmpty(ringbuff)){
		printf("Ring buffer completely available \n");
		return -1;
	}
    ringbuff->recBuff[ringbuff->first].free = 1;
	ringbuff->first = (ringbuff->first+1)%MAX_ELEMENTS;
	if(ringbuff->first == ringbuff->last)  //Returning back the last alloted buffer
		ringbuff->first = ringbuff->last =-1;

 return 1;	

}

int main()
{
	int index;
	RINGBUFF ringBuff;
	initialize_ring_buffer(&ringBuff);
	index = get_ring_buff(&ringBuff);
	ringBuff.recBuff[index].repData[0]=1;
	ringBuff.recBuff[index].repData[1]=1;
	ringBuff.recBuff[index].repData[2]=1;
	index = get_ring_buff(&ringBuff);
	ringBuff.recBuff[index].repData[0]=2;
	ringBuff.recBuff[index].repData[1]=2;
	ringBuff.recBuff[index].repData[2]=2;
	index = get_ring_buff(&ringBuff);
	ringBuff.recBuff[index].repData[0]=3;
	ringBuff.recBuff[index].repData[1]=3;
	ringBuff.recBuff[index].repData[2]=3;
	index = get_ring_buff(&ringBuff);
 return 0;
}
