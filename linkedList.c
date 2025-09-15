#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *create_Node(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (node)
    {
        node->data = data;
        node->next = NULL;
        return node;
    }

    return NULL;
}

void insert_Node(struct Node **root, int data)
{
    struct Node *n = create_Node(data); // node to insert

    if (!*root)
    {
        *root = n;
        return;
    }

    struct Node *temp = *root;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = n;
}

void print_Node(struct Node *root)
{

    if (!root)
    {
        printf("error");
    }

    while (root->next != NULL)
    {
        printf("data :[%d] \n", root->data);
        root = root->next;
    }
}

void free_LL(struct Node **root)
{
    struct Node *temp;
    struct Node *root_ = *root;
    while (root_ != NULL)
    {
        temp = root_;
        root_ = root_->next;
        free(temp);
    }
    *root = NULL;
}

int main()
{
    printf("naive LL implementation ... \n");
    return 0;
}