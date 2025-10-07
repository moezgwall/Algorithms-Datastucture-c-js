#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
// another impelementation for cvector
// this time it's generic , maybe 
// enjoy

typedef struct{
    void* items; 
    size_t size; 
    size_t capacity; 
    size_t type_size;
}cVector;

cVector* init(size_t capacity , size_t ts){
    cVector* vec = (cVector*) malloc(sizeof(cVector)); 
    vec->size = 0; 
    vec->capacity = capacity;
    vec->type_size = ts;
    assert(capacity > 0);
    vec->items =  malloc(vec->type_size * vec->capacity);

    return vec;
}

void append(cVector* cvec, void* data){
    if (!cvec) return;
    if (!data) return;
    if (cvec->size == cvec->capacity ){
        cvec->capacity *=2;
        cvec->items = realloc(cvec->items,cvec->type_size *cvec->capacity);
    }
    void* chunk = ((char*)cvec->items) + (cvec->size * cvec->type_size);
    memcpy(chunk,data,cvec->type_size);
    cvec->size +=1;
    return;
}

void cvecFree(cVector* cvec){
       if (!cvec) return;
       free(cvec->items);
       free(cvec);
       return;
}

void* get(cVector* cvec , int index){
        if (!cvec || index < 0) return;
        void * element = ((char*)cvec->items) + (index * cvec->type_size);
        return element;

}
int main(void){
    // string example 
    cVector* vec = init(2,128);
    char* x="alexy";
    char* y="tarval";
    char* z="sokoardi";
    append(vec,x);
    append(vec,y);
    append(vec,z);
    for (int i = 0 ; i <vec->size; i++){
        char* s = (char*)get(vec,i);
        printf("%s \n" , s );
    }
    cvecFree(vec);
    printf("\n");
    //float example
    cVector* cvec = init(2,sizeof(float));
    float xx=1.07;
    float yy=1.99;
    float zz=999.8;
    append(cvec,&xx);
    append(cvec,&yy);
    append(cvec,&zz);
    for (int i = 0 ; i <cvec->size; i++){
        printf("%f \t " ,((float*)cvec->items)[i]);
    }
    cvecFree(cvec);



    return 0;
}