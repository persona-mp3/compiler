#include <stdio.h>
#include <strings.h>

void loopStr(char *s);
void strArray();
void goSplit();
void crashOut();

int main() {
  // size of array is known at comp time;
  int n[] = {2, 4, 6, 3};
  // a string is alwasy represent as a pointer to the first character in
  // char-arr
  char *s = "ragenat";

  char *string = "stringer as pointer";

  crashOut();
  return 0;
}

void loopStr(char *s) {
  size_t s_len = strlen(s);
  printf("size of string -> %lu, size of char -> %lu\n", s_len, sizeof s[0]);
  for (int i = 0; i < s_len; i++)
    return;
}

void strArray() {
  // [s0, s1, s2]
  // [[s, h, a, r, e, d, \0], [], []]
  // s[0[3]] = r;
  char str_arr[][100] = {"Shared", "Stationery", "pOINT", "looked",
                         "management"};
  char a[1000] = "";
  int arr_size = sizeof str_arr / sizeof str_arr[0];
  printf("size of str_array -> %d\n", arr_size);
  for (int i = 0; i < arr_size; i++) {
    printf("%s, %lu\n", str_arr[i], sizeof(str_arr[i]));
  }
  return;
}

// For now lets just take a sequence of strings
// return an array of strings
void goSplit() {
  // res += stdin[i];
  // how will this not fail?? char vs char??
  // or perhaps im getting it wrong
  // the memory is probs stationed like this
  // *res --> [\0] | and to append a character it'd look like this
  // *res -->[\0, 'f']  or [\0, 102]. But since thats a null byte terminator
  // c would not border to  read after it??, so i could just replace the
  // first one *res --> ['f', \0] *res --> ['f', 'r', \0]
  //
  //
  // why??
	// So apparently, string literals cannot be modified in c, 
	// char *why = "\0", thats deadlocked
	//
  // printf("sizeof res b4 -> %lu", sizeof *res);
  char *stdin = "from;stdin";
  char *res = "\0";
  printf("size of res %lu -> ", sizeof(*res));
  int pos = 0;
}

void crashOut() {
  char *test = "linkin;Park";
  char res[100] = "\0";
  int res_len = sizeof res;
  int pos = 0;
  for (int i = 0; i < res_len; i++) {
    if (test[i] == ';') {
      continue;
    }
    res[pos] = test[i];
    pos++;
  }

  printf("final string?? -> %s\n", res);
}
