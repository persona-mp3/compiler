#include <cstddef>
#include <iostream>
#include <map>
#include <set>
#include <vector>
const char ENDLN = ';';
const char EXP = '^';
const char OPEN_QUOTE = '"';
const char CLOSING_QUOTE = '"';
const std::string OR = "||";
const std::string INT = "int";
const std::string STRING = "string";
const std::string BOOL = "bool";
const std::string ARR = "arr";

const std::set<std::string> RESERVERD = {OR, INT, STRING, BOOL, ARR};
const std::set<char> PUNCTUATIONS = {OPEN_QUOTE, CLOSING_QUOTE};
const std::set<char> OPERATIONS = {ENDLN, EXP};
const std::set<std::string> TYPE_SET = {STRING, INT, BOOL, ARR};

// so instead of a set, we can just create a map that tells them where they're
// from
std::map<std::string, int> TYPES;

std::vector<std::string> splint(std::string s) {
  char delimiter = ' ';
  std::vector<std::string> result;
  std::string word = "";
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == delimiter && word != "") {
      result.push_back(word);
      word = "";
    } else if (s[i] == ENDLN) {
      break;
    } else {
      word += s[i];
    }
  }

  if (!word.empty()) {
    result.push_back(word);
  }

  result.push_back(";");
  return result;
}
void tokenIterator(std::string &stream) {
  std::vector<std::string> tokens = splint(stream);
  for (size_t i = 0; i < tokens.size(); i++) {
    std::cout << "[" << tokens[i] << "]\n";
  }
}

int main(int argc, char *argv[]) {
  std::string operation{};
  std::cout << "Enter operation:\n";

  // so this stops at the first whitespace, but getline gets the line
  std::getline(std::cin, operation);

  tokenIterator(operation);

  return 0;
}
