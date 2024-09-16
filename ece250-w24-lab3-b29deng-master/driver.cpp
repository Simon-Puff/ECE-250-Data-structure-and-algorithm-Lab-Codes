// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "tokenize.h"


int main(int argc, char *argv[]){
    std::string command, line, temp;
    TwoWayDic *dic = nullptr;
    
    while(std::getline(std::cin, line)){
        if(line == "exit"){
            dic->~TwoWayDic();
            return 0;
        }else{
            size_t position_1 = line.find(' ');
            if(position_1 != std::string::npos){
                command = line.substr(0, position_1);
                temp = line.substr(position_1 + 1);


                if(command == "create"){
                    unsigned int size = std::stoul(temp);
                    if(size < 1 || size > 256){

                    }else{
                        dic = new TwoWayDic(size);
                    }
                    std::cout << "success" << std::endl;
                }else if(command == "insert"){
                    bool result = dic->insert(temp);
                    if(result == true){
                        std::cout << "success" << std::endl;
                    }else{
                        std::cout << "failure" << std::endl;
                    }
                }else if(command == "load"){
                    dic->load(temp);
                }else if(command == "tok"){
                    dic->tok(temp);
                    std::cout << std::endl;
                }else if(command == "ret"){
                    unsigned int size = std::stoul(temp);
                    if(size < 1 || size > dic->get_size()){

                    }else{
                        dic->ret(size);
                        std::cout << std::endl;
                    }
                }else if(command == "tok_all"){
                    dic->tok_all(temp);
                }else if(command == "ret_all"){
                    dic->ret_all(temp);
                }else if(command == "print"){
                    unsigned int size = std::stoul(temp);
                    if(size < 0 || size > dic->get_size()){

                    }else{
                        dic->print(size);
                    }
                }
            }
        }

    }

}