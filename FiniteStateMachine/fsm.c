#include <stdio.h>
#include "fsm.h"

void state_idle(FSM *fsm);
void state_processing(FSM *fsm);
void state_dispensing(FSM *fsm);

void state_idle(FSM *fsm){
    printf("Machine idle, waiting for user input...\n" );
    int event = dequeue(fsm->eventqueue);
    if (event==1){
    printf("Customer press button , transition to processing\n");
    fsm->currentstate = state_processing;        
    }
}

void state_processing(FSM *fsm){
    printf("Processing order...\n");
    int event =dequeue(fsm->eventqueue);
    if (event==2){
    printf("Order complete. Transitioning to DISPENSING.\n");
    fsm->currentstate = state_dispensing;
    }
}

void state_dispensing(FSM *fsm){
   printf("Dispensing product...\n");
    fsm->currentstate=state_idle;
}

void fsm_init(FSM *fsm, Queue *q , StateFunc initialstate){
    fsm->currentstate = initialstate;
    fsm-> eventqueue = q;
}

void fsm_process_event(FSM *fsm){
    while (!queueisEmpty(fsm->eventqueue)){
        fsm->currentstate(fsm);
    }
}
