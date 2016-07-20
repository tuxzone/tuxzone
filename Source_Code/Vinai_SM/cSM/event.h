#ifndef __EVENT_H_
#define __EVENT_H_

//FORWARD DECLARATION
struct event;

typedef struct event event;

struct event {
	int event_num;
};

static int base_token = 100;

#define BASE_TOKEN base_token
#define GET_NEXT_EVENT_TOKEN (++BASE_TOKEN)

#define DECLARE_EVENT(_EVENT_) extern event ON##_EVENT_

//#define SETUP_EVENT(_EVENT_) event ON##_EVENT_ = {ON##_EVENT_.event_num = GET_NEXT_EVENT_TOKEN}
//#define SETUP_EVENT(_EVENT_) _EVENT_->event_num = GET_NEXT_EVENT_TOKEN
#define SETUP_EVENT(_EVENT_) _EVENT_.event_num = GET_NEXT_EVENT_TOKEN
#define DEFINE_EVENT(_EVENT_) event _EVENT_

#define EVENT_ID(_EVENT_) _EVENT_.event_num

#define EVENT_PTR(_EVENT_) &_EVENT_

DECLARE_EVENT(Init);
DECLARE_EVENT(Timeout);
DECLARE_EVENT(Success);
DECLARE_EVENT(Failure);
DECLARE_EVENT(Wait);

DECLARE_EVENT(Event1);
DECLARE_EVENT(Event2);
DECLARE_EVENT(Event3);
DECLARE_EVENT(Event4);
#endif
