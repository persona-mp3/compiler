#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void stringsSplit(char *src);
void splitToArr(char *src);

void stringsSplit(char *src) {
  int strLen = strlen(src);
  char *result = malloc(strLen + 1); // allocated on heap
  if (!result) {
    printf("[x] epic failure, could not allocate memory");
    return;
  }
  result[strLen + 1] = '\0';

  char spaceDelimiter = ' ';
  char semiColonDelimiter = ';';
  int pos = 0;
  for (int i = 0; i < strLen; i++) {
    if (src[i] == spaceDelimiter || src[i] == semiColonDelimiter) {
      continue;
    }
    result[pos] = src[i];
    pos++;
  }

  printf("result -> %s\n", result);
  free(result);
  return;
}

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
}
void splitToArr(char *src) {
  /*
   * So if we had length of string; strLen; how many possible items
   * could be in an array of strings, and how many characets can each
   * "string"??/😭 / hold
   * Well?? we coukld just do an array of pointers
   * */
  // club bizzare slowed!! gumgum
  int strSize = strlen(src);
  int word_count = word_counter(src, " ;.*");
  // array of uninitialised pointers?? that have UB behaviour
  char **dest = malloc(word_count * sizeof(char *));
  if (!dest) {
    printf("[x] epic failure in malloc to dest\n");
    return;
  }
  int position = 0;
  char *currWord = malloc(strSize + 1);
  if (!currWord) {
    printf("[x] epic failure in malloc to currWord\n");
    return;
  }
  int storePos = 0;
  currWord[strSize + 1] = '\0';
  for (int i = 0; i < strSize; i++) {
    if (src[i] == ' ' || src[i] == ';') {
      dest[storePos] = currWord;
      dest[storePos] += '\0';
      storePos++;
      currWord = malloc(strSize + 1);
      if (!currWord) {
        printf("[x] epic failure in malloc to currWord\n");
        return;
      }
      currWord[strSize + 1] = '\0';
      position = 0;
      continue;
    }
    currWord[position] = src[i];
		// dest[0] = 0x22357
		// currWord = 0x9832A832
		// dest[0] = valueIn 0x9832A832
    dest[storePos] = currWord;
    position++;
  }
  for (int i = 0; i < word_count; i++) {
    printf("%s\n", dest[i]);
		free(dest[i]);
  }

	free(dest);
  return;
}

int main(int argc, char *argv[]) {
  char *test = "american idiot Green Daty";
  // char *test = "america idiot";
  splitToArr(test);
  return 0;
}
