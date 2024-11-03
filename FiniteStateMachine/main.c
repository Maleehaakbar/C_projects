#include <stdio.h>
#include "fsm.h"

int main(){
 
Queue eventqueue;
FSM vendingmachine;

queue_init(&eventqueue);
fsm_init(&vendingmachine, &eventqueue, state_idle);

// Simulate events: Customer interaction, processing, dispensing
enqueue(&eventqueue,1);
enqueue(&eventqueue,2);

// Process the events
fsm_process_event(&vendingmachine);
return 0;
}