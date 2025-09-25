#include <stdio.h>
#include <stdlib.h>


void shape() {
  const char kira[] = "Kira Yoshikage";
  int age = 23;
  // similar to go's fmt.Printf()
  // fprintf() => fmt.Fprintf()
  printf("My name is %s , and I am %d years old.\nMy goal is to live a simple and free life\n", kira, age);
  printf("The mundane life is the ideal lige for me and nothing more than a fantasy I wish to live\n");


  char charName[30];
  printf("Enter characters name ->: ");
  // scanf(formatter, memory_address)
  scanf("%s", charName);

  printf("this user, doddlebot, chose a character of -> %s\n", charName);
  printf("strings are stored in contiguous memory blocks\n");
  printf("since c has no default string type, it just does that exactly, and i assume, all langauges??\n");
  printf("Also, the reason persay, you print out the size of a string persay , 'balls', you'd get a length of 6\n");
  char balls[] = "balls";
  printf("%lu\n",sizeof(balls));
  printf("thats because, since these characters are laid in a contiguous memory, there needs to be an end to it\n");
  // printf("an escape sequence is provided :\\, which is a null byte character, represented as: \0   \n");
}

void userInput() {
  char input[30];
  // https://man7.org/linux/man-pages/man3/fgets.3p.html
  printf("Enter full show: \n");
  // fgets(char *store[], n bytes, src)
  fgets(input, 30, stdin);
  printf("input read from stdin -> %s", input);
}
int main() {
  userInput();
  return 0;
}
