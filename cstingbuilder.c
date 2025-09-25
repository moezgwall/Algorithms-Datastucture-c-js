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
    sb->data = malloc(sb->capacity);
    // empty str just contain '\0'
    // but ill ignore that hehehe
}

void append(StringBuilderS *sb, const char *str)
{
    size_t nlen = sb->size + strlen(str);
    if ((nlen + 1) > sb->capacity)
    {
        sb->capacity = (nlen + 1) * 2;
        sb->data = realloc(sb->data, sb->capacity);
    }
    strcpy(sb->data + sb->size, str);
    sb->size = nlen;
}

void freesb(StringBuilderS *sb)
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

int main(int argc, const char **argv)
{
    StringBuilderS *sb;
    init(sb);
    append(sb, "YOUR");
    append(sb, "MOM");
    append(sb, "69");
    printf("%s", sb->data);
    freesb(sb);
    return 0;
}