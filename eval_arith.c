#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// NAIVE IMPLEMENTATION OF EVAL EXPR IN C 


// DOESNT SUPPORT OPERATOR PRECEDENCE 
// TODO FIX IT 

double eval_expression(char* expr){
    double res = 0; 
    char op = '+';
    char* ptrexp = expr;

    while(*ptrexp){
        // skip space
        if (isspace(*ptrexp)){
            ptrexp++;
            continue;
        }

      if (isdigit(*ptrexp) || (*ptrexp == '-' &&  (ptrexp == expr || *(ptrexp - 1) == '+' || *(ptrexp - 1) == '-' || *(ptrexp - 1) == '*' || *(ptrexp - 1) == '/'))){
            char buffer[32];
            int i =0;
             // copy
            if( *ptrexp == '-'){
            buffer[i++] = *ptrexp;
            ptrexp++;
            }
             while(*ptrexp && (isdigit(*ptrexp) || *ptrexp == '.')){
                        buffer[i++] = *ptrexp;
                        ptrexp++;
            }

            buffer[i] = '\0';
             // not atoi , atof
            double tonumb = atof(buffer);

            if (op == '+') res += tonumb;
            else if (op == '-') res -= tonumb;
            else if (op == '*') res *= tonumb;
            else if (op == '/') res /= tonumb;

             continue;
         }

             if (*ptrexp == '+' || *ptrexp == '-' || *ptrexp == '*' || *ptrexp == '/'  ){
                        op = *ptrexp;
                        ptrexp++;
                        continue;
             }

            // others skip
            ptrexp++;

    }

    return res;

}



// refactor the eval_expression 
// space_ignore
static inline void ignore_space(char** p){
    while (isspace(**p)) (*p)++;
}







int main(){
    printf(" evalute the expression  , type <exit> to quit. \n ");
    char expression[256];
    while (1){
        printf(">> ");
    if ( fgets(expression,sizeof(expression),stdin) == NULL) break;
        // newline
        expression[strcspn(expression,"\n")] = '\0';

        if (strcmp(expression,"exit") == 0) break;

        double res = eval_expression(expression);
        printf(":= %.4f \n" , res);

    }


    return 0;

}