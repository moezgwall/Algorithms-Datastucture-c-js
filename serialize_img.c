#include <stdio.h>
#include <stdlib.h>

void serialize_img(const char* file_path)
{
    FILE* new_file = fopen(file_path,"rb");
    if(!new_file)
    {
        fprintf(stderr,"failed to open that file :  <%s>" , file_path);
        return;
    }

    
    fseek(new_file,0,SEEK_END);
    size_t file_size = ftell(new_file);
    fseek(new_file,0,SEEK_SET);
    
    unsigned char* buffer = (unsigned char*) malloc(file_size);
    if(!buffer){
        fprintf(stderr,"failed to allocate memory");
        free(buffer);
        fclose(new_file);
        return;
    }

    size_t buffer_size = fread(buffer,1,file_size,new_file);
    if (buffer_size != file_size){
        fprintf(stderr,"ERROR: SOMETHING WRONG");
        free(buffer);
        fclose(new_file);
        return;
    }   

    for(size_t i = 0; i < file_size; ++i){
        printf("%02x",buffer[i]);
    }


    fclose(new_file);
    free(buffer);
}


int main()
{
    const char* file_path  = "C:\\zeus\\output.ppm";
    serialize_img(file_path);



    return 0;
}