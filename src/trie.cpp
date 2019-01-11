#include "trie.h"

struct TrieNode *new_node() {
    auto *node = new TrieNode;

    for (auto &i : node->children)
        i = nullptr;
    node->leaf = false;
    return node;
}

Trie::Trie() {
    root = new_node();
}

void Trie::insert(std::string str) {
    auto *node = root;

    for (auto &i : str) {
        auto index = i - 'a';

        if (index < 0 || index > DOMAIN_SIZE) continue;

        if (!node->children[index])
            node->children[index] = new_node();
        node = node->children[index];
    }

    node->leaf = true;
}

bool Trie::search(std::string str) {
    auto *node = root;

    for (auto &i : str) {
        auto index = i - 'a';

        if (!node->children[index]) return false;
        node = node->children[index];
    }

    return (node != nullptr && node->leaf);
}

void traverse(TrieNode *node, const std::string &str, std::vector<std::string> *content) {
    if (node->leaf) content->push_back(str);
    for (int i = 0; i < DOMAIN_SIZE; i++) {
        auto child = node->children[i];
        if (child != nullptr)
            traverse(child, str + static_cast<char>(i + 'a'), content);
    }
}

std::vector<std::string> *Trie::all() {
    auto result = new std::vector<std::string>();
    traverse(root, "", result);
    return result;
}

std::vector<std::string> *Trie::all_with_prefix(std::string str) {
    auto result = new std::vector<std::string>();
    auto *node = root;

    for (auto &i : str) {
        auto index = i - 'a';

        if (!node->children[index]) return result;
        node = node->children[index];
    }

    traverse(node, str, result);
    return result;
}
