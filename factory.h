#ifndef FACTORY_H_
#define FACTORY_H_

typedef struct {
  int kind;
  char val[100];
} Token;

Token Factory(char *str);
#endif
