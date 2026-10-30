#include <stdio.h>
#include "lexer.h"

int main()
{
    char filename[100];

    printf("Enter input C file name: ");
    scanf("%s", filename);

    lexicalAnalyzer(filename);

    return 0;
}