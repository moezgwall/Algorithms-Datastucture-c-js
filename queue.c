#include <stdio.h>
#include <stdbool.h>

#define size 5

typedef struct{
	int data[size];
	int front;
	int tail;

}Queue;

void init_queue(Queue*  q){
	q->front  = 0 ;
	q->tail = 0;
	return;
}

bool is_Empty(Queue q){
	return q.front == q.tail;
}

bool is_Full(Queue q){
	return q.tail == size;
}

void enqueue(Queue* q , int value){
	// check if the queue is full 
	if (is_Full(*q)){
		return;
	}
	q->data[q->tail++] = value;
}

int dequeue(Queue* q){
	// check if the queue is empty
	if (is_Empty(*q)){
		return 1; // exit code
	}

	return q->data[q->front++];
}

int front(Queue q){
	if (is_Empty(q)){
		return 1;
	}
	return q.data[q.front];
}

int tail(Queue q){
	if (is_Empty(q)){
		return 1;
	}
	return q.data[q.tail -1];
}


int main(){

	// try it yourself 


	return 0;
}