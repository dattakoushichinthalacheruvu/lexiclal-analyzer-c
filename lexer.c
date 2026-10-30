#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

int isKeyword(char *word)
{
    char *keywords[] =
    {
        "auto", "break", "case", "char", "const",
        "continue", "default", "do", "double",
        "else", "enum", "extern", "float", "for",
        "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile",
        "while"
    };

    int count = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

int isIdentifierStart(char ch)
{
    if (isalpha(ch) || ch == '_')
    {
        return 1;
    }

    return 0;
}

int isIdentifierPart(char ch)
{
    if (isalnum(ch) || ch == '_')
    {
        return 1;
    }

    return 0;
}

int isSpecialSymbol(char ch)
{
    if (ch == '(' || ch == ')' ||
        ch == '{' || ch == '}' ||
        ch == '[' || ch == ']' ||
        ch == ';' || ch == ',' ||
        ch == '.')
    {
        return 1;
    }

    return 0;
}

int isOperator(char ch)
{
    if (ch == '+' || ch == '-' ||
        ch == '*' || ch == '/' ||
        ch == '%' || ch == '=' ||
        ch == '<' || ch == '>' ||
        ch == '!' || ch == '&' ||
        ch == '|' )
    {
        return 1;
    }

    return 0;
}

int isConstant(char *word)
{
    int i = 0;

    if (word[0] == '\0')
    {
        return 0;
    }

    while (word[i] != '\0')
    {
        if (!isdigit(word[i]))
        {
            return 0;
        }

        i++;
    }

    return 1;
}

void lexicalAnalyzer(char *filename)
{
    FILE *fp;
    char ch;
    char token[MAX_TOKEN];
    int i;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Unable to open file\n");
        return;
    }

    printf("\n");
    printf("========================================\n");
    printf("         LEXICAL ANALYZER OUTPUT\n");
    printf("========================================\n\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace(ch))
        {
            continue;
        }

        if (isalpha(ch) || ch == '_')
        {
            i = 0;

            while (isIdentifierPart(ch))
            {
                if (i < MAX_TOKEN - 1)
                {
                    token[i] = ch;
                    i++;
                }

                ch = fgetc(fp);
            }

            token[i] = '\0';

            if (isKeyword(token))
            {
                printf("KEYWORD      : %s\n", token);
            }
            else
            {
                printf("IDENTIFIER   : %s\n", token);
            }

            ungetc(ch, fp);
        }

        else if (isdigit(ch))
        {
            i = 0;

            while (isdigit(ch))
            {
                if (i < MAX_TOKEN - 1)
                {
                    token[i] = ch;
                    i++;
                }

                ch = fgetc(fp);
            }

            token[i] = '\0';

            printf("CONSTANT     : %s\n", token);

            ungetc(ch, fp);
        }

        else if (ch == '"')
        {
            i = 0;
            token[i++] = ch;

            ch = fgetc(fp);

            while (ch != '"' && ch != EOF)
            {
                if (i < MAX_TOKEN - 2)
                {
                    token[i] = ch;
                    i++;
                }

                ch = fgetc(fp);
            }

            if (ch == '"')
            {
                token[i++] = ch;
            }

            token[i] = '\0';

            printf("STRING       : %s\n", token);
        }

        else if (ch == '\'')
        {
            i = 0;
            token[i++] = ch;

            ch = fgetc(fp);

            if (ch != EOF)
            {
                token[i++] = ch;
            }

            ch = fgetc(fp);

            if (ch == '\'')
            {
                token[i++] = ch;
            }

            token[i] = '\0';

            printf("CHARACTER    : %s\n", token);
        }

        else if (ch == '/')
        {
            char next;

            next = fgetc(fp);

            if (next == '/')
            {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF)
                {
                }

                printf("COMMENT      : Single line comment\n");
            }
            else if (next == '*')
            {
                char previous = 0;

                while ((ch = fgetc(fp)) != EOF)
                {
                    if (previous == '*' && ch == '/')
                    {
                        break;
                    }

                    previous = ch;
                }

                printf("COMMENT      : Multi line comment\n");
            }
            else
            {
                printf("OPERATOR     : /\n");
                ungetc(next, fp);
            }
        }

        else if (isOperator(ch))
        {
            char next;

            next = fgetc(fp);

            if ((ch == '+' && next == '+') ||
                (ch == '-' && next == '-') ||
                (ch == '=' && next == '=') ||
                (ch == '!' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|'))
            {
                printf("OPERATOR     : %c%c\n", ch, next);
            }
            else
            {
                printf("OPERATOR     : %c\n", ch);
                ungetc(next, fp);
            }
        }

        else if (isSpecialSymbol(ch))
        {
            printf("SPECIAL      : %c\n", ch);
        }

        else
        {
            printf("UNKNOWN      : %c\n", ch);
        }
    }

    fclose(fp);

    printf("\n========================================\n");
    printf("       LEXICAL ANALYSIS COMPLETED\n");
    printf("========================================\n");
}