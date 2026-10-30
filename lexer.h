#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN 100

int isKeyword(char *word);
int isIdentifierStart(char ch);
int isIdentifierPart(char ch);
int isSpecialSymbol(char ch);
int isOperator(char ch);
int isConstant(char *word);
void lexicalAnalyzer(char *filename);

#endif