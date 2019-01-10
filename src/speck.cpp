#include <unordered_map>
#include "speck.h"

Speck::Speck(Trie *t) {
    trie = t;
}

bool Speck::validate(std::string str) {
    return trie->search(str);
}

std::string Speck::correct(std::string str) {
    if (trie->search(str)) return str;
    return suggestions(str)[0];
}

std::vector<std::string> Speck::suggestions(std::string str) {
    auto c = candidates(str);
    auto map = std::unordered_map<std::string, size_t>();

    for (std::string i : c) map[i]++;

    std::sort(
            c.begin(),
            c.end(),
            [&map](std::string const &a, std::string const &b) {
                if (a == b) return false;
                if (map[a] > map[b]) return true;
                else if (map[a] < map[b]) return false;
                return a < b;
            });
    c.erase(unique(c.begin(), c.end()), c.end());
    return c;
}

std::vector<std::string> Speck::candidates(std::string str) {
    auto result = *new std::vector<std::string>();
    auto combos = *new std::vector<std::string>();

    if (trie->search(str)) result.push_back(str);

    for (auto &c : combinations(str)) {
        for (auto &c2 : combinations(c))
            combos.push_back(c2);
        combos.push_back(c);
    }

    for (auto &c : combos)
        if (trie->search(c)) result.push_back(c);
    return result;
}

std::vector<std::string> Speck::combinations(std::string str) {
    auto result = *new std::vector<std::string>();
    auto splits = std::vector<std::pair<std::string, std::string>>();

    for (int i = 0; i < str.length() + 1; i++) {
        splits.push_back(*new std::pair<std::string, std::string>(
                str.substr(0, i),
                str.substr(i)
        ));
    }

    for (auto &i : splits) {
        if (i.second.length() > 0) {
            result.push_back(i.first + i.second.substr(1));

            if (i.second.length() > 1) {
                result.push_back(
                        i.first + i.second[1] + i.second[0] + i.second.substr(2)
                );
            }
        }

        for (int c = 0; c < DOMAIN_SIZE; c++) {
            if (i.second.length() > 0)
                result.push_back(i.first + static_cast<char>(c + 'a') + i.second.substr(1));
            result.push_back(i.first + static_cast<char>(c + 'a') + i.second);
        }
    }
    return result;
}
