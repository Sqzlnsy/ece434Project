#include "vectorBuffer.h"

Queue* createQueue(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (vector_t*)malloc(sizeof(vector_t) * size);
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
    return queue;
}

int isEmpty(Queue* queue) {
    return (queue->front == -1 && queue->rear == -1);
}

int isFull(Queue* queue) {
    return ((queue->rear + 1) % queue->size == queue->front);
}

void enqueue(Queue* queue, vector_t data) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
        queue->data[0] = data;
    } else {
        queue->rear = (queue->rear + 1) % queue->size;
        queue->data[queue->rear] = data;
    }
}

vector_t dequeue(Queue* queue) {
    vector_t empty = {0, 0, 0, 0};
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return empty;
    }
    vector_t data = queue->data[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->size;
    }
    return data;
}

vector_t front(Queue* queue) {
    vector_t empty = {0, 0, 0, 0};
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return empty;
    }
    return queue->data[queue->front];
}

vector_t rear(Queue* queue) {
    vector_t empty = {0, 0, 0};
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return empty;
    }
    return queue->data[queue->rear];
}

void printQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    int i;
    for (i = queue->front; i != queue->rear; i = (i + 1) % queue->size) {
        printf("(%lf, %lf, %lf) ", queue->data[i].x, queue->data[i].y, queue->data[i].z);
    }
    printf("(%lf, %lf, %lf)\n", queue->data[i].x, queue->data[i].y, queue->data[i].z);
}
