#include <stdbool.h>
#define QUEUESIZE 10

typedef struct{
    int arr[QUEUESIZE];
    int front;
    int rear;
}Queue;

void queue_init(Queue *q);
bool queueisEmpty(Queue *q);
bool queueisFull(Queue *q);
void enqueue(Queue *q ,int x);
int dequeue(Queue *q);
void display(Queue *q);
