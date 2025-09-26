#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define byte uint8_t

typedef struct
{
    byte *memory;
    size_t capacity;
    size_t offset;
} Arena;

/* Allocate memory block of size 'capacity' bytes for the arena*/
Arena Create_Arena(size_t capacity)
{
    Arena arena = {0}; // we could use memset()
    arena.memory = (byte *)malloc(capacity);
    if (!arena.memory)
    {
        fprintf(stderr, "failed to allocate arena \n");
        exit(1);
    }
    arena.capacity = capacity;
    arena.offset = 0;
    return arena;
}

/* allocating a chunk of memory inside of our arena*/
/* size is the number of bytes to allocate*/
void *Alloc(Arena *arena, size_t size)
{
    if (!arena)
    {
        fprintf(stderr, "failed... \n");
        exit(1);
    }
    if (size == 0)
    {
        exit(1);
    }

    if (arena->offset + size > arena->capacity)
    {
        fprintf(stderr, "failed due to overflow... \n");
        exit(1);
    }
    // pointer arithmetic (ptr+offset)
    // offset starts at 0 and increments by size (in bytes)
    void *ptr = arena->memory + arena->offset;
    arena->offset += size;

    return ptr;
}

void Free_Arena(Arena *arena)
{

    if (!arena)
        return;

    free(arena->memory);
    arena->memory = NULL;
    arena->capacity = 0;
    arena->offset = 0;
}
/* when we call this function we will rewrite the bytes already used*/
void Arena_Reset(Arena *arena)
{
    if (!arena)
        return;

    arena->offset = 0;
}

int main()
{

    Arena arena = Create_Arena(1024);                   // 1kb
    int *data = (int *)Alloc(&arena, sizeof(int) * 32); // 4 * 32 = 128 byte
    if (!data)
    {
        fprintf(stderr, " failed to allocate memory ... \n");
        return -1;
    }

    memset(data, 0, sizeof(int) * 32);

    for (int i = 0; i < 32; i++)
    {
        data[i] = i;
        printf("address [%p] : %d  \n", (data + i), data[i]);
    }
    size_t dataleft = Dataleft(&arena);
    printf("\n %d", dataleft);
    // after arena reset offset = 0 ; but data is still a valid pointer

    return 0;
}