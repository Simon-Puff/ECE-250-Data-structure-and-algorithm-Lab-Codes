#ifndef GAME_H
#define GAME_H
// define your classes here...
struct Player_node
{
    double x_location, y_location;
    Player_node* prev;
    Player_node* next;
    
    Player_node(double x, double y) 
    : x_location(x), y_location(y), 
    prev(nullptr), next(nullptr) {}
};

class Game
{
private:
    int player_number;
    Player_node* head_pointer;
    Player_node* tail_pointer;

public:
    Game();
    ~Game();

    void Spawn_newplayer(double x, double y);
    void Time_getclose(double t);
    void Lunch_eliminate();
    void Num_getnumber();
    void Prt_printcoord(double d);
    bool Check_quadrant(Player_node* curr);
    void Remove_node(Player_node* curr);
    double Calculate_distance(Player_node* curr);
    int return_count();
    void help_getnode();
};


#endif