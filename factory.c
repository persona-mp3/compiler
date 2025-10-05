#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE_TOKEN 0
#define ASSIGNMENT_TOKEN 1
#define DELIMITER_TOKEN 2
#define VALUE_TOKEN 3
#define IDENTIFIER_TOKEN 4
#define UNIDENTIED_TOKEN -1

const char INT_LIT[] = "int";
const char STR_LIT[] = "string";
const char BOOL_LIT[] = "bool";
const char ASSIGNMENT_LIT[] = "=";
const char DELIMETER_LIT[] = ";";
const char FN_LIT[] = "fn";

typedef struct {
  int kind;
  char val[];
} Token;

bool typeToken(char *str[], Token *t) {
  if (strcmp(*str, INT_LIT) == 0) {
    printf("t is int-type\n");
    t->kind = 0;
    strcpy(t->val, *str);
  } else if (strcmp(*str, STR_LIT) == 0) {
    printf("t is str-type\n");
    t->kind = 0;
    strcpy(t->val, *str);
  } else if (strcmp(*str, BOOL_LIT) == 0) {
    printf("t is %s\n", BOOL_LIT);
    t->kind = 0;
    strcpy(t->val, *str);
  } else {
    printf("[?] unidentified token literal -> %s\n", *str);
    return false;
  }

  return true;
}

bool assignToken(char *str[], Token *t) {
  if (strcmp(*str, ASSIGNMENT_LIT) == 0) {
    printf("assignment token found -> %s", *str);
    t->kind = ASSIGNMENT_TOKEN;
    strcpy(t->val, *str);
    return true;
  }
  printf("[?] unidentified token literal, assignmentToken failed -> %s\n",
         *str);
  return false;
}

void delimiterToken(char *str[], Token *t) {
  if (strcmp(*str, DELIMETER_LIT) == 0) {
    printf("delimiter token found -> %s", *str);
    t->kind = DELIMITER_TOKEN;
    strcpy(t->val, *str);
    return;
  }
  printf("[?] unidentified token literal, delimeterToken failed -> %s\n", *str);
  t->kind = UNIDENTIED_TOKEN;
  return;
}

Token Factory(char *str[]) {
  Token token;

  while (true) {
    if (typeToken(str, &token)) {
      break;
    } else if (assignToken(str, &token)) {
      break;
    } else {
      delimiterToken(str, &token);
    };

    break;
  }
  return token;
}

/*
 * So we can have somewhat of a factory patttern????
 * We can accept an incoming stream of text, and run them through a series
 * of dedicated tokenizers
 * string lexer = "My tokenizer";
 * we can have a flow like this:
 * typeToken -> varToken -> assignToken -> literalToken -> delimiterToken;
 * And then what ever this factory spits out, we can then use a parser to check
 * whats correct if typeToken can't figure it out, it sends it down the chain
 * until delimiter
 *
 * ==================
 *    FACTORY
 * ==================
 * bool typeToken(char *str[], Token token){
 * 		if str is unidentified, return false, and don't modify the token
 * }
 * bool varToken(char *str[], Token token){
 * 		if str is unidentified, return false, and don't modify the token
 * }
 * bool assignToken(char *str[], Token token){
 * 		if str is unidentified, return false, and don't modify the token
 * }
 * bool literalToken(char *str[], Token token){
 * 		if str is unidentified, return false, and don't modify the token
 * }
 * bool delimiterToken(char *str[], Token token){
 * 		if str is unidentified, return a token of undefined
 * }
 *
 * So the factory will return the final token
 * If at anypoint any of these tokenizers return true, we can break
 */
