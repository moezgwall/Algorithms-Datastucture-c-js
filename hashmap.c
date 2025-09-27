#include <stdlib.h>
#include <stdio.h>
#define initial_capacity 5

typedef struct
{
    char *key;
    void *data;
} entity;

typedef struct
{
    entity *tab;
    int size;
    int capacity;
} HashMap;

HashMap *init_hashmap()
{
    HashMap *hm = (HashMap *)malloc(sizeof(HashMap));
    hm->tab = (entity *)malloc(sizeof(entity) * initial_capacity);
    hm->size = 0; // keep track of the size in each add()
    hm->capacity = initial_capacity;

    return hm;
}

void resize(HashMap *hm)
{
    hm->capacity = hm->capacity * 2;
    hm->tab = (entity *)realloc(hm->tab, hm->capacity * sizeof(entity));
    return;
}

void add(HashMap *hm, char *key, int value)
{
    if (!hm)
    {
        printf("error : hm doesn't exist \n");
    }
    if (hm->size >= hm->capacity)
    {
        resize(hm);
    }
    hm->tab[hm->size].key = strdup(key);
    hm->tab[hm->size].data = malloc(sizeof(int));
    *((int *)hm->tab[hm->size].data) = value;
    hm->size++;

    return;
}

void print(HashMap *hm)
{
    for (int i = 0; i < hm->size; ++i)
    {
        printf("[key[%s] , value[%d]] \n ", hm->tab[i].key, *((int *)hm->tab[i].data));
    }
    return;
}

int main(int argc, char **argv)
{
    HashMap *hm = init_hashmap();
    add(hm, "weapons", 15);
    add(hm, "rocket", 10);
    add(hm, "dildo", 5);
    print(hm);

    return 0;
}
