#include <iostream>
#include "trie.h"

int main() {
    auto tree = Trie();

    tree.insert("hello");

    auto words = *tree.all();

    std::string word = "hello";
    auto splits = std::vector<std::pair<std::string, std::string>>();
    auto deletes = std::vector<std::string>();
    auto transposes = std::vector<std::string>();
    auto replaces = std::vector<std::string>();
    auto inserts = std::vector<std::string>();

    for (int i = 0; i < word.length() + 1; i++) {
        splits.push_back(*new std::pair<std::string, std::string>(
                word.substr(0, i),
                word.substr(i)
        ));
    }

    for (auto &i : splits) {
        if (i.second.length() > 0) {
            deletes.push_back(i.first + i.second.substr(1));

            if (i.second.length() > 1) {
                transposes.push_back(
                        i.first + i.second[1] + i.second[0] + i.second.substr(2)
                );
            }
        }

        for (int c = 0; c < DOMAIN_SIZE; c++) {
            if (i.second.length() > 0)
                replaces.push_back(i.first + static_cast<char>(c + 'a') + i.second.substr(1));
            inserts.push_back(i.first + static_cast<char>(c + 'a') + i.second);
        }
    }


    for (auto &i : inserts) {
        std::cout << i << std::endl;
    }
    return 0;
}