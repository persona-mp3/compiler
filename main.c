#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "factory.h"
#include "split.h"

Token Factory(char *str);

int file_reader(char *name) {
  FILE *fh;
  struct stat fstats;
  const int CHUNK = 4;

  fh = fopen(name, "r");
  if (stat(name, &fstats) == -1) {
    perror("failed to get stat -> %s: ");
    return EXIT_FAILURE;
  }

  if (!fh) {
    perror("failed to open file -> %s\n");
    return EXIT_FAILURE;
  }

  int fsize = fstats.st_size;
  char buff[fsize + 1];

  size_t bytes_read;
  while ((bytes_read = fread(buff, CHUNK, fsize, fh)) > 0) {
    printf("%lu, %d\n", bytes_read, fsize);
  }
  buff[fsize + 1] = '\0';

  printf("%lu, %d\n", bytes_read, fsize);
  printf("%s\n", buff);
  fclose(fh);
  // and then we can then parse each line and tokenize it using strtok
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("enter filepath to read\n");
    return 0;
  }
  file_reader(argv[1]);
  return 0;
}
