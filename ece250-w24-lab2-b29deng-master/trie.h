#ifndef TRIE_H
#define TRIE_H
#include <iostream>
// define your classes here...
class trie
{
    private:
        trie *Children[26];
        bool isEndOfWord;
        int word_count;
        void post_order_destructor_help(trie* root);
        int C_I_LUT(char character);
        char I_C_LUT(int i);
        void delete_node(trie *curr);
        void catch_error();
        int count_child(trie *curr);
        int count_child_word(trie *curr);
        bool eraseHelper(trie* node, const std::string& word, int depth, int wordLength);
    public:
        trie();
        ~trie();
        void load(trie *root);
        void insert(std::string& word, trie *root);
        void insert_no_output(std::string& word, trie *root);
        int prefix_count(std::string& word, trie *root);
        bool isEmpty() const;
        bool erase(const std::string& word);
        void print(trie *root, std::string prev);
        void spellcheck(const std::string &word, std::string::size_type index, trie *root);
        void empty(trie *root);
        void clear();
        void size();
        void exit();
    };
#endif