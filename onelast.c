#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int word_counter(char *src, char *delim) {
  int len = strlen(src);
  int count = 0;
  for (int i = 0; i < len; i++) {
    while (i < len) {
      if (strchr(delim, src[i]) != NULL) {
        break;
      }
      i++;
    }

    count++;

    while (i < len) {
      if (strchr(delim, src[i]) == NULL) {
        break;
      }
      i++;
    }
  }

  printf("word count -> %d\n", count);
  return count;
  ;
}

void string_split(char *src) {
  char *delims = " ;.*";
  int len = strlen(src);
  int words = word_counter(src, delims);

  // skeptical about this?? doesnt make sense
  char **dest = malloc(words * sizeof(char *));
  char *currWord = malloc(len + 1);
  if (!dest || !currWord) {
    printf("[x] error in allocating for dest or currWord\n");
    return;
  }

  int storePos = 0;
  int srcPos = 0;
  for (int i = 0; i < len; i++) {
    if (src[i] == ' ' || src[i] == ';') {
      // only save a word if its not empty
      if (srcPos > 0) {
        currWord[srcPos] = '\0';
        dest[storePos++] = currWord;
        currWord = malloc(len + 1);
        if (!currWord) {
          printf("[x] error in allocating for new currWord\n");
					for(int i=0;  i < words; i++){
						free(dest[i]);
					}
					free(dest);
          return;
        }
        srcPos = 0;
      }
      continue;
    }
    currWord[srcPos++] = src[i];
  }

  if (srcPos > 0) {
    currWord[srcPos] = '\0';
    dest[storePos++] = currWord;
  }

  for (int i = 0; i < words; i++) {
    printf("%s\n", dest[i]);
    free(dest[i]);
  }

  return;
}

int main(int argc, char *argv[]) {
  char *test = "ragebait fancy shmancy        ";
  string_split(test);
  return 0;
}
