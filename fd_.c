#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  File descriptor implementation (naive approach for educational purposes)
*/

struct fd{
    char* file_name;
    int buffer[1024];
    int pos;
    int still_open;
};

#define MAX_FD 1024
struct fd* fd_table[MAX_FD];

int oopen(const char* name){
    int is_free = -1;
    for (int i=0;i< MAX_FD;i++){
        if (fd_table[i] == NULL || fd_table[i]->still_open ==0){
            is_free = i;
            break;
        }

    }
    if (is_free == -1){
        printf("Error: Out of file descriptors");
        return -1;
    }
    if (fd_table[is_free] == NULL){
        fd_table[is_free] = (struct fd*)malloc(sizeof(struct fd));
    }
    fd_table[is_free]->file_name = strdup(name);
    memset(fd_table[is_free]->buffer,0,sizeof(fd_table[is_free]->buffer));
    fd_table[is_free]->pos = 0;
    fd_table[is_free]->still_open = 1;

    return is_free;

}

int wwrite(int fd,int data){
    if (fd<0 || !fd_table[fd] || fd >=MAX_FD ||!fd_table[fd]->still_open){
        return -1;
    }

    struct fd* current_file = fd_table[fd];
    if (current_file->pos >= 1024){
        return -2;
    }
    current_file->buffer[current_file->pos] = data;
    current_file->pos++;
    return 0;

}

void cclose(int fd){
    if (fd <0 || fd>=MAX_FD || !fd_table[fd]||!fd_table[fd]->still_open) return;
    free(fd_table[fd]->file_name);
    fd_table[fd]->file_name = NULL;
    fd_table[fd]->still_open = 0;
    fd_table[fd]->pos = 0;
    return;
}

int main(){

memset(fd_table,0,sizeof(fd_table));
int fd_ = oopen("logs.txt");
printf("file_name: %s , FD: %d \n",__FILE__,fd_);
wwrite(fd_,100);
wwrite(fd_,200);
cclose(fd_);
return 0;
}
