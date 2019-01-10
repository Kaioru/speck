#include <iostream>
#include "trie.h"
#include "speck.h"

int main() {
    auto tree = Trie();
    auto speck = Speck(&tree);

    tree.insert("hello");
    std::cout << speck.correct("henlo") << std::endl;
    return 0;
}