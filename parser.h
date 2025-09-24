#include <iostream>
#ifndef PARSER_H
#define PARSER_H
// Parser status for int-type declaration
struct IntStatus {
  bool ok;
  int code;
  int value;
};

// Parser status for string-type declaration
struct StringStatus {
  bool ok;
  int code;
  std::string value;
};

IntStatus intParser(std::string &s);
StringStatus stringParser(std::string &s);

#endif
