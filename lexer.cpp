/*
 * So we need to be able to get a stream of text
 * and identify what each set of words/character means.
 * For example. int n = 32 * 3
 * The token should be able to say
 *  - int -> reserverd/type
 *  - n -> variable/identifier
 *  - = -> operation/assignment
 *  - 32 -> character/number
 *  - * -> operation
 *  - 3 -> character/number
 *
 * So is thinking about how to structure the code wrong right now??
 * Well not really, but lets see how we might do this.
 *
 * ------------
 *  - First we need to read a stream of characters, for now, we can use std::cin
 *  - Secondly, iterate through the stream of characters and identify them
 * against the table
 *  - For now, we can just print their position
 * */

#include <iostream>
#include <set>
#include <vector>
const std::string OR = "||";
const std::string INT = "int";
const std::string STRING = "string";
const std::string BOOL = "bool";
const std::string ARR = "arr";
const char ENDLN = ';';
const char EXP = '^';

const std::set<std::string> RESERVERD = {OR, INT, STRING, BOOL, ARR};
const std::set<char> OPERATIONS = {ENDLN, EXP};

std::vector<std::string> splint(std::string s) {
  char delimiter = ' ';
  std::vector<std::string> result;
  std::string word = "";
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == delimiter) {
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

  return result;
}
void tokenIterator(std::string &stream) {
  std::vector<std::string> res = splint(stream);
  for (int i = 0; i < res.size(); i++) {
    if (RESERVERD.contains(res[i])) {
      std::cout << "Found reserved -> " << res[i] << " in resreved\n";
    } else {
      std::cout << "Unidentified token ->" << res[i] << '\n';
    }
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
