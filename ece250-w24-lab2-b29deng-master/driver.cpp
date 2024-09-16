// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"

int main(int argc, char *argv[]){
    //std::cout << "Hello World" << std::endl;
    trie Trie;
    trie* root = &Trie; 
    std::string command, line, temp;

    while(std::getline(std::cin, line)){
        if(line == "p"){
            Trie.print(root, "");
            std::cout << std::endl;
        }else if(line == "load"){
            Trie.load(root);
        }else if(line == "empty"){
            Trie.empty(root);
        }else if(line == "clear"){
            root->clear();
        }else if(line == "size"){
            Trie.size();
        }else if(line == "exit"){
            Trie.~trie();
            return 0;
        }else{

            size_t position_1 = line.find(' ');
            if(position_1 != std::string::npos){
                command = line.substr(0, position_1);
                temp = line.substr(position_1 + 1);


                if(command == "i"){
                    Trie.insert(temp, root);
                }else if(command == "c"){
                    if(Trie.prefix_count(temp, root) == -1){
                        std::cout << "not found" << std::endl;
                    }else{
                        std::cout << "count is ";
                        std::cout << Trie.prefix_count(temp, root) << std::endl;
                    }
                }else if(command == "e"){
                    Trie.erase(temp);
                }else if(command == "spellcheck"){
                    Trie.spellcheck(temp, 0, root);
                }
            }
        }

    }
}