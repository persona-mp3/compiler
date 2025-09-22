#include <iostream>
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

// splits stream of text into an array of characters/words, delimted by a space
std::vector<Token> split(std::string &s) {
  std::vector<Token> tokens;
  std::string token = "";

  for (int i = 0; i < s.length(); i++) {
    if (s[i] == DELIMITER && token != "") {
      tokens.push_back(tokenMatcher(token));
      token = "";
    } else if (s[i] == END_TOKEN) {
      break;
    } else if (QUOTES.find(s[i]) != QUOTES.end()) {
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
  std::cout << "Tokens extracted -> :\n";
  return tokens;
}

bool parse(std::vector<Token> &tokens) {
  if (tokens[0].type == "TYPE" && tokens[1].type == "userDef" &&
      tokens[2].type == "SYMBOL" &&
      (tokens[3].type == "QUOTES" || tokens[3].type == "userDef")) {
    std::cout << "Valid syntax\n";
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
  bool validSyntax = parse(tokens);
  for (size_t i = 0; i < tokens.size(); i++) {
    std::cout << "[" << tokens[i].type << " -> " << tokens[i].value << "]\n";
  }
  return 0;
}
