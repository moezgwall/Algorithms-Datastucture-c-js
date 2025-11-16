#include <stdio.h>



int main(){

    const char* path_file = "output.ppm";
    int k = 60;
    int width = 16 * k;
    int height = 9 * k; 
    FILE* f = fopen(path_file, "wb");
    fprintf(f,"P6\n");
    fprintf(f,"%d %d \n",width,height);
    fprintf(f,"255\n");


    for (int j = 0; j < height; ++j)
    {
        for (int i= 0 ; i < width; ++i)
        {
            if ((i/60 + j/60) % 2 == 0)
            {
                fputc(0xFF,f);
                fputc(0x00,f);
                fputc(0x00,f);

            }else{

                fputc(0x00,f);
                fputc(0x00,f);
                fputc(0x00,f);
            }


        }
    }

    


    
    printf(" generating .ppm format file <%s>", path_file);







    return 0;

}