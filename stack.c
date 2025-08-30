#include <stdio.h>
#include <stdbool.h>
#define size 5

typedef struct {
	int data[size];
	int top;
}Stack;	

void init_stack(Stack* s){
	s->top = -1; // means stack is empty
	return;
}
bool is_Empty(Stack s){
	return (s.top == -1);
}
bool is_Full(Stack s){
	return (s.top == size - 1);
}

void push(Stack* s , int value){
		// check if the stack is already full
		if (is_Full(*s)){
			printf("stack overfolw"); return;
		}

		s->data[s->top++] = value;
		printf("element has been added to stack : %d", value);
		return;

}
int pop(Stack* s){
	// check if the stack is already empty
	if (is_Empty(*s)){
		printf("stack is empty!"); return;
	}
	int value = s->data[s->top];
	s->top--; // removing the element

	return value;

}

int top(Stack* s ){
	// check if the stack is empty
	if (is_Empty(*s)){
		printf("stack is already empty"); return 1; // exit code 
	}

	return s->data[s->top];

}

int main(){
	Stack s;  
	init_stack(&s); // top == -1
	push(&s,5);
	push(&s,6);
	push(&s,7);
	push(&s,8);
	push(&s,9);

	while(!is_Empty(s)){
		top(&s); 
		pop(&s);

	}

	

	return 0;
}