#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} Vector;

Vector *make_vec(size_t capacity)
{
    Vector *vec = malloc(sizeof(Vector));
    if (!vec)
    {
        return NULL;
    }
    vec->capacity = capacity;
    vec->size = 0;
    vec->data = malloc(capacity * sizeof(int));
    if (!vec->data)
    {
        return NULL;
    }

    return vec;
}

void push_element(Vector *vec, int data)
{
    if (!vec)
    {
        return;
    }
    if (vec->size >= vec->capacity)
    {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(int));
        if (!vec->data)
        {
            return;
        }
    }
    vec->data[vec->size++] = data;
}

int main()
{
    Vector *vec = make_vec(5);
    push_element(vec, 15);
    printf("%d", vec->data[0]);

    return 0;
}