#include <stdio.h>
#include <string.h>

/*
 * string_view : example 
 * idea : from @tsoding
 * */

typedef struct {
    char* data;
    size_t count;
}Str_view;

Str_view init_str_view(char* cstr){
        return (Str_view){
            .data = cstr,
            .count = strlen(cstr),
        };
}

void chop_from_bg(Str_view* str){
        str->count -=1;
        str->data +=1; 
}
void chop_from_end(Str_view* str){
        str->count -=1;
}

int main()
{
    Str_view sv = {0};
    char* cstr = "hello world";
    sv = init_str_view(cstr);
    printf("original : %.*s\n",sv.count,sv.data);
    chop_from_end(&sv);
    printf("chopped from end: %.*s\n",sv.count,sv.data);
    
    return 0;
}
