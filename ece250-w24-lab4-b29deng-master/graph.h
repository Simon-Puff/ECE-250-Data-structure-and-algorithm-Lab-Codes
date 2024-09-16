// define your classes here...
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <unordered_map>
#include <vector>

struct Edge{
    double distance;
    double speed;
    double factor;
    Edge();
    Edge(double d, double s);
    ~Edge() = default;
};

struct MinComparator {
    bool operator()(const std::pair<double, std::vector<int>>& a, const std::pair<double, std::vector<int>>& b) {
        return a.first > b.first; // Compare based on the double value
    }
};

class Graph{
    private:
        std::unordered_map <int, std::unordered_map<int, Edge >> graph;
        double calculate_weight(const std::pair<const int, Edge>);
    public:
        Graph() = default;
        ~Graph() = default;
        void insert(int a, int b, double d, double s);
        void load(std::string filename);
        bool traffic(int a, int b, double A);
        bool update(std::string filename);
        bool print(int a);
        bool delete_node(int a);
        std::vector<int> path(int a, int b);
        double lowest(int a, int b);
};

#endif