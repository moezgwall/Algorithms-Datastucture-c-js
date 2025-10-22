#include <stdlib.h>
#include <stdio.h>

// invert a given binary tree
// in a recursive way 
// author : gWall 


typedef struct Node Node;

struct Node{
    int data;
    Node* left;
    Node* right;
};
#define MAX_ITEMS 20
typedef struct{
    Node* items[MAX_ITEMS];
    int front;
    int rear;
}Queue;

// create a simple node;

Node* createNode(int data){
    Node* node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->data = data;

    return node;
}
#include <stdbool.h>
bool isEmpty(Queue*  q){
    return ( q->front == q->rear);
}
void initQueue(Queue* q){
    q->front = 0;
    q->rear = 0;
}

void enQueue(Queue* q,Node* n){
    if (!n) return;

    if (q->rear < MAX_ITEMS){
        q->items[q->rear++] = n;
    }
    return;
}

Node* deQueue(Queue* q){
    if(!isEmpty(q)){
        return q->items[q->front++];
    }

    return NULL;

}
// left become right
// right become left
void swap2Nodes(Node** a, Node** b){
    Node* temp = *a;
    *a = *b;
    *b = temp;
}
// recursive way
void invert(Node* root){
    if (root == NULL){
        return;
    }
    invert(root->left);
    invert(root->right);

    swap2Nodes(&(root->left),&(root->right));
}


void printTree(Node* root){
    if (root == NULL){
        printf("[*]");
        return;
    }

    Queue q;
    initQueue(&q);
    enQueue(&q,root);

    while(!isEmpty(&q)){

        Node* current = deQueue(&q);

        if( current == NULL){
            printf("*");
            continue; // skip next iterations
        }else{

            printf("[%d]",current->data);
            enQueue(&q,current->left);
            enQueue(&q,current->right);

        }

    }


}


int main(){

    Node* root = createNode(69);
    root->left = createNode(9);
    root->right = createNode(6);
    root->left->left = createNode(17);
    root->left->right = createNode(33);
    root->right->left = createNode(0);
  

    invert(root);

    printTree(root);
    // output : [69][6][9][0][33][17]

    return 0;
}



