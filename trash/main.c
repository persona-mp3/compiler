#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reader(const char fname[]) {
  // char file_name[] = "contact-details.js"
  printf("reading -> %s\n", fname);
  FILE *fptr;
  fptr = fopen(fname, "r+");
  if (!fptr) {
    printf("error_n -> %d\n", errno);
    perror("error: ");
    return;
  }

  char line[255];
  while (fgets(line, sizeof(line) + 1, fptr)) {
    printf("%s",  line);
  }
  fclose(fptr);


  return;
}

int main() {
  printf("welcome to the c-implementation of reno\n");
  char fname[30];
  printf("enter the file you wish to read: \n");
  // When 'enter' is hit, \n is appended to the end to the str
  // making fopen to return 2, File Doesn't exist
  // fgets(fname, 30, stdin);
  scanf("%s", fname);

  reader(fname);
  return 0;
}
