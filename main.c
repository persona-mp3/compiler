#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "utils.h"

FILE *readFile(char *name);
int doStuff(FILE *fptr, char *fName);
bool lexer(FILE *f);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("enter file path to read\n");
    return -1;
  }

  char *fileName = argv[1];
  FILE *f = readFile(fileName);
  if (!f) {

    return -1; // could've returned the error here
  }

  doStuff(f, fileName);

  return EXIT_SUCCESS;
}

/*
 * readFile opens the file in rb mode and returns pointer to the file
 * to the caller, who is responsible for closing the file.
 * */
FILE *readFile(char *name) {
  FILE *fptr;

  fptr = fopen(name, "r");
  if (!fptr) {
    printf("could not open file %s\n", name);
    return NULL;
  }

  return fptr;
}

int doStuff(FILE *fptr, char *fName) {
  struct stat fileInfo;
  if (stat(fName, &fileInfo) != 0) {
    printf("error getting stat info for %s\n", fName);
    perror("e-> :");
    return EXIT_FAILURE;
  };

  if (!fptr) {
    printf("WHAT?? Get the fck outta here, want to get with a segfault\n");
    perror("e-> :");
    return EXIT_FAILURE;
  }

  int fileSize = fileInfo.st_size;
  // process file in chunks
  int CHUNK = 1023;
  size_t bytesRead;
  // fread(dest, rate, dest(size), src)

  bool isWhat = lexer(fptr);
  return EXIT_SUCCESS;
}

// so we could just vlose the buffer from there
typedef struct {
  char *value;
  int id;
} Tokens;

bool lexer(FILE *f) {

  char *line = NULL;
  size_t limit = 0;
  char **c;
  int sucess;
  while ((sucess = getline(&line, &limit, f)) != -1) {
    if (!line) {
      printf("footGun!!, line is null\n");
      perror("e-> :");
      return false;
    }
    c = toArray(line);
    printf("sizeof %lu\n", sizeof(c));
    for (int i = 0; i < sizeof(c); i++) {
      printf("%s\n", c[i]);
    }
    break;
  }

  // free(c);
  fclose(f);
  return true;
}

// MASSIVE SEGAULR
