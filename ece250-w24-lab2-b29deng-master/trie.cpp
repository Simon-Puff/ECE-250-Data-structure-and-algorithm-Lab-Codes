#include "trie.h"
#include <iostream>
#include <fstream>

// implement classes' member functions here...
// Initial test push
trie::trie(){
    //std::cout << "hello" << std::endl;
    isEndOfWord = false;
    word_count = 0;
    for(int i = 0; i <= 25; i++){
        Children[i] = nullptr;
    }
}

trie::~trie(){
    exit();
}
void trie::insert(std::string& word, trie *root){
    trie* curr = root;
    for(int index = 0; index < word.length(); index++){
        int i = C_I_LUT(word[index]);
        if(curr->Children[i] != nullptr){
            // nothing
        }else{
            curr->Children[i] = new trie;
        }
    curr = curr->Children[i];
    }
    if(curr->isEndOfWord == true){
        std::cout << "failure" << std::endl;
    }else{
        curr->isEndOfWord = true;
        word_count ++;
        std::cout << "success" << std::endl;
    }
}
void trie::insert_no_output(std::string& word, trie *root){
    trie* curr = root;
    for(int index = 0; index < word.length(); index++){
        int i = C_I_LUT(word[index]);
        if(curr->Children[i] != nullptr){
            // nothing
        }else{
            curr->Children[i] = new trie;
        }
    curr = curr->Children[i];
    }
    if(curr->isEndOfWord == true){
        //std::cout << "failure" << std::endl;
    }else{
        curr->isEndOfWord = true;
        word_count ++;
        //std::cout << "success" << std::endl;
    }
}
int trie::prefix_count(std::string& word, trie *root){
    trie* curr = root;
    for(std::string::size_type index = 0; index < word.size(); index++){
        int i = C_I_LUT(word[index]);
        if(curr->Children[i] != nullptr){
            curr = curr->Children[i];
        }else{
            return -1;
        }
    }
    return count_child_word(curr);
}
bool trie::erase(const std::string& word){
    return eraseHelper(this, word, 0, word.size());
}
bool trie::eraseHelper(trie* node, const std::string& word, int depth, int wordLength) {
    if (node == nullptr) {
        return false; // Base case: Node does not exist.
    }

    if (depth == word.size() || (depth == word.size() - 1 && C_I_LUT(word[depth]) == -1)) {
        if (!node->isEndOfWord) {
            std::cout << "failure" << std::endl; // Word isn't in the Trie.
            return false;
        }
        
        node->isEndOfWord = false; // Mark this node as not the end of a word anymore.
        
        if (node->isEmpty()) {
            if (depth == wordLength) { // Check if at the base level of recursion.
                std::cout << "success" << std::endl; // Only print success at the base level.
            }
            return true; // The node can potentially be deleted.
        } else {
            return false; // The node is part of other words.
        }
    }

    int index = depth < word.size() ? C_I_LUT(word[depth]) : -1;
    if (index == -1 || node->Children[index] == nullptr) {
        std::cout << "failure" << std::endl; // Invalid character path or child does not exist.
        return false;
    }

    bool shouldDeleteChild = eraseHelper(node->Children[index], word, depth + 1, wordLength);
    if (shouldDeleteChild) {
        delete node->Children[index];
        node->Children[index] = nullptr;
        
        return node->isEmpty() && !node->isEndOfWord; // Return if the current node is now redundant.
    }

    return false; // If we didn't delete this node, it's not redundant.
}
 bool trie::isEmpty() const {
        for (int i = 0; i < 26; ++i) {
            if (this->Children[i] != nullptr) {
                return false;
            }
        }
        return true;
    }
void trie::print(trie *root, std::string word) {
    // Base case: If root is null, return
    if (root == nullptr){
        return;
    }
    if (root->isEndOfWord) {
        std::cout << word << " "; // Print the word followed by a space
    }

    for (int i = 0; i <= 25; ++i) {
        if (root->Children[i]) {
            // Append current character to 'word' and recurse
            print(root->Children[i], word + I_C_LUT(i));
        }
    }
}

void trie::spellcheck(const std::string &word, std::string::size_type index, trie *root){
    if(root->Children[C_I_LUT(word[index])] != nullptr && index < word.length() - 1){
        spellcheck(word, index +1, root->Children[C_I_LUT(word[index])]);
    }else{
        if(root->Children[C_I_LUT(word[index])] == nullptr && index == 0){
            std::cout << std::endl;
        }else if(root->Children[C_I_LUT(word[index])] == nullptr && index != 0){
            std::string prev;
            for(int i = 0; i < index; i++){
                prev += word[i];
            }
            print(root, prev);
            std::cout << std::endl;
        }
        else if(index == word.size() - 1 && this->Children[C_I_LUT(word[index])]->isEndOfWord == true){
            std::cout << "correct" << std::endl;
        }else if(index == word.size() - 1 && this->Children[C_I_LUT(word[index])]->isEndOfWord == false){
            std::string prev;
            for(int i = 0; i <= index; i++){
                prev += word[i];
            }
            print(root->Children[C_I_LUT(word[index])], prev);
            std::cout << std::endl;
        }
    }
}
void trie::empty(trie *root){
    if(count_child(root) != 0){
        std::cout << "empty 0" << std::endl;
    }else if(count_child(root) == 0){
        std::cout << "empty 1" << std::endl;
    }
}
void trie::clear(){
    //
    for(int i = 0; i <= 25; i++){
        post_order_destructor_help(this->Children[i]);
    }
    this->word_count = 0;
    std::cout << "success" << std::endl;
}
void trie::size(){
    std::cout << "number of words is " + std::to_string(word_count) << std::endl;
}
void trie::exit(){
    for (int i = 0; i < 26; ++i) {
        if (Children[i] != nullptr) {
            delete Children[i]; // This recursively calls the destructor for each child
            Children[i] = nullptr;
        }
    }
}
void trie::delete_node(trie *curr){
    curr->isEndOfWord = false;
    for(int i = 0; i <= 25; i++){
        delete curr->Children[i];
        curr->Children[i] = nullptr;
    }
}
int trie::C_I_LUT(char character) {
    if(character == 'A') {
        return 0;
    } else if(character == 'B') {
        return 1;
    } else if(character == 'C') {
        return 2;
    } else if(character == 'D') {
        return 3;
    } else if(character == 'E') {
        return 4;
    } else if(character == 'F') {
        return 5;
    } else if(character == 'G') {
        return 6;
    } else if(character == 'H') {
        return 7;
    } else if(character == 'I') {
        return 8;
    } else if(character == 'J') {
        return 9;
    } else if(character == 'K') {
        return 10;
    } else if(character == 'L') {
        return 11;
    } else if(character == 'M') {
        return 12;
    } else if(character == 'N') {
        return 13;
    } else if(character == 'O') {
        return 14;
    } else if(character == 'P') {
        return 15;
    } else if(character == 'Q') {
        return 16;
    } else if(character == 'R') {
        return 17;
    } else if(character == 'S') {
        return 18;
    } else if(character == 'T') {
        return 19;
    } else if(character == 'U') {
        return 20;
    } else if(character == 'V') {
        return 21;
    } else if(character == 'W') {
        return 22;
    } else if(character == 'X') {
        return 23;
    } else if(character == 'Y') {
        return 24;
    } else if(character == 'Z') {
        return 25;
    } else {
        return -1; // For characters outside 'A'-'Z'
    }
}
void trie::load(trie *root){
    std::ifstream file("corpus.txt");
    std::string word;
    while(file >> word){
        insert_no_output(word, root);
    }
    std::cout << "success" << std::endl;
    file.close();
}
char trie::I_C_LUT(int i){
    if (i >= 0 && i <= 25) {
        // 'a' has an ASCII value of 97, so adding the index will give us the correct character
        return 'A' + i;
    } else {
        
    }
}
void trie::post_order_destructor_help(trie* root){
    for(int i = 0; i <= 25; i++){
        //std::cout << i << std::endl;
        if(this->Children[i] == nullptr){
        }else{
            this->Children[i]->post_order_destructor_help(this->Children[i]);
            delete this->Children[i];
            this->Children[i] = nullptr;
        }
    }
}

void trie::catch_error(){
    try{
        throw std::runtime_error("failure");
    }
    catch(const std::runtime_error){
        std::cout << "failure" << std::endl;
    }
}

int trie::count_child(trie *curr){
    int count = 0;
    for(int i = 0; i <= 25; i++){
        if(curr->Children[i] != nullptr){
            count++;
        }
    }
return count;
}

int trie::count_child_word(trie *curr){
    int count = 0;
    for(int i = 0; i <= 25; i++){
        if(curr->Children[i] != nullptr){
            count += count_child_word(curr->Children[i]);
        }
    }
    if(curr ->isEndOfWord == true){
        count ++;
    }
return count;
}