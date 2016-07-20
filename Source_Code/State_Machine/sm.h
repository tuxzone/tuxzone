#ifndef _SM_H_
#define _SM_H_

#include <stdio.h>

static int BASE_STATE_ID = 100;
#define GET_NEXT_STATE (++BASE_STATE_ID)
void S0_init();
void S1_init();
void S2_init();
void S3_init();
void S0_exit();
void S1_exit();
void S2_exit();
void S3_exit();
typedef void (*init_handler_t) (void);
init_handler_t init_handler[] = {S0_init, S1_init, S2_init, S3_init};

typedef void (*exit_handler_t) (void);
exit_handler_t exit_handler[] = {S0_exit, S1_exit, S2_exit, S3_exit};

typedef enum event{
	Event1=0,
	Event2,
	Event3,
	Event4,
	Event5,
}EVENT;


typedef struct transition_table{
	 EVENT event;
	 int (*event_handler) (void *);
	 struct state *next_state;
}transTable;



typedef struct state {
	int sid;
	void (*initHandler) (void);
	int event_count;
//	EVENT event_no;
	transTable *tt;
	struct state *next_state;
	void (*ExitHandler) (void);
}STATE;	

STATE S0,S1,S2,S3;

STATE SM_states[4];;

#define SETUP_STATE(_STATE_,INDEX) _STATE_.sid=GET_NEXT_STATE;_STATE_.initHandler=init_handler[INDEX]; _STATE_.event_count=0;_STATE_.next_state=0;_STATE_.ExitHandler=exit_handler[INDEX]




#endif
