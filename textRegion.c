#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// im building a little lexer 
// my idea is to treat the whole text as a region 
// and extract from it a sub regions and process them
// \*.*/ -> 


typedef enum{
    TOKEN_TEXT=1,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_EOF,
    TOKEN_SYMBOL // for the delimiters except the space
}TOKEN_TYPE;

void tokenToStr(TOKEN_TYPE token){
    switch (token)
    {
    case TOKEN_TEXT:
        printf("[TEXT] \n");break;
    case TOKEN_KEYWORD:
        printf("[KEYWORD] \n");break;
    case TOKEN_NUMBER:
        printf("[NUMBER] \n");break;
    case  TOKEN_EOF:
        printf("[ENDFILE] \n");break;
    case  TOKEN_SYMBOL:
        printf("[SYMBOL] \n");break;
    default:
        printf("[UNKOWN] \n");
    };
    
    return;
}


typedef struct{
    char* rtext;
    size_t len;
    size_t size;
    TOKEN_TYPE type;
    void (*withType)(TOKEN_TYPE);
}textRegion;

const char* delimters = ".,-*/|;#&:!? ";
const char* reserved_keywords[] = {
    "static",
    "int",
    "void",
    "float",
    "double",
    "char",
    "extern",
    "const",
    "volatile",
    "inline",
    "main",
    "register",
    "auto",
    "typeof",
    "sizeof",
    "size_t",
    "return",
    "true",
    "false",
    "argc",
    "argv"
};

bool isReservedKeyWord(const char* word){
    size_t nb_keywords = sizeof(reserved_keywords) / sizeof(reserved_keywords[0]);
    for (size_t i = 0; i < nb_keywords;i++){
        if (strcmp(reserved_keywords[i],word) == 0){
            return true;
        }
    }
    return false;
}


bool isDelimiter(char c , const char* delimters){
    while(*delimters){
        if (c == *delimters){
            return true; 
        }
        delimters++; 
    }
    return false; 
}

textRegion getSubRegion(char** text){

    while(**text !='\0' && isDelimiter(**text,delimters)){
        (*text)++;
    }

    if(**text == '\0'){
        
        return (textRegion){NULL,0,0};
    }

    char* begin_region = *text;
    char* end_region = begin_region;

    while (*end_region !='\0' && !isDelimiter(*end_region,delimters)){
        end_region++;
    }
    size_t regionLen = (size_t) (end_region - begin_region);
   
    char* word = malloc(regionLen + 1);
    memcpy(word,begin_region,regionLen);
    word[regionLen] = '\0';


    if (*end_region == ' '){
        *text = end_region+1;
    }else{
        *text = end_region;
    }

    textRegion rt;
    rt.rtext = word;
    rt.len = regionLen;
    rt.size = regionLen;
    rt.type = isReservedKeyWord(word) ? TOKEN_KEYWORD : TOKEN_TEXT;
    rt.withType = &tokenToStr;
    return rt;
}

int getSubRegionCount(char* text){
    char* txt = strdup(text);
    char* ptrText = txt;
    int countRegions = 0;
    while (*ptrText != '\0'){
        textRegion tx = getSubRegion(&ptrText);
        if (tx.rtext != NULL && tx.len > 0){
            countRegions++;
            free(tx.rtext);
        }
    }
    free(txt);
    return countRegions;
}



int main(){
    char input[] = "sizeof const love|extra gwall.test.main,zozin email sprase*info float|int";
    char* ptr = input;
    const char* textInput = input;
    int nregions = getSubRegionCount(ptr);
    while (*ptr != '\0') {
        textRegion region = getSubRegion(&ptr);
        printf("Sub-Region: '%s' ,Length: %zu ,Type: ", region.rtext, region.len);
        region.withType(region.type);
        free(region.rtext);
    }
    printf("Number of Sub Regions: [%d] \n",nregions);
    return 0;
}