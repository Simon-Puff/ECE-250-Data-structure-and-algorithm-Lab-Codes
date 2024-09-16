#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <vector>
#include <iostream>

struct Node {
    std::string word;
    unsigned int token;
    Node* next;

    Node();

    // to do
    //~Node();
};

class HashTable{
    private:
        void resize();
    public:
        Node** table;
        unsigned int capacity;
        unsigned int size;
        HashTable(unsigned int capacity_para);
        ~HashTable();
        unsigned hash_function(const std::string& str, unsigned int size);
        bool insert(const std::string& word, unsigned int token);
        int get_token(const std::string& word); 
};

class TwoWayDic{
    private:
        std::vector<std::string> tokensToWords;
        HashTable* wordsToTokens;

        bool load_help_function(std::string filename);
    public:
        TwoWayDic(unsigned int size);
        ~TwoWayDic();
        bool insert(std::string& str);
        void load(std::string file_name);
        void tok(std::string& word);
        void ret(unsigned int token);
        void tok_all(std::string& word_array);
        void ret_all(std::string& token_array);
        void print(unsigned int k);
        void exit();
        unsigned int get_size();
};

#endif