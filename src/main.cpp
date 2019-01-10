#include <iostream>
#include <fstream>
#include "trie.h"
#include "speck.h"
#include "filet.h"

int main() {
    auto tree = Trie();
    auto speck = Speck(&tree);

    std::ifstream in("dictionary.csv");
    if (!in) std::cout << "Failed to load dictionary.csv" << std::endl;
    auto filet = Filet(&in);

    for (auto &row: filet) tree.insert(row[0]);

    std::cout << speck.correct("henlo") << std::endl;
    return 0;
}