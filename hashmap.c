#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
        return;
    }
    // if the key exist we overwrite data[key]
    for (int i = 0; i < hm->size;i++){
        if (strcmp(hm->tab[i].key, key)==0){
           *((int*)hm->tab[i].data) = value;
            return;
        }
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

// get an element from the hashmap

int get(HashMap* hm, char* key){
    for (int i=0; i < hm->size;i++){
        if (strcmp(hm->tab[i].key, key) ==0){
            return *((int*)hm->tab[i].data);
        }

    }
    // if -1 already a value in the hashmap 
    // ill ignore this case 
    // and maybe return a pointer to int so -1 will be just NULL , and get the value by passing 
    // it to the function args
    return -1;
}

// the hash function was missing 
// not mine but i found it attractive
int hash(char* key , int capacity){
    int hash = 0;
    for (int i = 0; key[i] != '\0';i++){
        hash = (hash * 31  + key[i] ) % capacity;
    }

    return hash;
}

void print(HashMap *hm)
{
    for (int i = 0; i < hm->size; ++i)
    {
        printf("\t  HASHED-INDEX[%d] | KEY[%s] -- VALUE[%d] \n ",hash(hm->tab[i].key,hm->capacity), hm->tab[i].key, *((int *)hm->tab[i].data));
    }
    return;
}
void free_hashmap(HashMap *hm)
{
    if (!hm) return;

    for (int i = 0; i < hm->size; ++i)
    {
        free(hm->tab[i].key);
        free(hm->tab[i].data);
    }
    free(hm->tab);
    free(hm);
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
