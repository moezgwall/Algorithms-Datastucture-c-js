#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *key;
    int data;
} entity;

typedef struct
{
    entity *set_pair;
    int size_pair;
    int capacity;
} PAIR;

// todo : look up for key
// todo : hash key
// todo : improve more!

PAIR *init_Pair(int capacity)
{
    PAIR *p = malloc(sizeof(PAIR));
    p->size_pair = 0;
    p->capacity = capacity;
    p->set_pair = malloc(sizeof(entity) * p->capacity);
    return p;
}

void insert_pair(PAIR *p, char *key, int value)
{
    if (!p)
    {
        printf("[ERORR] : INVALID ACCESS MEMORY.... \n");
        exit(1);
    }
    if (p->size_pair >= p->capacity)
    {
        p->capacity *= 2;
        p->set_pair = realloc(p->set_pair, p->capacity * sizeof(entity));
    }
    p->set_pair[p->size_pair].data = value;
    p->set_pair[p->size_pair].key = strdup(key);
    p->size_pair++;

    return;
}

int find_key_index(PAIR *p, const char *key)
{
    for (int i = 0; i < p->size_pair; i++)
    {
        if (strcmp(p->set_pair[i].key, key) == 0)
            return i;
    }
    return -1;
}

void show_pair(PAIR *p)
{
    if (!p)
    {
        printf("{ERORR: NOT ALLOCA \n}");
    }
    for (int i = 0; i < p->size_pair; i++)
    {

        printf("[key : %s | value : %d ]. \n", p->set_pair[i].key, p->set_pair[i].data);
    }
}
void free_pair(PAIR *p)
{
    if (!p){
        return;
    }

    for (int i = 0; i < p->size_pair; i++)
    {
        free(p->set_pair[i].key);
    }
    free(p->set_pair);
    free(p);
}

int main()
{

    return 0;
}
