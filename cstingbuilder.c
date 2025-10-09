#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *data;
    size_t size;
    size_t capacity;
} StringBuilderS;

void init(StringBuilderS *sb)
{
    sb->size = 0;
    sb->capacity = 128;
    sb->data = malloc(sb->capacity * sizeof(char));
    if (!sb->data){
        fprintf(stderr,"failed to allocate memory.");
        return;
    }
    sb->data[sb->size] = '\0';

}

void append(StringBuilderS *sb, const char *str)
{
    size_t nlen = sb->size + strlen(str);
    size_t nstr = strlen(str);
    if ((nlen + 1) > sb->capacity)
    {
        sb->capacity = (nlen + 1) * 2;
        sb->data = realloc(sb->data, sb->capacity);
        if (!sb->data){
            fprintf(stderr,"failed to allocate memory");
            return;
        }
    }
    //strcpy(sb->data + sb->size, str); -> NOT SFAE
    memcpy(sb->data + sb->size, str,nstr + 1);
    sb->size = nlen;
}

void freeSbuilder(StringBuilderS *sb)
{
    if (!sb)
    {
        return;
    }
    free(sb->data);
    sb->data = NULL;
    sb->capacity = 0;
    sb->size = 0;
}

size_t getSize(const StringBuilderS* sb){
        if(!sb){
            return 0;
        }
        return sb->size;
}

size_t getCapacity(const StringBuilderS* sb){
        if(!sb){
            return 0;
        }
        return sb->capacity;
}

void clear(StringBuilderS* sb){
    if(!sb || !sb->data) return;
    sb->size = 0;
    sb->data[0] = '\0';
    return;
}

char* getSuffix(const StringBuilderS* sb, char c){
         if (!sb || !sb->data) return strdup("");   

         char* pos = strchr(sb->data , c);
         if (!pos) return strdup("");

         return strdup(pos);
}

char* getPrefix(const StringBuilderS* sb , char c){
        if (!sb || !sb->data) return strdup("");
        char* pos = strchr(sb->data,c);
        size_t len;
        if (pos){
        len = (size_t) (pos - sb->data);
        }else{
        len = sb->size; 
        }
        char* prefix = malloc(len + 1);
        if (!prefix) return NULL;

        strncpy(prefix,sb->data,len);
        prefix[len] = '\0';

        return prefix;
}

int main(int argc, const char **argv)
{
    StringBuilderS sb;
    init(&sb);
    append(&sb, "YOUR");
    append(&sb, "MOM");
    append(&sb, "69");
    printf("%s \n", sb.data);
    /* test suffix*/
    StringBuilderS new;
    init(&new);
    append(&new,"file.c");
    char* suffix = getSuffix(&new,'.');
    printf("suffix : %s \n",suffix);

    /*test prefix*/
    char* prefix = getPrefix(&new,'.');
    printf("prefix : %s \n",prefix);

    /* get the size*/
    printf("size : %zu .\n",getSize(&sb));
    /* get capacity*/
    printf("capacity : %zu .\n",getCapacity(&sb));


    freeSbuilder(&sb);
    freeSbuilder(&new);
    return 0;
}