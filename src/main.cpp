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

    while (true) {
        std::cout << "=== speck menu ===" << std::endl;
        std::cout << "1. check word" << std::endl;
        std::cout << "2. spell check file (WIP)" << std::endl;
        std::cout << "3. add to dictionary" << std::endl;
        std::cout << "4. save dictionary (WIP)" << std::endl;
        std::cout << "5. words with prefix" << std::endl;
        std::cout << "10. quit" << std::endl;

        int option;
        std::cin >> option;

        switch (option) {
            case 1: {
                std::string word;
                std::cout << "what word?" << std::endl;
                std::cin >> word;

                if (!speck.validate(word)) {
                    auto suggestions = speck.suggestions(word);

                    std::cout << "did you mean: " << suggestions[0] << "?";
                    if (suggestions.size() > 1) {
                        std::vector<std::string> others(suggestions.begin() + 1,
                                                        suggestions.begin() + (suggestions.size() > 4
                                                                               ? 4
                                                                               : 4 - suggestions.size()));

                        auto ss = std::stringstream();

                        ss << " " << "or maybe: ";
                        for (int i = 0; i < others.size(); i++) {
                            ss << others[i];
                            if (i < others.size() - 2) ss << ", ";
                            else if (i == others.size() - 2) ss << " or ";
                            else ss << "?";
                        }

                        std::cout << ss.str() << std::endl;
                    }
                } else std::cout << word << " " << "has a valid spelling." << std::endl;
                break;
            }
            case 3: {
                std::string word;
                std::cout << "what word?" << std::endl;
                std::cin >> word;

                if (!tree.search(word)) {
                    std::cout << word << " " << "is already in the dictionary." << std::endl;
                    break;
                }

                tree.insert(word);
                std::cout << word << " " << "has been added to the dictionary." << std::endl;
                break;
            }
            case 5: {
                std::string word;
                std::cout << "what prefix?" << std::endl;
                std::cin >> word;
                auto results = tree.all_with_prefix(word);

                std::cout << "found " << results->size() << " results with the prefix " << word << ":" << std::endl;
                for (auto &i: *results)
                    std::cout << i << std::endl;
                break;
            }
            default:
                std::cout << "Unknown option!" << std::endl;
                return 0;
        }
        std::cout << std::endl;
    }
}
