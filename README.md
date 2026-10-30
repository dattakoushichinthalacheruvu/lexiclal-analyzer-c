# Lexical Analyzer in C

A C-based lexical analyzer that scans source code and identifies tokens like keywords, identifiers, operators, constants, and special symbols.

### Features
- Identifies Keywords, Identifiers, Operators, Separators
- Detects Constants and Header files
- Counts number of tokens
- Handles C language syntax
- Removes comments and whitespaces

### How it Works
- Reads C source file character by character
- Uses Finite State Machine to classify tokens
- Checks keywords from predefined list
- Outputs token type for each lexeme

### Tech Stack
- Language: C / Lex
- Concepts: Compiler Design, File Handling, String Processing
- Tools: GCC, Lex/Flex (optional)

### How to Run
```bash
gcc lexical.c -o lexical
./lexical input.c
