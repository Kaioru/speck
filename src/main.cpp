#include <iostream>
#include <fstream>
#include <sstream>
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

    // TODO: a nice cli menu
    auto suggestions = speck.suggestions("henlo");

    std::cout << "Did you mean: " << suggestions[0] << "?";
    if (suggestions.size() > 1) {
        std::vector<std::string> others(suggestions.begin() + 1,
                                        suggestions.begin() + (suggestions.size() > 4
                                                               ? 4
                                                               : 4 - suggestions.size()));

        auto ss = std::stringstream();

        ss << " Or maybe: ";
        for (int i = 0; i < others.size(); i++) {
            ss << others[i];
            if (i < others.size() - 2) ss << ", ";
            else if (i == others.size() - 2) ss << " or ";
            else ss << "?";
        }

        std::cout << ss.str();
    }
    return 0;
}