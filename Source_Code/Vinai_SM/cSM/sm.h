#ifndef __SM_H_
#define __SM_H_

#include"state.h"
#include"event.h"

//DATA DECLARATIONS
struct transition_table
{
	void* src_state;
	void* event_id;
	void* dst_state;
};
typedef struct transition_table transition_table;

#define DEBUG 1

struct APP_CONTEXT
{
	int instance;
	state *s;
	event *e;
};

struct sm
{
	transition_table *ptt;
	int ttSize;
};

typedef struct sm sm;

//EXTERNS
extern state *cur_state, *last_state;
extern sm s_machine;

//FUNCTION DECLARATIONS
state* lookup_transition(state *s, int e);
void process_event(event *e);
void statemachine_init(transition_table *tt, int *ptt_size);


#endif
