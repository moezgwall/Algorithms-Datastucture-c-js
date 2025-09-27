#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
 struct Node{
	int data;
	Node* left;
	Node* rigth;
};

 Node* create_Node(int data){
	Node* node = (Node*) malloc(sizeof(Node));
	node->rigth = NULL;
	node->left = NULL;
	node->data = data;

	return node;
}

Node* insert_Node( Node* node , int data){
	if (node == NULL){
		node = create_Node(data);
	}else if (node->data < data){
		node->left = insert_Node(node->left, data);
	}else {
		node->rigth = insert_Node(node->rigth, data);
	}

	return node;

}

void print_Tree(Node* node){
		while ( node != NULL){
			print_Tree(node->left);
			printf("data : %d",node->data);
			print_Tree(node->rigth);
		}

}

int main(){
	// try yourself

	return 0;
}