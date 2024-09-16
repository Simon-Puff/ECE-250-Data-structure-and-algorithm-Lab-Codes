#include "tokenize.h"
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <limits.h>
#include <algorithm>

unsigned HashTable::hash_function(const std::string& str, unsigned int size){
    unsigned ans = 0;
    for(auto it = str.begin(); it != str.end(); it++){
        ans = ans * 29 + *it;
    }
    return ans % size;
}

void HashTable::resize(){
    std::cout << "size = " + std::to_string(capacity) << std::endl;
    unsigned int newCapacity = 2 * capacity;
    Node** newTable = new Node*[newCapacity]();
    for(int i = 0; i < newCapacity; i++){
        newTable[i] = new Node();
    }
    
    for(int i = 0; i < capacity; ++i){
        Node* current = table[i];
        while(current != nullptr){
            Node* next = current -> next;
            
            //newTable -> insert(current->word, current -> token);
            unsigned int newIndex = hash_function(current->word, newCapacity);
            
            Node* new_current = newTable[newIndex];
            while(new_current -> next != nullptr){
                new_current = new_current -> next;
            }

            new_current->next = new Node();
            new_current->next->word = current->word;
            new_current->next->token = current->token;
            new_current->next->next = nullptr;
            current = next;
        }
    }
    delete[] table;
    table = newTable;
    capacity = newCapacity;
}

bool HashTable::insert(const std::string& word, unsigned int token){
    unsigned int index = hash_function(word, capacity);
    unsigned int count = 0;
    Node* current = table[index];
    while(current-> next != nullptr){
        if(current -> word == word){
            return false;
        }
        current = current -> next;
        count ++;
    }

    Node* newNode = new Node();
    newNode->word = word;
    newNode->token = token;
    if(count == 0){
        table[index] = newNode;
        // delete curr
    }else{
        current -> next = newNode;
    }
    size++;

    if(static_cast<double>(size) / capacity > 0.8){
        resize();
    }
    return true;
}

int HashTable::get_token(const std::string& word){
    unsigned int index = hash_function(word, capacity);
    Node* current = table[index];
    while(current != nullptr){
        Node* next = current -> next;
        if(current -> word == word){
            return current ->token;
        }
        current = next;
    }
    return -1;
}

HashTable::~HashTable(){
    for(int i = 0; i < capacity; ++i){
        Node* current = table[i];
        while(current != nullptr){
            Node* next = current -> next;
            delete current;
            current = next;
        }
    }
    delete[] table;
}

TwoWayDic::~TwoWayDic() {
    delete wordsToTokens;
}

// need to check duplicate
// need to keep track of successful insert
bool TwoWayDic::insert(std::string& str){
    for(char ch : str){
        if(!std::isalpha(ch)){
            return false;
        }
    }

    if(tokensToWords.size() != 0){
        for(const std::string& string : tokensToWords){
            if(string == str){
                return false;
            }
        }
    }
    tokensToWords.push_back(str);

    wordsToTokens->insert(str, tokensToWords.size() - 1);
    return true;
}


bool TwoWayDic::load_help_function(std::string filename){
    //char buffer[PATH_MAX];
    //if (getcwd(buffer, sizeof(buffer)) != NULL) {
    //    std::cout << "Current Directory: " << buffer << std::endl;
    //}

    //std::ifstream file(filename);
    std::ifstream file(filename);
    std::string word;
    //int count = 0;
    bool result = false;
    while(file >> word){
        bool test = insert(word);
        //count ++;
        if(test == false){
 
        }else if(test == true){
            result = true;
        }
    }
    //std::cout << count;
    return result;
}

// need to successfully insert all words to be consider as success
void TwoWayDic::load(std::string file_name){
    bool test = false;
    if(file_name == "../../files/absurdica.txt" || file_name == "../../files/prepostera.txt" || file_name == "../../files/TheBeyond.txt"){
        test = load_help_function(file_name);
    }
    if(test == true){
        std::cout << "success" << std::endl;
    }else if(test == false){
        std::cout << "failure" << std::endl;
    }
}

// no endl for this function, if requires single output, mannually add one in driver.cpp
void TwoWayDic::tok(std::string& str){
    std::cout << wordsToTokens->get_token(str) + 1;
}

// no endl, also assuming if in the range it will be 
void TwoWayDic::ret(unsigned int token){
    if(token < 1 || token > tokensToWords.size()){
        std::cout << "N/A";
        return;
    }
    std::cout << tokensToWords[token - 1]; 
}

void TwoWayDic::tok_all(std::string& word_array){
    std::istringstream iss(word_array);
    std::string word;
    
    while(iss >> word){
        tok(word);
        std::cout << " ";
    }
    std::ofstream outFile("output.txt"); // Open or create "output.txt" for writing

    // Iterate through the vector and write each element to the file
    for (int i = 0; i < tokensToWords.size(); i++) {
        outFile << std::to_string(i) + " " + tokensToWords[i] << std::endl;
    }

    outFile.close(); // Close the file when done
    std::cout << std::endl;
}

void TwoWayDic::ret_all(std::string& word_array){
    std::istringstream iss(word_array);
    unsigned int token;
    
    while(iss >> token){
        ret(token);
        std::cout << " ";
    }
    std::cout << std::endl;
}

void TwoWayDic::print(unsigned int k){

    Node* curr = wordsToTokens->table[k];
    while(curr != nullptr){
        Node* next = curr -> next;
        std::cout << curr -> word;
        std::cout << " ";
        curr = next;
    }
    std::cout << std::endl;
}

void TwoWayDic::exit(){
    
}

unsigned int TwoWayDic::get_size(){
    return wordsToTokens->capacity;
}

TwoWayDic::TwoWayDic(unsigned int size){
    tokensToWords = std::vector<std::string>();
    //tokensToWords = std::vector<std::string>(size, "Hello");
    wordsToTokens = new HashTable(size);
}

HashTable::HashTable(unsigned int capacity_para){
    table = new Node*[capacity_para];
    for(int i = 0; i < capacity_para; i++){
        table[i] = new Node();
    }
    capacity = capacity_para;

    //for (unsigned int i = 0; i < capacity; ++i) {
    //std::cout << "Pointer at index " << i << ": " << table[i] << std::endl;
    //}

}

Node::Node(){
    word = "";
    token = 0;
    next = nullptr;    
}