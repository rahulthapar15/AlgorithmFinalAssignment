#pragma once

#include <vector>
#include <list>
using namespace std;

typedef struct point
{
    int vertex_no;     //vertex Number
    list<int> path_from_start;  //the vertices on the shortest path from start
    float cost_from_start;  //the cost of the shortest path from start
}Vertex;

class Graph
{
private:
    float **connectivity_matrix;                        //connectivity matrix of graph
    const int number_of_vertices;                       //total number of vertices in the graph
    float graph_density;                                //density of the graph

    vector<Vertex> closed_set;                          //a set inclue closest nodes
    vector<Vertex> open_set;                            //a set inclue successors of closest nodes

    //find the shortest path from s to t
    void dijkstra_algorithm(int s, int t);

    //update the open set from n, return whether it is updated
    bool update_open_set(const Vertex &n);

    //update the closed set, return number of the new member of closed set
    int update_closed_set();

    //check whether n is in closed set
    bool is_in_closed_set(int n);
public:
    Graph(int n = 50);
    ~Graph();

    //initiate a graph with density d, and edges' cost in range(min, max)
    void initiate_graph(float d, float min = 1.0, float max = 10.0);

    //interface for user to get the shortest path from s to t
    float get_shortest_path(int s, int t);

    //print the connectivity matrix of the graph
    void print_connectivity_matrix();

    //return the total number of vertices in the graph
    int get_vertices() const;
};

//generate a number in range(lower, upper)
inline float random_generator(float lower, float upper);
