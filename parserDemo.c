#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAX_LEN 512

/*
 *  creating a JSON parser in C.(NOT A LEXER BUT STILL CALL IT PARSER)
 *  another naive approach but who cares!
 * */

typedef struct {
  char str[MAX_LEN];
  size_t count;
} Symbol;

typedef enum { OPEN_BRACKET, CLOSE_BRACKET, PARAM, VALUE } Identifier;

typedef struct Entity Entity;
struct Entity {
  Symbol s;
  Identifier id;
  void (*cb)(char *);
};

Entity table[MAX_LEN];

Symbol init(char *str) {
  Symbol s;
  strcpy(s.str, str);
  s.count = strlen(s.str);
  return s;
}

void parse_symbol(char *str) {
  Symbol s = init(str);
  char *ptr = s.str;
  size_t gc = 0;
  size_t gec = 1;
  while (*ptr != '\0') {
    switch (*ptr) {
    case '{': {
      gc++;
      printf("Identifier :[%c] -> Symbol count : %zu \n", *ptr, gc);
      ptr++;
      break;
    };
    case '}': {
      gc++;
      printf("Identifier : [%c] -> Symbol count : %zu \n", *ptr, gc);
      ptr++;
      break;
    };
    case ':': {
      ptr++;
      while (*ptr != '\0' && *ptr != ':' && *ptr != ',') {
        if (*ptr == ' ')
          ptr++;
        if (isalnum(*ptr)) {
          char buffer[128];
          size_t counter = 0;
          while (isalnum(*ptr) && *ptr != '\0') {
            buffer[counter] = *ptr;
            ptr++;
            counter++;
          }
          buffer[counter] = '\0';
          printf("Value : [%s] -> Expression count : %zu \n", buffer, gec);
          break;
        }
        ptr++;
      }
      break;
    }
    case ' ':
    case '.':
    case '?':
    case '/': {
      ptr++;
      break;
    };
    case ',': {
      ptr++;
      gec++;
      printf("Next Expression : %zu \n", gec);
      continue;
    }
    case ';': {
      gc++;
      printf("Identifier : [%c] -> Symbol count : %zu \n", *ptr, gc);
      printf("End of evaluation. \n");
      ptr++;
      break;
    };
    default: {
      if (isalnum(*ptr)) {
        char buffer[128];
        size_t counter = 0;
        while (isalnum(*ptr) && *ptr != '\0') {
          buffer[counter] = *ptr;
          counter++;
          ptr++;
        }
        buffer[counter] = '\0';
        printf("Param : [%s] --> Expression count : %d \n", buffer, gec);
        break;
      }
      break;
    }
    };
  }
  ptr++;
  return;
}

int main() {

  parse_symbol("{ param: value, param1:value1};");

  return 0;
}
