#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

void queue_init(Queue *q){ 
q->front=-1;
q->rear=-1;
}

bool queueisEmpty(Queue *q){
  return q->front==-1;
}

bool queueisFull(Queue *q){
  return (q->rear + 1) % QUEUESIZE == q->front;
}

void enqueue(Queue *q ,int x){
  if (queueisFull(q)){
    printf("queue overflow");
    return;
  }

  if (queueisEmpty(q)){
     q->front=0;
  }

  q->rear= (q->rear + 1) % QUEUESIZE;
  q->arr[q->rear]= x;
  printf("element inserted %d\n", q->arr[q->rear]);
}

int dequeue(Queue *q){
  int data;

  if (queueisEmpty(q)){
    printf("queue underflow");
    return -1;
  }

  data = q->arr[q->front];

  if (queueisFull(q)){
    q->front=-1;
    q->rear=-1;
  }
  else {
    q->front= (q->front+1) % QUEUESIZE;
  }
  return data;
}

void display(Queue *q){
   int i; 

  if(queueisEmpty(q)){
    return;
  }
   
  printf ("queue elements are ");
  for (i=q->front; i<=q->rear; i++){
    printf("%d\n", q->arr[i]);
  }   

}

/*int main(){

Queue queue;

enqueue(&queue, 10);
enqueue(&queue, 11);
enqueue(&queue, 9);
display(&queue);
printf("%d\n",dequeue(&queue));
display(&queue);

}*/