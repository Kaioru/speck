#pragma once

#include "iostream"
#include "trie.h"

class Speck {
private:
    Trie *trie;
public:
    Speck(Trie *t);

    bool validate(std::string str);
    std::string correct(std::string str);
    std::vector<std::string> candidates(std::string str);
    std::vector<std::string> combinations(std::string str);
};