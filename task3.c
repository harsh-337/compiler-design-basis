#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

// List of keywords
const char *keywords[] = {
    "int", "float", "char", "if", "else", "while", "for", "return", "void", "main"
};

// Check if string is a keyword
int isKeyword(const char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Check if character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || 
            ch == '=' || ch == '<' || ch == '>' || ch == '!');
}

// Lexical analyzer function
void lexicalAnalyzer(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    char ch, buffer[MAX_LEN];
    int idx = 0;

    while ((ch = fgetc(fp)) != EOF) {
        // Identifiers or keywords
        if (isalpha(ch) || ch == '_') {
            buffer[idx++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_')
                buffer[idx++] = ch;
            buffer[idx] = '\0';
            idx = 0;

            if (isKeyword(buffer))
                printf("[KEYWORD]: %s\n", buffer);
            else
                printf("[IDENTIFIER]: %s\n", buffer);

            ungetc(ch, fp); // put back non-alnum character
        }
        // Operators
        else if (isOperator(ch)) {
            char next = fgetc(fp);
            if ((ch == '=' || ch == '!' || ch == '<' || ch == '>') && next == '=') {
                printf("[OPERATOR]: %c%c\n", ch, next);
            } else {
                printf("[OPERATOR]: %c\n", ch);
                ungetc(next, fp);
            }
        }
        // Skip whitespace and others
        else if (isspace(ch) || ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {
            continue;
        }
    }

    fclose(fp);
}

int main() {
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);

    printf("\n--- Lexical Analysis Output ---\n");
    lexicalAnalyzer(filename);

    return 0;
}