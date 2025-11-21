#include <stdio.h>
#include <stdlib.h>

unsigned char* serialize_img(const char* file_path)
{
    FILE* new_file = fopen(file_path,"rb");
    if(!new_file)
    {
        fprintf(stderr,"failed to open that file :  <%s>" , file_path);
        return NULL;
    }
    fseek(new_file,0,SEEK_END);
    size_t file_size = ftell(new_file);
    fseek(new_file,0,SEEK_SET);
    
    unsigned char* buffer = (unsigned char*) malloc(file_size);
    if(!buffer){
        fprintf(stderr,"failed to allocate memory");
        fclose(new_file);
        return NULL;
    }

    size_t buffer_size = fread(buffer,1,file_size,new_file);
    if (buffer_size != file_size){
        fprintf(stderr,"ERROR: SOMETHING WRONG");
        free(buffer);
        fclose(new_file);
        return NULL;
    }   
        
    fclose(new_file);
    return buffer;
}


// TODO : serialize in chunks of memory 
#define MEMO_CHUNK 1024*1024  // 1 MB

void serialize_b_chunk(void);







int main()
{
    const char* file_path  = "C:\\zeus\\output.ppm";
    unsigned char* buffer = serialize_img(file_path);

   

    return 0;
}