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

typedef struct {
  int kind;
  char val[100];
} Token;

Token Factory(char *str);

int readFile(char *fileName[]) {
  FILE *fptr;
  fptr = fopen(*fileName, "r");
  if (!fptr) {
    printf("[x] failed to open file\n");
    return EXIT_FAILURE;
  }

  char word[1024];
  Token token;

  while (fscanf(fptr, "%1023s", word) == 1) {
    token = Factory(word);
    printf("Token -> %s | Value: %d\n", token.val, token.kind);
  }
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("enter filepath to read\n");
    return 0;
  }
  readFile(&argv[1]);
  return 0;
}
