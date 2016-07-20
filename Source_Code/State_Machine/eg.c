#include "sm.h"

void S0_init()
{
	printf("Inside %s\n",__FUNCTION__);
}

void S0_exit()
{
	printf("Inside %s\n",__FUNCTION__);
}

void S1_init()
{
	printf("Inside %s\n",__FUNCTION__);
}

void S1_exit()
{
	printf("Inside %s\n",__FUNCTION__);
}

void S2_init()
{
	printf("Inside %s\n",__FUNCTION__);
}

void S2_exit()
{
	printf("Inside %s\n",__FUNCTION__);
}

void S3_init()
{
	printf("Inside %s\n",__FUNCTION__);
}

void S3_exit()
{
	printf("Inside %s\n",__FUNCTION__);
}

void  initialize_states()
{
	SETUP_STATE(SM_states[0],0);
	//SETUP_STATE(SM_states[1],1);
	SETUP_STATE(SM_states[2],2);
//	SETUP_STATE(SM_states[3],3);
}

int main()
{
	initialize_states();
	SM_states[0].initHandler();
	SM_states[2].ExitHandler();
}



