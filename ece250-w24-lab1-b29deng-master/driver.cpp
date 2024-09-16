// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "game.h"


int main(int argc, char *argv[]){
    Game game;
    std::string line, command, time, distance, temp;
    double x,y;

     while(std::getline(std::cin, line)){
        if(line == "get"){
            game.help_getnode();
        }
        if(line == "LUNCH"){
            game.Lunch_eliminate();
        }else if(line == "NUM"){
            game.Num_getnumber();
        }else if(line == "OVER"){
            if(game.return_count() == 0){
                std::cout << "wolf wins" << std::endl;
            }else if(game.return_count() != 0){
                std::cout << "players win" << std::endl;
            }
            game.~Game();
            break;
        }else{

            size_t position_1 = line.find(' ');
            if(position_1 != std::string::npos){
                command = line.substr(0, position_1);
                temp = line.substr(position_1 + 1);
            if(command == "TIME"){
                time = temp;
                game.Time_getclose(std::stod(time));
            }else if(command == "PRT"){
                distance = temp;
                game.Prt_printcoord(std::stod(distance));
            }else{
                size_t position_2 = temp.find(' ');
                if(command == "SPAWN"){
                    x = std::stod(temp.substr(0, position_2));
                    y = std::stod(temp.substr(position_2 + 1));
                    game.Spawn_newplayer(x,y);
                }
            }
            }
        }

        
     }
     return 0;
}