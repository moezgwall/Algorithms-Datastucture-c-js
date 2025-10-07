#include <stdio.h>
#include <stdlib.h>


// i learned more about BST

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}Node;

Node* init(int data){
    Node* n = malloc(sizeof(Node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node* insert(Node* root,int data){
        if (!root) {
            return init(data);
        }

        if (data > root->data){
            root->right = insert(root->right,data);
        }else{
            root->left = insert(root->left,data);
        }

        return root;
}

void print(Node* root){
        if (root == NULL) return;
        print(root->left);
        printf("[%d]",root->data);
        print(root->right);

}

Node* findMinNode(Node* root){
        while (root && root->left != NULL){
            root = root->left;
        }

        return root;

}
Node* findMaxNode(Node* root){
        while(root && root->right != NULL){
            root = root->right;
        }
        return root;
}

Node* search(Node* root, int data){
        if ( root == NULL || root->data == data){
            return root;
        }
        if (data < root->data){
           return search(root->left,data);
        }else{
            return search(root->right,data);
        }

        return root;
}
// order successor
Node* deleteByOrderSuccessor(Node* root , int data){
        if (root == NULL) return NULL;

        if (data < root->data){
            root->left = deleteByOrderSuccessor(root->left,data);
        }else if (data > root->data){
            root->right = deleteByOrderSuccessor(root->right,data);
        }else{
            if (root->left == NULL){
                Node* temp = root->right;
                free(root);
                return temp;
            }else if (root->right == NULL){
                Node* temp = root->left;
                free(root);
                return temp;
            }else{
                Node* temp = findMinNode(root->right);
                root->data = temp->data;
                root->right = deleteByOrderSuccessor(root->right,temp->data);


            }

        }

        return root;
}

// order predecessor
Node* deleteByOrderPredecessor(Node* root , int data){
        if (root == NULL) return NULL;

        if (data < root->data){
            root->left = deleteByOrderPredecessor(root->left,data);
        }else if (data > root->data){
            root->right = deleteByOrderPredecessor(root->right,data);
        }else{
            if (root->left == NULL){
                Node* temp = root->right;
                free(root);
                return temp;
            }else if (root->right == NULL){
                Node* temp = root->left;
                free(root);
                return temp;
            }else{
                Node* temp = findMaxNode(root->left);
                root->data = temp->data;
                root->left = deleteByOrderPredecessor(root->left,temp->data);


            }

        }

        return root;
}

int main(){
    Node* root = init(5); 
    insert(root,6);
    insert(root,17);
    insert(root,0);
    insert(root,155);
    Node* min = findMinNode(root);
    Node* max = findMaxNode(root);
    printf("%d \n",min->data);
    printf("%d \n", max->data);

    // you can try another examples 


    return 0;
}


