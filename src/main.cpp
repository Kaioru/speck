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
    auto begin = clock();
    auto filet = Filet(&in);

    for (auto &row: filet) tree.insert(row[0]);
    auto end = clock();
    std::cout << "Loaded "
              << tree.all()->size()
              << " words in "
              << double(end - begin) / CLOCKS_PER_SEC << "s"
              << std::endl;

    while (true) {
        std::cout << "=== speck menu ===" << std::endl;
        std::cout << "1. check word" << std::endl;
        std::cout << "2. spell check file" << std::endl;
        std::cout << "3. add to dictionary" << std::endl;
        std::cout << "4. save dictionary" << std::endl;
        std::cout << "5. words with prefix" << std::endl;
        std::cout << "10. quit" << std::endl;

        int option;
        std::cin >> option;

        switch (option) {
            case 1: {
                std::string word;
                std::cout << "what word?" << std::endl;
                std::cin >> word;
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);

                if (!speck.validate(word)) {
                    auto suggestions = speck.suggestions(word);

                    if (suggestions.empty()) {
                        std::cout << word << " " << "has an invalid spelling." << std::endl;
                        break;
                    }

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
            case 2: {
                struct SpellingError {
                    int row;
                    int col;
                    std::string original;
                    std::string suggestion;
                };

                auto errors = *new std::vector<SpellingError>();
                std::string path;

                std::cout << "which file?" << std::endl;
                std::cin >> path;

                std::ifstream in(path);
                if (!in) {
                    std::cout << "Failed to load" << " " << path << std::endl;
                    break;
                }
                auto begin = clock();
                auto count = 0;
                auto filet = Filet(&in, " ");

                auto rowCount = 0;
                for (auto &row: filet) {
                    auto colCount = 0;

                    rowCount++;
                    for (auto &col: row) {
                        count++;
                        colCount++;
                        if (!speck.validate(col))
                            errors.push_back({rowCount, colCount, col, speck.correct(col)});
                    }
                }

                auto end = clock();
                std::cout << "Checked "
                          << count
                          << " words in "
                          << double(end - begin) / CLOCKS_PER_SEC
                          << "s" << std::endl;
                std::cout << "Found "
                          << errors.size()
                          << " spelling errors"
                          << std::endl;
                std::cout << std::endl;

                for (auto &error : errors) {
                    std::cout << error.original
                              << " at "
                              << error.row << ":" << error.col
                              << " (did you mean "
                              << error.suggestion
                              << "?)"
                              << std::endl;
                }
                break;
            }
            case 3: {
                std::string word;
                std::cout << "what word?" << std::endl;
                std::cin >> word;
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                
                if (tree.search(word)) {
                    std::cout << word << " " << "is already in the dictionary." << std::endl;
                    break;
                }

                tree.insert(word);
                std::cout << word << " " << "has been added to the dictionary." << std::endl;
                break;
            }
                
            case 4: {
                std::string path;

                std::cout << "which file?" << std::endl;
                std::cin >> path;

                std::ofstream out(path);
                Filet filet = Filet();
                auto begin = clock();
                auto words = *tree.all();

                for (auto &word : words)
                    filet.push_back({word});

                filet.write(&out);

                auto end = clock();
                std::cout << "Wrote "
                          << words.size()
                          << " words in "
                          << double(end - begin) / CLOCKS_PER_SEC
                          << "s" << std::endl;
                break;
            }
            case 5: {
                std::string word;
                std::cout << "what prefix?" << std::endl;
                std::cin >> word;
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                auto results = tree.all_with_prefix(word);

                std::cout << "found " << results->size() << " results with the prefix " << word << ":" << std::endl;
                for (auto &i: *results)
                    std::cout << i << std::endl;
                break;
            }
            case 10:
                return 0;
            default:
                std::cout << "Unknown option!" << std::endl;
                break;
        }
        std::cout << std::endl;
    }
}
