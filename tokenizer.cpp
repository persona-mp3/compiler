#include <cctype>
#include <iostream>
#include <pthread.h>
#include <set>
#include <vector>

const char DELIMITER = ' ';
const char END_TOKEN = ';';
const std::set<std::string> TYPES = {"int", "string", "bool", "float"};
const std::set<std::string> RESERVERD = {"if", "else", "fi", "elseif",
                                         "switch"};
const std::set<std::string> SYMBOLS = {";", "=", ":", "(", ")",
                                       "[", "]", "{", "}"};
const std::set<char> QUOTES = {'"'};
const std::set<std::string> IDENTIFIERS = {"const", "var", "temp"};
const std::set<std::string> OPERATIONS = {"==", "!=", "+", "**", "%", "-",
                                          "<",  ">",  "!", "||", "&&"};

struct Token {
  std::string type;
  std::string value;
};

// now time to try and decipher the kind of characters entered
Token tokenMatcher(std::string tok) {
  if (TYPES.find(tok) != TYPES.end()) {
    return {"TYPE", tok};
  } else if (SYMBOLS.find(tok) != SYMBOLS.end()) {
    return {"SYMBOL", tok};
  } else if (IDENTIFIERS.find(tok) != IDENTIFIERS.end()) {
    return {"IDENTIFIER", tok};
  } else if (OPERATIONS.find(tok) != OPERATIONS.end()) {
    return {"OPERATION", tok};
  } else if (RESERVERD.find(tok) != RESERVERD.end()) {
    return {"RESERVERD", tok};
  } else {
    return {"userDef", tok};
  }
}

std::vector<Token> split(std::string &s) {
  std::vector<Token> tokens;
  std::string token = "";

  for (int i = 0; i < s.length(); i++) {
    if (s[i] == DELIMITER) {
      tokens.push_back(tokenMatcher(token));
      token = "";
    } else if (s[i] == END_TOKEN) {
      break;
    } else if (s[i] == '"') {
      if (!token.empty()) {
        tokens.push_back(tokenMatcher(token));
        token = "";
      }

      tokens.push_back({"QUOTES", std::string(1, s[i])});
    } else {
      token += s[i];
    }
  }

  if (!token.empty()) {
    tokens.push_back(tokenMatcher(token));
    token = "";
  }

  tokens.push_back(tokenMatcher(";"));
  return tokens;
}

struct IntStatus {
  bool ok;
  int code;
  int value;
};

struct StringStatus {
  bool ok;
  int code;
  std::string value;
};

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

StringStatus stringParser(std::vector<Token> &tokens) {
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
// splits stream of text into an array of characters/words, delimted by a space
bool parse(std::vector<Token> &tokens) {
  if (tokens[0].type == "TYPE" && tokens[1].type == "userDef" &&
      tokens[2].type == "SYMBOL" &&
      (tokens[3].type == "QUOTES" || tokens[3].type == "userDef")) {

    if (tokens[0].value == "int") {
      std::cout << "type::int\n";
      IntStatus status = intParser(tokens[3].value);
      if (!status.ok) {
        std::cout << "Invalid syntax\n";
        return status.ok;
      }

      std::cout << "Integer declared -> " << status.value << " \n";
    } else if (tokens[0].value == "string") {
      std::cout << "type::string\n";
      // copying original vector but starting from the 3rd token instead
      auto slice = std::vector<Token>(tokens.begin() + 3, tokens.end());
      StringStatus status = stringParser(slice);
      if (!status.ok) {
        return status.ok;
      }

      auto result = status.value;
      std::cout << "result -> " << result << "\n";
    }
    return true;
  }

  std::cout << "Invalid syntax\n";
  return false;
}

int main(int argc, char *argv[]) {
  std::string userInput;
  std::cout << "Tokenizer: \n";
  std::getline(std::cin, userInput);

  auto tokens = split(userInput);
  parse(tokens);
  return 0;
}
