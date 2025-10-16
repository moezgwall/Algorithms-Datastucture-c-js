#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// XOR to find the difference 
// of 2 cstrings 
// 1 char diff



char findDiffernce(char* str1,char* str2){

    char ch = 0;
    while (*str1 != '\0'){

        ch = ch ^ *str1;

        str1++;
    }

     while (*str2 != '\0'){

        ch = ch ^ *str2;

        str2++;
    }
    
    return ch;
    

}


int main(void){
    printf("%c",findDiffernce("moezgwall","moezwall"));
    // output is : g
    return 0;
}