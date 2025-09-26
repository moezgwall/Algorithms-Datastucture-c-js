#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    const char *data;
    size_t size;
} StringViewS;

/* we create a string-view from this
    trash: const char* str
*/
static inline StringViewS SvFromStr(const char *str)
{
    StringViewS strview = {0};
    strview.data = str;
    strview.size = strlen(str);

    return strview;
}

/* using memcmp to compare on bytes level ,since our string view is not NULL TERMINATED
and not using strcmp beacause of this fucking NULL TERM '\0'
*/
static inline bool CompareSv(StringViewS a, StringViewS b)
{
    return a.size == b.size && memcmp(a.data, b.data, a.size) == 0;
}

int main()
{

    StringViewS str = SvFromStr("YOUR MOM");
    StringViewS str1 = SvFromStr("YOUR MOM");
    printf("are they same words : %d", CompareSv(str, str1));

    return 0;
}