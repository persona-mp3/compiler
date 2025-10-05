#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * So we can have the following types of tokens:
 * - Type token (int, string, bool, char)
 * - Assignment token(=)
 * - Delimeter token(;)
 * - VariableName token
 * - Identifier token -> (fn, class)
 *
 *   strcopy(char *dst, const char *src)
 * */
// #define TYPE_TOKEN 0
// #define ASSIGNMENT_TOKEN 1
// #define DELIMETER_TOKEN 2
// #define VALUE_TOKEN 3
// #define IDENTIFIER_TOKEN 4
// #define UNIDENTIFIED -1
//
// const char INT_LIT[] = "int";
// const char STR_LIT[] = "string";
// const char BOOL_LIT[] = "bool";
// const char ASSIGNEMT_LIT[] = "=";
// const char DELIMETER_LIT[] = ";";
// const char FN_LIT[] = "fn";
//
typedef struct {
  int kind;
  char val[];
} Token;

Token Factory(char *str[]);

int readFile(char *fileName[]) {
  FILE *fptr;
  fptr = fopen(*fileName, "r");
  if (!fptr) {
    printf("[x] failed to open file\n");
    return EXIT_FAILURE;
  }

  char *word[1024];
  Token token;

  while (fscanf(fptr, "%1023s", *word)) {
    puts(*word);
    printf("new token -> %s, %d", token.val, token.kind);
    token = Factory(word);
  }
  printf("new token -> %s, %d", token.val, token.kind);
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("enter filepath to read\n");
    return 0;
  }

  for (int i = 0; i < argc; i++) {
    printf("arg[%d] -> %s\n", i, argv[i]);
  }
  readFile(&argv[1]);
  return 0;
}
