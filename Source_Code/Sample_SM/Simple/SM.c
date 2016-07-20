#include <stdio.h>

#define MAX_EVENTS 10
#define MAX_STATES 10

enum __event {SRINGON, VRINGON, SRINGOFF, VRINGOFF, SHOOK, VHOOK, SENDCALL, VENDCALL, NULLEVENT };
typedef enum __event event;

enum __stateIdx {IDLE, SRINGING, VRINGING, BRINGING, SINCALL, VINCALL, BINCALL, VINCALLSRINGING, NULLSTATE};
typedef enum __stateIdx stateIdx;

typedef int (*func)(void);

struct __state;

typedef struct __state state;

struct __state {
	event e;
	func eh;
	stateIdx ns;
};

stateIdx cur_state, last_state;

struct __sm {
		  state *s;
};

typedef struct __sm sm;

sm states[MAX_STATES];

int sRingOnEh(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int vRingOnEh(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int sRingOffEh(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int vRingOffEh(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int sOffHookEh(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int vOffHookEh(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int sEndCallEh(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int vEndCallEh(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int sInCallMuteEh ()
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

int sInCallUnMuteEh ()
{
	printf("%s\n", __FUNCTION__);
	return 0;
}

state bIncall[] =   {   {VENDCALL, bNoActionEh, SINCALL},            //On receive vendor endcall from host
                        {SENDCALL, bNoActionEh, VINCALL},            //On receive standard endcall from host/device
                        {SMUTE, sInCallMuteEh, BINCALL},            //On receive vendor mute from host/device
                        {SUNMUTE, sInCallUnMuteEh, BINCALL},        //On receive vendor mute from host/device
                        {VMUTE, vInCallMuteEh, BINCALL},            //On receive vendor mute from host/device
                        {VUNMUTE, vInCallUnMuteEh, BINCALL},        //On receive vendor mute from host/device
						{NULLEVENT, NULL, NULLSTATE},               //last entry
                    };

state vIncall[] =   { 	{VRINGOFF, vRingOffEh, VINCALL},			//On receive vendor ringoff from host
						{VENDCALL, vEndCallEh, STATEIDLE},			//On receive vendor encall from host/device
						{SHOOK, sOffHookEh, BINCALL},				//On receive standard offhook from host
						{SRINGON, sRingOnEh, VINCALLSRINGING},      //On receive standard ringon from host
						{SRINGOFF, sRingOffEh, VINCALL},			//On receive standard ringoff from host
                        {VMUTE, vInCallMuteEh, VINCALL},            //On receive vendor mute from host/device
                        {VUNMUTE, vInCallUnMuteEh, VINCALL},        //On receive vendor unmute from host/device
						{NULLEVENT, NULL, NULLSTATE},				//last entry
					};

state sIncall[] =   { 	{SRINGOFF, sRingOffEh, SINCALL},            //On receive standard ringoff from host
						{SENDCALL, sEndCallEh, STATEIDLE},          //On receive standard endcall, from host/device 
						{VHOOK, vOffHookEh, BINCALL},               //On receive vendor offhook from host
                        {SMUTE, sInCallMuteEh, SINCALL},            //On receive standard mute from host/device
                        {SUNMUTE, sInCallUnMuteEh, SINCALL},        //On receive standard unmute from host/device
						{NULLEVENT, NULL, NULLSTATE},               //last entry
					};

state bRinging[] =  {   {VRINGOFF, vRingOffEh, SRINGING},           //On receive vendor ringoff from host
						{SRINGOFF, sRingOffEh, VRINGING},           //On receive standard ringoff from host
						{SHOOK, sOffHookEh, SINCALL},               //On receive standard offhook, accept call from host/device
						{VHOOK, vOffHookEh, VINCALL},               //On receive vendor offhook from host
						{NULLEVENT, NULL, NULLSTATE},               //last entry
					};

state sRinging[] = {    {VRINGON, vRingOnEh, BRINGING},             //On receive vendor ring from host
						{SRINGOFF, sRingOffEh, STATEIDLE},          //On receive standard ringoff from host
						{SHOOK, sOffHookEh, SINCALL},               //On receive standard offhook, accept call from host/device
						{VHOOK, vOffHookEh, VINCALL},               //On receive vendor offhook from host
						{NULLEVENT, NULL, NULLSTATE},               //last entry
					};

state vRinging[] =  {   {SRINGON, sRingOnEh, BRINGING},             //On receive standard ring from host
						{VRINGOFF, vRingOffEh, STATEIDLE},          //On receive vendor ringoff from host
						{VHOOK, vOffHookEh, VINCALL},               //On receive vendor offhook, accept call from host/device
						{SHOOK, sOffHookEh, SINCALL},               //On receive standard offhook, outgoing call from host
						{NULLEVENT, NULL, NULLSTATE},               //last entry
					};

state sIdle[] =     { 	{SRINGON, sRingOnEh, SRINGING},             //On receive standard ring from host
						{VRINGON, vRingOnEh, VRINGING},             //On receive vendor ring from host
						{SHOOK, sOffHookEh, SINCALL},               //On receive standard offhook from host, outgoing call
						{VHOOK, vOffHookEh, VINCALL},               //On receive vendor offhook from host, outgoing call
						{NULLEVENT, NULL, NULLSTATE},               //last entry
					};


void initialize_states()
{
	states[0].s = sIdle;
	states[1].s = sRinging;
	states[2].s = vRinging;
	states[3].s = bRinging;
	states[4].s = sIncall;
	states[5].s = vIncall;
	states[6].s = bIncall;
	states[7].s = NULL;

	cur_state = IDLE;
	last_state = NULLSTATE;
}

void print_state(stateIdx s)
{
	switch(s)
	{
		case IDLE: printf("IDLE"); break;
		case SRINGING: printf("SRINGING"); break;
		case VRINGING: printf("VRINGING"); break;
		case BRINGING: printf("BRINGING"); break;
		case SINCALL: printf("SINCALL"); break;
		case VINCALL: printf("VINCALL"); break;
		case BINCALL: printf("BINCALL"); break;
		case VINCALLSRINGING: printf("VINCALLSRINGING"); break;
		default: printf("In state not defined\n"); break;
	}
}

int process(event e)
{
	int i, ret = 0;
	func execute;
	state *s;

	if(states[cur_state].s == NULL)
			  return -1;

	s = states[cur_state].s;

	for(i=0; i<MAX_EVENTS; i++)
	{
		if(s[i].e != NULLEVENT)
		{
			if(s[i].e == e)
			{
				execute = s[i].eh;

				print_state(cur_state); printf(" -> "); print_state(s[i].ns); printf("\n");

				if(last_state != s[i].ns)
				{
					printf("Executing State Entry handler\n");
				}

				/*execute eh*/
				ret = execute();

				last_state = cur_state;

				/*update cur_state*/
				cur_state = s[i].ns;

				break;
			}	
		}
		else
		{
			printf("Event not registered\n");
			break;	  
		}
	}

}

main()
{
int ch;


initialize_states();

printf("Size: %d %d %d %d\n", sizeof(sIdle), sizeof(sIdle[0].e), sizeof(sIdle[0].eh), sizeof(sIdle[0].ns));

while(1)
{
	printf("Enter 0: SRINGON\n");
	printf("Enter 1: VRINGON\n");
	printf("Enter 2: SRINGOFF\n");
	printf("Enter 3: VRINGOFF\n");
	printf("Enter 4: SHOOK\n");
	printf("Enter 5: VHOOK\n");
	printf("Enter 6: SENDCALL\n");
	printf("Enter 7: VENDCALL\n");
	printf("Enter 9: Exit\n");
	printf("Enter Choice: ");
	scanf("%d", &ch);

	switch(ch)
	{
		case SRINGON: process(SRINGON); break;
		case VRINGON: process(VRINGON); break;
		case SRINGOFF: process(SRINGOFF); break;
		case VRINGOFF: process(VRINGOFF); break;
		case SHOOK: process(SHOOK); break;
		case VHOOK: process(VHOOK); break;
		case SENDCALL: process(SENDCALL); break;
		case VENDCALL: process(VENDCALL); break;
		case 9: goto EXIT;
		default: printf("Enter proper choice\n"); goto EXIT; 
	}
}
EXIT:
printf("Goodbye World\n");
}

