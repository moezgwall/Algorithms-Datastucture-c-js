
#ifndef STR_IMPL
#define STR_IMPL

const char *reserved_keywords[] = {
    "auto",
    "break",
    "continue",
    "while",
    "do",
    "goto",
    "if",
    "else",
    "switch",
    "case",
    "NULL",
    "for",
    "struct",
    "typedef",
    "define",
    "int",
    "char",
    "bool",
    "double",
    "float",
    "static",
    "inline",
    "long",
    "short",
    "volatile",
    "sizeof",
    "extern",
    "const", "union", "enum"};

bool isKeyword(const char *str)
{
    size_t len = sizeof(reserved_keywords) / sizeof(reserved_keywords[0]);
    for (size_t i = 0; i < len; ++i)
    {
        if (strcmp(str, reserved_keywords[i]) == 0)
            return true;
    }
    return false;
}

bool isDelimiter(char c)
{
    return (c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '{' || c == '}' || c == '[' || c == ']' ||
            c == ',' || c == '(' || c == ')' || c == ';' || c == ':');
}

bool isOperator(char c)
{
    return (c == '<' || c == '+' || c == '-' || c == '*' || c == '/' || c == '>');
}

bool isNumeric(const char *str)
{
    if (!str || *str == '\0')
    {
        return false;
    }
    size_t count = 0;
    while (isdigit(*(str + count)))
    {
        count++;
    }

    return (str[count] == '\0');
}
#endif