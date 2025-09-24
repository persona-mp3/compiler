#include "parser.h"


IntStatus intParser(std::string &s) {
  std::string parsedNumber;
  for (int i = 0; i < s.length(); i++) {
    if (!std::isdigit(s[i]) && s[i] != '.') {
      return {false, 1};
    }

    parsedNumber += s[i];
  }
  return {true, 0, std::stoi(parsedNumber)};
}

StringStatus stringParser(std::vector<T> &tokens) {
  std::string parsedStr;

  const char *opening_quote = tokens[0].value.c_str();
  const char *closing_quote = tokens[tokens.size() - 2].value.c_str();
  if (QUOTES.find(*opening_quote) == QUOTES.end() &&
      QUOTES.find(*closing_quote) == QUOTES.end()) {
    std::cout << "Invalid syntax, did you forget to insert opening and closing "
                 "quotes?\n";
    return {false, 1, ""};
  }

  for (size_t i = 0; i < tokens.size() - 2; i++) {
    parsedStr += tokens[i].value;
    if (i != 0 || tokens[i].value != std::string(1, '"')) {
      parsedStr.append(1, ' ');
    }
  }

  parsedStr.append(1, *tokens[tokens.size() - 2].value.c_str());
  parsedStr.append(1, *tokens[tokens.size() - 1].value.c_str());

  return {true, 0, parsedStr};
}
