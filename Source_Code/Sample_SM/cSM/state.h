#ifndef __STATE_H_
#define __STATE_H_

#include "event.h"

#define MAX_EVENTS_PER_STATE 20
//FORWARD DECLARATIONS
struct state;
struct eventExecute;
struct APP_CONTEXT;

typedef struct state state;
typedef struct eventExecute eventExecute;
typedef struct APP_CONTEXT APP_CONTEXT;
typedef int(*FUNC_PTR)(APP_CONTEXT *ctxt);

void add_event(state *s, event *e);
void list_events_in_state(state *s);
void register_event_handler(state *s, event *e, FUNC_PTR);
FUNC_PTR get_handler(state *s, event *e);

struct eventExecute {
	event *event_id;
	int (*execute)(APP_CONTEXT *ctxt);
};

struct state
{
	int sid;
	int no_events;
	eventExecute fun_execute[MAX_EVENTS_PER_STATE];
};

static int base_state_id = 200;

#define BASE_STATE_ID base_state_id
#define GET_NEXT_STATE_TOKEN (++BASE_STATE_ID)

//ADD EVENT TO STATE
//#define ADD_EVENT_TO_STATE(_STATE_, _EVENT_) add_event(&S##_STATE_, &ON##_EVENT_);
#define ADD_EVENT_TO_STATE(_STATE_, _EVENT_) add_event(_STATE_, _EVENT_);

#define DEFINE_STATE(_STATE_) state _STATE_; //= {S##_STATE_.sid = GET_NEXT_STATE_TOKEN,S##_STATE_.no_events = 0}

#define SETUP_STATE(_STATE_) _STATE_.sid = GET_NEXT_STATE_TOKEN; _STATE_.no_events = 0; memset((void *)_STATE_.fun_execute, 0, sizeof(eventExecute))
//#define SETUP_STATE(_STATE_) state _STATE_ = {_STATE_.sid = GET_NEXT_STATE_TOKEN,_STATE_.no_events = 0}

#define DECLARE_EVENT_HANDLER(_STATE_, _EVENT_) int S##_STATE_ON##_EVENT_(APP_CONTEXT *)
	
#define ADD_BASE_EVENTS_TO_STATE(_STATE_, _INIT_, _TIMEOUT_)	ADD_EVENT_TO_STATE(_STATE_, _INIT_); ADD_EVENT_TO_STATE(_STATE_, _TIMEOUT_)
//#define ADD_BASE_EVENTS_TO_STATE(_STATE_)	ADD_EVENT_TO_STATE(_STATE_, Init); ADD_EVENT_TO_STATE(_STATE_, Timeout)
	
//DECLARE_EVENT_HANDLER(_STATE_, Init); DECLARE_EVENT_HANDLER(_STATE_, Timeout)

#define STATE_ID(_STATE_) _STATE_.sid

#define STATE_PTR(_STATE_) &_STATE_

#define LIST_EVENTS_IN_STATE(_STATE_) list_events_in_state(_STATE_);

//DEFINE EVENT
#define REGISTER_EVENT_HANDLER(_STATE_, _EVENT_, _FP_) register_event_handler(_STATE_, _EVENT_, _FP_);

#define GET_EXE_FN(_STATE_) S##_STATE_.fun_execute[0].execute

#define GET_INIT_FN_FROM_STATE(_STATE_) _STATE_->fun_execute[0].execute

#define GET_STATE(_STATE_) &S##_STATE_

#define GET_EVENT(_EVENT_) &ON##_EVENT_

#define EXIT_STATE 0

#define GET_HANDLER_FROM_STATE_FOR_GIVEN_EVENT(_STATE_, _EVENT_) get_handler(_STATE_, _EVENT_)

#endif
