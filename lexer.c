#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
// TOKENS TYPES

typedef enum
{
    TOKEN_IDENTIFIER = 10,
    TOKEN_NUMBER = 11,
    TOKEN_SEMICOLON = 12,
    TOKEN_DOT = 13,
    TOKEN_EXCLAMATION = 14,
    TOKEN_UNKNOWN = 15,
    TOKEN_EOF = 16,
} TOKEN_T; // stands for token type

typedef struct
{
    char *text;
    int size;
    TOKEN_T type;
} TOKEN;

// check for the token type

const char *token_to_str(TOKEN_T token_t)
{
    switch (token_t)
    {
    case TOKEN_IDENTIFIER:
        return "IDENTIFIER";
    case TOKEN_NUMBER:
        return "NUMBER";
    case TOKEN_SEMICOLON:
        return "SEMICOLON";
    case TOKEN_DOT:
        return "DOT";
    case TOKEN_EXCLAMATION:
        return "EXCLAMATION";
    case TOKEN_UNKNOWN:
        return "UNKNOWN";
    case TOKEN_EOF:
        return "EOF";
    default:
        return "INVALID_TOKEN";
    }
}

// TOKENIZER $$$$

TOKEN tokenizer(char **text)
{
    char *start = *text;
    // first check for whitespace
    while (isspace(*start))
    {
        start++;
    } // skip spaces
    // new post # space
    *text = start;

    // empty input ?
    if (**text == '\0')
    {
        TOKEN token = {.text = *text, .size = 0, .type = TOKEN_EOF};
        return token;
    }

    char c = **text;

    if (isalpha(c) || c == '_')
    {
        char *begin = *text;
        while (isalnum(**text) || **text == '_')
        {
            (*text)++;
        }
        TOKEN token = {.text = begin,
                       .size = (int)(*text - begin),
                       .type = TOKEN_IDENTIFIER};
        return token;
    }

    if (isdigit(c))
    {
        char *begin = *text;
        while (isdigit(**text))
        {
            (*text)++;
        }
        TOKEN token = {.text = begin,
                       .size = (int)(*text - begin),
                       .type = TOKEN_NUMBER};
        return token;
    }

    // other characters like ; . !
    (*text)++;
    switch (c)
    {

    case ';':
        return (TOKEN){*text - 1, 1, TOKEN_SEMICOLON};
    case '.':
        return (TOKEN){.text = *text - 1,
                       .size = 1,
                       .type = TOKEN_DOT};
    case '!':
        return (TOKEN){.text = *text - 1,
                       .size = 1,
                       .type = TOKEN_EXCLAMATION};
        ;
    default:
        return (TOKEN){.text = *text - 1,
                       .size = 1,
                       .type = TOKEN_UNKNOWN};
    }
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        char *txt = argv[1];

        TOKEN token = {NULL};

        while (token.type != TOKEN_EOF)
        {
            token = tokenizer(&txt);
            printf("TOKEN : %s [", token_to_str(token.type));
            for (int i = 0; i < token.size; i++)
            {
                putchar(token.text[i]);
            }
            printf("].\n");
        }
    }
    else
    {
        printf("feed the str via command line .... \n");
    }
    return 0;
}