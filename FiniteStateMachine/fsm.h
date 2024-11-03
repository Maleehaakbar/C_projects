#ifndef FSM_H
#define FSM_H


#include "queue.h"

struct FSM;

typedef void (*StateFunc) (struct FSM*);

typedef struct FSM {
    StateFunc currentstate;
    Queue *eventqueue;
}FSM;

void state_idle(FSM *fsm);
void state_processing(FSM *fsm);
void state_despensing(FSM *fsm);
void fsm_init(FSM *fsm, Queue *q , StateFunc initialstate);
void fsm_process_event(FSM *fsm);

#endif

