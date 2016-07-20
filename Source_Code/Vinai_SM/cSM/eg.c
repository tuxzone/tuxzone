#include<stdio.h>
#include<string.h>
#include<stddef.h>
#include "event.h"
#include "state.h"
#include "sm.h"


int s0_onInit(APP_CONTEXT *ctxt);
int s0_onTimeout(APP_CONTEXT *ctxt);

int s1_onInit(APP_CONTEXT *ctxt);
int s1_onTimeout(APP_CONTEXT *ctxt);

int s2_onInit(APP_CONTEXT *ctxt);
int s2_onTimeout(APP_CONTEXT *ctxt);

int sEnd_onInit(APP_CONTEXT *ctxt);
int sEnd_onTimeout(APP_CONTEXT *ctxt);

int s0_on_event1(APP_CONTEXT *ctxt);
int s0_on_event2(APP_CONTEXT *ctxt);
int s0_on_event3(APP_CONTEXT *ctxt);
int s1_on_event1(APP_CONTEXT *ctxt);
int s1_on_event2(APP_CONTEXT *ctxt);
int s2_on_event1(APP_CONTEXT *ctxt);
int s2_on_event2(APP_CONTEXT *ctxt);
int s2_on_event3(APP_CONTEXT *ctxt);

/*Define States Globally*/
DEFINE_STATE(SS0);
DEFINE_STATE(SS1);
DEFINE_STATE(SS2);
DEFINE_STATE(SEnd);

/*Defining Events Globally*/
/*Base Events by framework*/
DEFINE_EVENT(ONInit);
DEFINE_EVENT(ONTimeout);
DEFINE_EVENT(ONSuccess);
DEFINE_EVENT(ONFailure);
DEFINE_EVENT(ONWait);

/*Define App specific events Globally*/
DEFINE_EVENT(ONEvent1);	
DEFINE_EVENT(ONEvent2);
DEFINE_EVENT(ONEvent3);
DEFINE_EVENT(ONEvent4);
DEFINE_EVENT(ONEvent5);

/*Define Transition table*/
transition_table tt[] = {
	{STATE_PTR(SS0), EVENT_PTR(ONEvent1), STATE_PTR(SS1)},
	{STATE_PTR(SS0), EVENT_PTR(ONEvent2), STATE_PTR(SS2)},
	{STATE_PTR(SS0), EVENT_PTR(ONEvent3), STATE_PTR(SEnd)},
	{STATE_PTR(SS0), EVENT_PTR(ONEvent4), STATE_PTR(SS0)},
	{STATE_PTR(SS1), EVENT_PTR(ONEvent1), STATE_PTR(SS0)},
	{STATE_PTR(SS1), EVENT_PTR(ONEvent2), STATE_PTR(SS2)},
	{STATE_PTR(SS2), EVENT_PTR(ONEvent1), STATE_PTR(SS0)},
	{STATE_PTR(SS2), EVENT_PTR(ONEvent2), STATE_PTR(SS1)},
	{STATE_PTR(SS2), EVENT_PTR(ONEvent3), STATE_PTR(SEnd)},
	{STATE_PTR(SEnd), EVENT_PTR(ONEvent1), NULL},
};

void initialize_states()
{
	SETUP_STATE(SS0);
	SETUP_STATE(SS1);
	SETUP_STATE(SS2);
	SETUP_STATE(SEnd);
}

void initialize_events()
{
	SETUP_EVENT(ONInit);
	SETUP_EVENT(ONTimeout);
	SETUP_EVENT(ONSuccess);
	SETUP_EVENT(ONFailure);
	SETUP_EVENT(ONWait);

	/*Define App specific events here*/
	SETUP_EVENT(ONEvent1);	
	SETUP_EVENT(ONEvent2);
	SETUP_EVENT(ONEvent3);
	SETUP_EVENT(ONEvent4);
	SETUP_EVENT(ONEvent5);
}

//Main thread using state machine
main()
{
	int ch;
	int tt_size;

	initialize_events();

	initialize_states();

#ifdef DEBUG
	printf("Init %d Timeout %d success %d Failure %d wait %d Event1 %d Event2 %d Event3 %d Event4 %d Event5 %d\n", 
			EVENT_ID(ONInit),EVENT_ID(ONTimeout), EVENT_ID(ONSuccess), EVENT_ID(ONFailure), EVENT_ID(ONWait), 
			EVENT_ID(ONEvent1), EVENT_ID(ONEvent2), EVENT_ID(ONEvent3), EVENT_ID(ONEvent4), EVENT_ID(ONEvent5));
	printf("S0 %d S1 %d S2 %d\n", STATE_ID(SS0), STATE_ID(SS1), STATE_ID(SS2));
#endif

	/*Add Base events to Defined states*/
	ADD_BASE_EVENTS_TO_STATE(&SS0, &ONInit, &ONTimeout);
	ADD_BASE_EVENTS_TO_STATE(&SS1, &ONInit, &ONTimeout);
	ADD_BASE_EVENTS_TO_STATE(&SS2, &ONInit, &ONTimeout);
	ADD_BASE_EVENTS_TO_STATE(&SEnd, &ONInit, &ONTimeout);

	/*Register Base event handlers to states*/
	REGISTER_EVENT_HANDLER(&SS0, &ONInit, s0_onInit);
	REGISTER_EVENT_HANDLER(&SS0, &ONTimeout, s0_onTimeout);

	REGISTER_EVENT_HANDLER(&SS1, &ONInit, s1_onInit);
	REGISTER_EVENT_HANDLER(&SS1, &ONTimeout, s1_onTimeout);

	REGISTER_EVENT_HANDLER(&SS2, &ONInit, s2_onInit);
	REGISTER_EVENT_HANDLER(&SS2, &ONTimeout, s2_onTimeout);

	REGISTER_EVENT_HANDLER(&SEnd, &ONInit, sEnd_onInit);
	REGISTER_EVENT_HANDLER(&SEnd, &ONTimeout, sEnd_onTimeout);

	/*Add additional events to state*/
	ADD_EVENT_TO_STATE(&SS0, &ONEvent1);
	ADD_EVENT_TO_STATE(&SS0, &ONEvent2);
	ADD_EVENT_TO_STATE(&SS0, &ONEvent3);
	ADD_EVENT_TO_STATE(&SS0, &ONEvent4);

	ADD_EVENT_TO_STATE(&SS1, &ONEvent1);
	ADD_EVENT_TO_STATE(&SS1, &ONEvent2);

	ADD_EVENT_TO_STATE(&SS2, &ONEvent1);
	ADD_EVENT_TO_STATE(&SS2, &ONEvent2);
	ADD_EVENT_TO_STATE(&SS2, &ONEvent3);

#ifdef DEBUG
	LIST_EVENTS_IN_STATE(&SS0);
	LIST_EVENTS_IN_STATE(&SS1);
	LIST_EVENTS_IN_STATE(&SS2);
#endif

	REGISTER_EVENT_HANDLER(&SS0, &ONEvent1, s0_on_event1);
	//REGISTER_EVENT_HANDLER(&SS0, &ONEvent2, s0_on_event2);
	//REGISTER_EVENT_HANDLER(&SS0, &ONEvent3, s0_on_event3);
	REGISTER_EVENT_HANDLER(&SS1, &ONEvent1, s1_on_event1);
	REGISTER_EVENT_HANDLER(&SS1, &ONEvent2, s1_on_event2);
	REGISTER_EVENT_HANDLER(&SS2, &ONEvent1, s2_on_event1);
	REGISTER_EVENT_HANDLER(&SS2, &ONEvent2, s2_on_event2);
	REGISTER_EVENT_HANDLER(&SS2, &ONEvent3, s2_on_event3);

	tt_size = sizeof(tt);
	statemachine_init(tt, &tt_size);

	while(1)
	{
		printf("1 For Event1\n");
		printf("2 For Event2\n");
		printf("3 For Event3\n");
		printf("4 For Event4\n");
		printf("5 For Event5\n");
		printf("10 For exit\n");
		printf("Enter your choice: ");
		scanf("%d", &ch);

		switch(ch)
		{
			case 1: process_event(&ONEvent1); break;
			case 2: process_event(&ONEvent2); break;
			case 3: process_event(&ONEvent3); break;
			case 4: process_event(&ONEvent4); break;
			case 5: process_event(&ONEvent5); break;
			case 10: goto EXIT;
			default: printf("Unknown Event\n"); break;
		}
	}
EXIT:
	printf("Exit from Main\n");
}

// event handlers definitions
 int s0_onInit(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s Entry Handler\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONWait);
 }

int s0_onTimeout(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return e.event_num;
}

int s1_onInit(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s Entry Handler\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONWait);
}

int s1_onTimeout(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return e.event_num;
}

int s2_onInit(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s Entry Handler\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONWait);
}

int s2_onTimeout(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return e.event_num;
}

int sEnd_onInit(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s Entry Handler\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONEvent1);
}

int sEnd_onTimeout(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONWait);
}

 int s0_on_event1(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONEvent1);
}

 int s0_on_event2(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONEvent2);
}

int s0_on_event3(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONEvent3);
}

int s1_on_event1(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONEvent1);
}

int s1_on_event2(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONEvent2);
}

int s2_on_event1(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONEvent1);
}

int s2_on_event2(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONEvent2);
}

int s2_on_event3(APP_CONTEXT *ctxt)
{
	event e;
	printf("%s\n", __FUNCTION__);
	e.event_num = ctxt->e->event_num;

	return EVENT_ID(ONEvent3);
}
