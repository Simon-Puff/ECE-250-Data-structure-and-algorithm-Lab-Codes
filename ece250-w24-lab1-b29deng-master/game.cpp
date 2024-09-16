#include "game.h"
#include <iostream>
using namespace std;
#include <cmath>
// implement classes' member functions here...

Game::Game(){
    Game::head_pointer = nullptr;
    Game::tail_pointer = nullptr;
    Game::player_number = 0;
}

Game::~Game(){
    Player_node* current = head_pointer;
    while(current != nullptr){
        Player_node* next_pointer = current -> next;
        delete current;
        current = next_pointer;
        next_pointer = nullptr;
    }
    current = nullptr;
    head_pointer = nullptr;
    tail_pointer = nullptr;
}

void Game::Spawn_newplayer(double x, double y){
    if( (x > 0) && (x <= 500) && (y > 0) && (y <= 500) ){
        Player_node* newNode = new Player_node(x ,y);
        if(head_pointer == nullptr){
            head_pointer = newNode;
            tail_pointer = newNode;
            newNode->prev = nullptr;
            newNode->next = nullptr;
        }else{
            Player_node* temp;
            temp = head_pointer;
            head_pointer = newNode;
            head_pointer->next = temp;
            temp->prev = head_pointer;
            temp = nullptr;
        }
        Game::player_number ++;
    cout << "success" << endl;
    }else{
        std::cout << "failure" << std::endl;
    }

}
void Game::Time_getclose(double t){
    Player_node* execution_pointer = head_pointer;
    if((t>0) && (t<=500)){
        while(execution_pointer!= nullptr){
            double x,y;
            x = execution_pointer->x_location;
            y = execution_pointer->y_location;
            //cout << execution_pointer->x_location;
            //cout << " ";
            //cout << execution_pointer->y_location;
            //cout << "before" << endl;
            execution_pointer->x_location -= t * cos(atan2(y,x));
            execution_pointer->y_location -= t * sin(atan2(y,x));
            //cout << execution_pointer->x_location;
            //cout << " ";
            //cout << execution_pointer->y_location;
            //cout << "after" << endl;

            if(Check_quadrant(execution_pointer) == false){
                Player_node* temp = execution_pointer->next;
                Remove_node(execution_pointer);
                execution_pointer = temp;
                temp = nullptr;
            }else{
            execution_pointer = execution_pointer -> next;
            }
        }
    }
    Num_getnumber();
}


void Game::Lunch_eliminate(){
    Player_node* execution_pointer = head_pointer;
    while(execution_pointer!= nullptr){
        if(Calculate_distance(execution_pointer) < 1){
            //cout << "Distance is: ";
            //cout << Calculate_distance(execution_pointer) << endl;
            Player_node* temp = execution_pointer -> next;
            Remove_node(execution_pointer);
            execution_pointer = temp;
        }else{
        execution_pointer = execution_pointer -> next;
        }
    }
    Num_getnumber();
}
void Game::Num_getnumber(){
    std::string ch = "num of players: ";
    std::string result = ch + std::to_string(player_number);
    cout << result << endl;
}
void Game::Prt_printcoord(double d){
    Player_node* execution_pointer = head_pointer;
    int count = 0;
    while(execution_pointer!= nullptr){
        if((Calculate_distance(execution_pointer) < d) && (count == 0)){
            char ch = ' ';
            std::string x_str, y_str;
            x_str = std::to_string(execution_pointer->x_location);
            y_str = std::to_string(execution_pointer->y_location);
            x_str = x_str.erase(x_str.find_last_not_of('0')+1, std::string::npos);
            y_str = y_str.erase(y_str.find_last_not_of('0')+1, std::string::npos);
            if (x_str.back() == '.'){
                x_str.pop_back();
            }            
            if (y_str.back() == '.'){
                y_str.pop_back();
            }
            std::string result = x_str + ch + y_str;
            cout << result;
            count ++;
        }else if((Calculate_distance(execution_pointer) < d) && (count != 0)){
            char ch = ' ';
            std::string x_str, y_str;
            x_str = std::to_string(execution_pointer->x_location);
            y_str = std::to_string(execution_pointer->y_location);
            x_str = x_str.erase(x_str.find_last_not_of('0')+1, std::string::npos);
            y_str = y_str.erase(y_str.find_last_not_of('0')+1, std::string::npos);
            if (x_str.back() == '.'){
                x_str.pop_back();
            }            
            if (y_str.back() == '.'){
                y_str.pop_back();
            }
            std::string result =ch + x_str + ch + y_str;
            cout << result;
            count ++;
        }
        execution_pointer = execution_pointer -> next;
    }
    if(count == 0){
        cout << "no players found" << endl;
    }else{
    cout << endl;
    }
}

bool Game::Check_quadrant(Player_node* curr){
    if((curr->x_location > 0) && (curr->y_location >0)){
        //cout << curr->x_location + curr->y_location << endl;
        //cout << "TRUE";
        return true;
    }else{
        return false;
    }
}
void Game::Remove_node(Player_node* curr){
    if (!curr) return; // Safeguard against nullptr input.

    // Single-node case:
    if (head_pointer == tail_pointer) {
        head_pointer = nullptr;
        tail_pointer = nullptr;
    }
    else if (curr == head_pointer) {
        head_pointer = curr->next;
        if (head_pointer) head_pointer->prev = nullptr;
    }
    else if (curr == tail_pointer) {
        tail_pointer = curr->prev;
        if (tail_pointer) tail_pointer->next = nullptr;
    }
    else {
        if (curr->prev) curr->prev->next = curr->next;
        if (curr->next) curr->next->prev = curr->prev;
    }

    delete curr;
    Game::player_number--;
}


double Game::Calculate_distance(Player_node* curr){
    double x, y;
    x = curr->x_location;
    y = curr->y_location;
    double distance;
    distance = sqrt(pow(curr->x_location, 2) + pow(curr->y_location, 2));
    //cout << "distance: ";
    //cout << distance;
    //cout << endl;
    return distance;
}

int Game::return_count(){
    return player_number;
}

void Game::help_getnode(){
    Player_node* execution_pointer = head_pointer;
    while(execution_pointer!= nullptr){
        cout<< execution_pointer->x_location;
        cout<< " ";
        cout<< execution_pointer->y_location;
        execution_pointer = execution_pointer->next;
    }
}