#include "graph.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include <set>
#include <vector>
#include <utility>
#include <cmath>

// Constructors
Edge::Edge(){
    factor = 1;
}

Edge::Edge(double d, double s){
    distance = d;
    speed = s;
    factor = 1;
}
// -------------------------------------------------------
// Functions for Graph
void Graph::insert(int a, int b, double d, double s){
    if(a > 0 && a <= 500000 && b > 0 && b <= 500000){
        // do nothing
    }else{
        // out of bound
        //std::cout << "out of bound" << std::endl;
        return;
    }
    // get coordinates for Node a and Node b
    auto it_a = graph.find(a);
    auto it_b = graph.find(b);    
    // We check if a exists
    if(it_a != graph.end()){ // if exists
        if(it_b != graph.end()){ // b also exists
            // updates the edge on Node a
            graph[a][b].distance = d;
            graph[a][b].speed = s;
            // updates the edge on Node b
            graph[b][a].distance = d;
            graph[b][a].speed = s;
        }else{ // b does not exist
            // we need to insert b, with initial link to a
            graph[b][a] = Edge(d, s);
            // update node a with link to b, as well
            graph[a][b] = Edge(d, s);
        }
    }else{ // if a does not exist
        if(graph.find(b) == graph.end()){ // b does not as well
            // add node a, link a to b
            graph[a][b] = Edge(d, s);
            // add node b, link b to a
            graph[b][a] = Edge(d, s);
        }else{ // b does exist
            // insert a, with initial link to b
            graph[a][b] = Edge(d, s);
            graph[b][a] = Edge(d, s);
            // update node b, make it link to a
        }
    }
}

void Graph::load(std::string filename){
    std::ifstream file(filename);
    std::string command;
    while(getline(file, command)){
        int a, b;
        double d, s;

        std::istringstream iss(command);
        iss >> a >> b >> d >> s;
        insert(a,b,d,s);
    }
}

bool Graph::traffic(int a, int b, double A){
    if(a > 0 && a <= 500000 && b > 0 && b <= 500000 && A >= 0 && A <= 1){
        // do nothing
    }else{
        // out of bound
        //std::cout << "out of bound" << std::endl;
        return false;
    }

    auto it_a = graph.find(a);
    auto it_b = graph.find(b);
    if(it_a != graph.end() && it_b != graph.end()){
        graph[a][b].factor = A;
        graph[b][a].factor = A;
        return true;
    }else{
        return false;
    }
}

bool Graph::update(std::string filename){
    std::ifstream file(filename);
    std::string command;
    bool result = false;
    while(getline(file, command)){
        int a, b;
        double A;
        bool cycle_result = false;

        std::istringstream iss(command);
        iss >> a >> b >> A;
        cycle_result= traffic(a,b,A);
        if(cycle_result == true){
            result = true;
        }
    }
    return result;
}

bool Graph::print(int a){
    if(a > 0 && a <= 500000){

    }else{
        return false;
    }

    auto it_a = graph.find(a);
    if(it_a != graph.end()){
        for (const auto& innerPair : graph[a]) {
            std::cout << innerPair.first;
            std::cout << " " ;
        }
    }else{
        return false;
    }
    std::cout << std::endl;
    return true;
}

bool Graph::delete_node(int a){
    if(a <= 0 && a > 500000){
        return false;
    }
    auto it_a = graph.find(a);
    if(it_a != graph.end()){
        for (const auto& innerPair : graph[a]) {
            int connect_to = innerPair.first;
            graph[connect_to].erase(a);
        }
        graph.erase(a);
        return true;
    }else{
        return false;
    }
}

std::vector<int> Graph::path(int a, int b){
    auto it = graph.find(b);
    if(it == graph.end()){
        std::cout << "failure" << std::endl;
        std::vector<int> return_non(1, -1);
        return return_non;
    }
    std::priority_queue
    <std::pair<double, std::vector<int>>, std::vector<std::pair<double, std::vector<int>>>, MinComparator> pq_min;
    std::set<int> visited_set;
    //visited_set.insert(a);
    pq_min.push({0.0, {a}});

    while(pq_min.empty() == false){
        auto poped = pq_min.top();
        pq_min.pop();
        double current_weight = poped.first;
        std::vector<int> path = poped.second;
        int last_node = path.back();
        if (!visited_set.insert(last_node).second) {
            continue; // Node already processed
        }
        if (last_node == b){
            return path;
        }
        
        for (const auto& innerPair : graph[last_node]) {
            int next_node = innerPair.first;
            std::vector<int> next_path = path;
            double new_distance = current_weight + calculate_weight(innerPair);
            
            if(new_distance != INFINITY && visited_set.find(next_node) == visited_set.end()){
                next_path.push_back(next_node);

                /*if(next_node == b) {
                    return next_path; // Found viable path to destination
                }*/
        
                pq_min.push({new_distance, next_path});
            }
        }
    }
    std::cout << "failure" << std::endl;
    std::vector<int> return_non(1, -1);
    return return_non;
}

double Graph::lowest(int a, int b){
    auto it = graph.find(b);
    if(it == graph.end()){
        std::cout << "failure" << std::endl;
        std::vector<int> return_non(1, -1);
        return -1.0;
    }
    std::priority_queue
    <std::pair<double, std::vector<int>>, std::vector<std::pair<double, std::vector<int>>>, MinComparator> pq_min;
    std::set<int> visited_set;
    //visited_set.insert(a);
    pq_min.push({0.0, {a}});

    while(pq_min.empty() == false){
        auto poped = pq_min.top();
        pq_min.pop();
        double current_weight = poped.first;
        std::vector<int> path = poped.second;
        int last_node = path.back();
        if (!visited_set.insert(last_node).second) {
            continue; // Node already processed
        }
        if (last_node == b){
            return poped.first;
        }
        
        for (const auto& innerPair : graph[last_node]) {
            int next_node = innerPair.first;
            std::vector<int> next_path = path;
            double new_distance = current_weight + calculate_weight(innerPair);
            
            if(new_distance != INFINITY && visited_set.find(next_node) == visited_set.end()){
                next_path.push_back(next_node);

                /*if(next_node == b) {
                    return next_path; // Found viable path to destination
                }*/
        
                pq_min.push({new_distance, next_path});
            }
        }
    }
    std::cout << "failure" << std::endl;
    std::vector<int> return_non(1, -1);
    return -1;
}

//Help Function
double Graph::calculate_weight(const std::pair<const int, Edge> pair){
    return pair.second.distance / (pair.second.factor * pair.second.speed);
}
// implement classes' member functions here...