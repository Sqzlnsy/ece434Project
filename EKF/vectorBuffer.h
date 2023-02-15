#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct vectorblock {
    double x;
    double y;
    double z;
    double ts; //timestamp
} vector_t;

typedef struct Queue {
    vector_t* data;
    int front;
    int rear;
    int size;
} Queue;

Queue* createQueue(int size);
int isEmpty(Queue* queue);
int isFull(Queue* queue);
void enqueue(Queue* queue, vector_t data);
vector_t dequeue(Queue* queue);
vector_t front(Queue* queue);
vector_t rear(Queue* queue);
void printQueue(Queue* queue);

#endif /* QUEUE_H_ */
