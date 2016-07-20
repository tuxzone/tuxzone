#include<stdio.h>
#include "sm.h"

state *cur_state, *last_state;
APP_CONTEXT ctxt;
sm s_machine;


void statemachine_init(transition_table *tt, int *ptt_size)
{
	/*set cur_state to initial state*/
	s_machine.ptt = tt;
	s_machine.ttSize = *ptt_size;

	cur_state = (state *)tt[0].src_state;
	last_state = NULL;

	process_event(&ONInit);
}

state* lookup_transition(state *s, int e)
{
	int i = 0;
	state *next_state = NULL;

#ifdef DEBUG
	printf("state %d event %d size %d\n", s->sid, e, s_machine.ttSize);
#endif

	for(i=0;i<s_machine.ttSize;i++)
	{
		if(((state *)s_machine.ptt[i].src_state == s) && (((event *)s_machine.ptt[i].event_id)->event_num == e))
		{
			next_state = (state *)s_machine.ptt[i].dst_state;
#ifdef DEBUG
			printf("LUT Found next state\n");
#endif
			break;
		}
	}

	return next_state;
}

void process_event(event *e)
{
	int (*fptr)(APP_CONTEXT *ctxt) = NULL;
	eventExecute *cur_event;
	int rc;
	state *next_state = NULL;

	if(cur_state == NULL)
	{
		printf("State machine is not initialized or it is ended\n");
		return;
	}

	/*
	Get structure pointer from State ID
	Get the current state
	Get the Event 
	Get the Event handler
	Event handler will return event
	*/
		
	/*Set state variable in context*/
	ctxt.s = cur_state;
	rc = 0;

	/*Check are we entering in to this state for first time, then execute state entry handler*/
	if(cur_state->sid != ((last_state!=NULL)?last_state->sid:0))
	{
		/*Set event variable in context*/
		cur_event = &cur_state->fun_execute[0];
		ctxt.e = cur_event->event_id;

#ifdef DEBUG
		printf("State Entry: State %d event %d\n", cur_state->sid, cur_event->event_id->event_num);
#endif

		/*Get state InitHandler and Exceute it */
		fptr = GET_INIT_FN_FROM_STATE(cur_state);
		if(fptr != NULL)
		{			
			rc = fptr(&ctxt);
			printf("1 rc %d\n", rc);
		}
#ifdef DEBUG
		else
		{
			printf("A: Handler is not registered for this event\n");
		}
#endif
	}
	else
	{
		ctxt.e = e;
#ifdef DEBUG
		printf("Else Received Event state %d event %d\n", cur_state->sid, e->event_num);
#endif
		fptr = GET_HANDLER_FROM_STATE_FOR_GIVEN_EVENT(cur_state, e);
		if(fptr != NULL)
		{			
			rc = fptr(&ctxt);
			printf("2 rc %d\n", rc);
		}
		else
		{
#ifdef DEBUG
			printf("B Handler is not registered for this event\n");
#endif
			rc = e->event_num;
		}

	}
	

	if(rc == EVENT_ID(ONWait))
	{
		//Do not change state be in the current state
#ifdef DEBUG
		printf("no Change in cur_state: Waiting in the current state ...\n");
#endif
		last_state = cur_state;
	}
	else // if (rc != 0) 
	{
		//Do LUT and forward to next
		next_state = lookup_transition(ctxt.s, rc);
		if(next_state != NULL)
		{
			;
#ifdef DEBUG
			printf("current state %d\n", cur_state->sid);
#endif
		}
		else
		{
#ifdef DEBUG
			printf("next_state is null\n");
#endif
			cur_state = NULL;
			goto Exit_Process;
		}

		
		/*if next_state is not equal to cur_state, then update cur_state and last_state and it should execute next_state initHandler*/
		if(next_state != cur_state)
		{
			last_state = cur_state;
			cur_state = next_state;

			/*Execute InitHandler*/
			ctxt.s = cur_state;
			cur_event = &cur_state->fun_execute[0];
			ctxt.e = cur_event->event_id;

			/*Get state InitHandler and Exceute it */
			fptr = GET_INIT_FN_FROM_STATE(cur_state);
			if(fptr != NULL)
			{			
				rc = fptr(&ctxt);
				printf("3 rc %d\n", rc);
				last_state = cur_state;
			}
#ifdef DEBUG
			else
			{
				printf("C Handler is not registered for this event\n");
			}
#endif
		}
		/*if next_state is cur_state, then there is no chnage in state and do not execute Inithandler again*/
		else
		{
			last_state = cur_state;
		}

	}
	//else
		//printf("State Handler returned improper event\n");

Exit_Process:		
	;
#ifdef DEBUG
	if(cur_state == NULL)
		printf("cur_state is NULL\n");
#endif

}
