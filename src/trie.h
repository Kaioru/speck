#pragma once

#include <iostream>
#include <vector>
#include <string>

const int DOMAIN_SIZE = 26;

struct TrieNode
{
    struct TrieNode *children[DOMAIN_SIZE];
    bool leaf;
};

class Trie
{
  private:
    TrieNode *root;

  public:
    Trie();

    void insert(std::string str);
    bool search(std::string str);
    std::vector<std::string> * all();
    std::vector<std::string> * all_with_prefix(std::string str);
};