// include libraries here
#include <iostream>
#include <string>
#include "graph.h"
#include <sstream>
#include <vector>
#include <iomanip>


int main(int argc, char *argv[]){
    std::string command, line, temp;
    int a, b;
    double d, s, A;
    Graph graph;

    while(std::getline(std::cin, line)){
        if(line == "exit"){
            return 0;
        }else{
            size_t position_1 = line.find(' ');
            if(position_1 != std::string::npos){
                command = line.substr(0, position_1);
                temp = line.substr(position_1 + 1);
            }
            if(command == "insert"){
                std::istringstream iss(temp);
                iss >> a >> b >> d >> s;
                graph.insert(a,b,d,s);
                std::cout << "success" << std::endl;
                /*
                size_t position_1 = temp.find(' ');
                a = temp[position_1 - 1] - '0';
                b = temp[position_1 + 1] - '0';
                temp = temp.erase(0, position_1 + 3);
                size_t position_2 = temp.find(' ');
                d = std::stod(temp.substr(0, position_1 - 1));
                s = std::stod(temp.substr(position_1 + 1));
                graph.insert(a,b,d,s);
                */
            }else if(command == "load"){
                graph.load(temp);
                std::cout << "success" << std::endl;
            }else if(command == "traffic"){
                std::istringstream iss(temp);
                iss >> a >> b >> A;
                bool result = graph.traffic(a , b , A);
                if(result == true){
                    std::cout << "success" << std::endl;
                }else{
                    std::cout << "failure" << std::endl;
                }
            }else if(command == "update"){
                bool result = graph.update(temp);
                if(result == true){
                    std::cout << "success" << std::endl;
                }else{
                    std::cout << "failure" << std::endl;
                }
            }else if(command == "print"){
                bool result = graph.print(std::stoi(temp));
                if(result == true){
                    //std::cout << "success" << std::endl;
                }else{
                    std::cout << "failure" << std::endl;
                }
            }else if(command == "delete"){
                bool result = graph.delete_node(std::stoi(temp));
                if(result == true){
                    std::cout << "success" << std::endl;
                }else{
                    std::cout << "failure" << std::endl;
                }
            }else if(command == "path"){
                std::istringstream iss(temp);
                iss >> a >> b;
                std::vector<int> shortest_path = graph.path(a, b);
                if(shortest_path.size() != 1 && shortest_path.front() != -1){
                    for(int i : shortest_path){
                        std::cout << i;
                        std::cout << " ";
                    }
                    std::cout << std::endl;
                }
            }else if(command == "lowest"){
                std::istringstream iss(temp);
                iss >> a >> b;
                double result = graph.lowest(a, b);
                if(result == -1.0){

                }else{
                    std::cout << std::fixed;
                    std::cout << std::setprecision(3);
                    std::cout << result << std::endl;
                }
            }
        }
    }
}