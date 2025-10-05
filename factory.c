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
  char val[100];
} Token;

bool typeToken(char *str[], Token *t) {
  if (strcmp(*str, INT_LIT) == 0) {
    t->kind = 0;
    strcpy(t->val, *str);
  } else if (strcmp(*str, STR_LIT) == 0) {
    t->kind = 0;
    strcpy(t->val, *str);
  } else if (strcmp(*str, BOOL_LIT) == 0) {
    t->kind = 0;
    strcpy(t->val, *str);
  } else {
    return false;
  }

  return true;
}

bool assignToken(char *str[], Token *t) {
  if (strcmp(*str, ASSIGNMENT_LIT) == 0) {
    t->kind = ASSIGNMENT_TOKEN;
    strcpy(t->val, *str);
    return true;
  }
  return false;
}

void delimiterToken(char *str[], Token *t) {
  if (strcmp(*str, DELIMETER_LIT) == 0) {
    t->kind = DELIMITER_TOKEN;
    strcpy(t->val, *str);
    return;
  }
  printf("[?] delimeterToken failed for -> %s\n", *str);
  t->kind = UNIDENTIED_TOKEN;
	strcpy(t->val, "UID");
  return;
}

Token Factory(char *str) {
  Token token;
	if (typeToken(&str, &token)) return token;
	if (assignToken(&str, &token)) return token;
	delimiterToken(&str, &token);
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
