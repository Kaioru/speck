#include <iostream>
#include "trie.h"

int main() {
    auto tree = Trie();

    tree.insert("hello");
    tree.insert("hello");
    tree.insert("my");
    tree.insert("name");
    tree.insert("is");
    tree.insert("dibo");

    for (auto &i : *tree.all())
        std::cout << i << std::endl;
    return 0;
}