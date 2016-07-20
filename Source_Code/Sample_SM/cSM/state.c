#include<stdio.h>
#include "state.h"
#include "event.h"

void add_event(state *s, event *e)
{
	//int i;
	
	if(s->no_events <= MAX_EVENTS_PER_STATE)
	{
			  s->fun_execute[s->no_events].event_id = (event *)e;
			  s->no_events += 1;
#ifdef DEBUG
			  printf("Added event %d to state %d total events %d\n", e->event_num, s->sid, s->no_events);
#endif
	}
	else
		printf("Maximum number of events crossed for this state\n");

	return;
}

void list_events_in_state(state *s)
{
	int i = 0;

	printf("%s %d %d\n", __FUNCTION__, s->no_events, s->sid);
	
	for (i=0;i<s->no_events;i++)
		printf("Events %d\n", s->fun_execute[i].event_id->event_num);

	return;
}

void register_event_handler(state *s, event *e, FUNC_PTR fp)
{
	int i = 0;

	for (i=0;i<s->no_events;i++)
	{
		if(s->fun_execute[i].event_id->event_num == e->event_num)
		{
			s->fun_execute[i].execute = fp;
#ifdef DEBUG
			printf("Registered Event Handler for state %d event %d\n", s->sid, e->event_num);
#endif
			break;
		}
	}
}

FUNC_PTR get_handler(state *s, event *e)
{
	int i = 0;

#ifdef DEBUG
	printf("state %d event %d no of event in state %d\n", s->sid, e->event_num, s->no_events);
#endif

	for(i=0;i<s->no_events;i++)
	{
		if(s->fun_execute[i].event_id->event_num == e->event_num)
		{			
			if(s->fun_execute[i].execute != NULL)
			{
#ifdef DEBUG
				printf("Found Registered Handler\n");
#endif
				return s->fun_execute[i].execute;
			}
			else
				break;
		}
	}
		
	return NULL;
}