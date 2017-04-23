#include <iostream>
#include <time.h>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include "Dijkstra.h"
using namespace std;

Graph::Graph(int n) : number_of_vertices(n)
{
    connectivity_matrix = new float *[number_of_vertices];
    int i;
    for (i = 0; i < number_of_vertices; i++)
    {
        connectivity_matrix[i] = new float[number_of_vertices];
    }
}

Graph::~Graph()
{
    int i;
    open_set.clear();
    closed_set.clear();
    for (i = 0; i < number_of_vertices; i++)
    {
        delete [] connectivity_matrix[i];
    }
    delete [] connectivity_matrix;
    connectivity_matrix = NULL;
}

inline float random_generator(float lower, float upper)
{
  //Get random Cost
    int range = (int)upper * 10 - (int)lower * 10;
    int temp = rand() % range + (int)lower * 10;
    return (float)temp / 10;
}

int Graph::get_vertices() const
{
    return number_of_vertices;
}

void Graph::initiate_graph(float d, float min, float max)
{
    if (NULL == connectivity_matrix){
        cout << "Memory Allocate Failed!" <<endl;
        return ;
    }
    if ((d <= 0.0) || (d > 1.0)){
        cout << "Invalid Graph Density!" << endl;
        return ;
    }
    if ((min <= 0.0) || (max <= 0.0) || (min >= max)){
        cout << "Invalid Edge Cost Range!" <<endl;
        return ;
    }
    graph_density = d;
    int i, j;
    float random;
    srand((unsigned int)time(NULL));
    for (i = 0; i < number_of_vertices; i++)
    {
        connectivity_matrix[i][i] = 0.0;                      //the cost from i to i is 0
        for (j = i + 1; j < number_of_vertices; j++)
        {
            random = random_generator(0.0, 1.0);              //get a decimal between 0 and 1
            if (random >= graph_density)                      //there is no path if random is less than density
            {
                connectivity_matrix[i][j] = 0.0;
                connectivity_matrix[j][i] = connectivity_matrix[i][j];          //undirected graph
            }
            else                                             //else, there is a path
            {
                connectivity_matrix[i][j] = random_generator(min, max);         //get a value between min to max, default is 1 to 10
                connectivity_matrix[j][i] = connectivity_matrix[i][j];
            }
        }
    }
}

void Graph::print_connectivity_matrix()
{
    int i, j;
    for (i = 0; i < number_of_vertices; i++)
    {
        for (j = 0; j < number_of_vertices; j++)
        {
            cout << setiosflags(ios::fixed) << setprecision(1) << connectivity_matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

float Graph::get_shortest_path(int s, int t)
{
    if ((s < 1) || (s > number_of_vertices))
    {
        cout << "No Such Start Vertex " << s <<endl;
        return 0.0;
    }
    if ((t < 1) || (t > number_of_vertices))
    {
        cout << "No Such End Vertex " << t <<endl;
        return 0.0;
    }
    if (s == t)
    {
        return 0.0;
    }
    dijkstra_algorithm(s - 1, t - 1);               //perform dijkstra's algorithm
    Vertex T = closed_set.back();                   //the last member of closed set
    if (T.vertex_no != t - 1)                       //the destination is not in
    {
        cout << "No Path From " << s << " To " << t << endl;
        open_set.clear();
        closed_set.clear();
        return -1;
    }
    cout <<" "<<s <<"\t" <<" "<<t << "\t";
    cout <<T.cost_from_start <<"\t\t";
    list<int>::iterator iter;

    for (iter = T.path_from_start.begin(); iter != T.path_from_start.end(); iter++)
    {
        if (*iter != T.path_from_start.back())
        {
            cout << (*iter) + 1 << "->";
        }
        else
        {
            cout << (*iter) + 1 <<endl;
        }
    }
    // cout <<  "\t\t"<<T.cost_from_start << endl;
    open_set.clear();
    closed_set.clear();
    return T.cost_from_start;
}

bool Graph::is_in_closed_set(int n)
{
    vector<Vertex>::iterator iter;
    for (iter = closed_set.begin(); iter != closed_set.end(); iter++)
    {
        if ((*iter).vertex_no == n)
        {
            return true;
        }
    }
    return false;
}

bool Graph::update_open_set(const Vertex &n)
{
    int i;
    bool open_set_updated = false;
    float temp_cost = 0;
    vector<Vertex>::iterator iter;
    for (i = 0; i < number_of_vertices; i++)
    {
        if ((connectivity_matrix[n.vertex_no][i] != 0.0) && !is_in_closed_set(i))       //if cost from n to i is not 0, and i is not in closed set
        {
            for (iter = open_set.begin(); iter != open_set.end(); iter++)               //check whether i is in open set
            {
                if ((*iter).vertex_no == i)
                {
                    temp_cost = n.cost_from_start + connectivity_matrix[n.vertex_no][i];//get cost from start to i through n
                    if (temp_cost < (*iter).cost_from_start)                            //if there is an approve, update it
                    {
                        (*iter).cost_from_start = temp_cost;
                        (*iter).path_from_start = n.path_from_start;
                        (*iter).path_from_start.push_back(i);
                        open_set_updated = true;
#ifdef DEBUG
                        cout << "open set update: " << i << ", " << connectivity_matrix[n.vertex_no][i] << endl;
#endif
                    }
                    break;
                }
            }
            if (iter == open_set.end())                     //i is not in open set, add it to open set
            {
                Vertex V;
                V.vertex_no = i;
                V.cost_from_start = connectivity_matrix[n.vertex_no][i] + n.cost_from_start;
                V.path_from_start = n.path_from_start;
                V.path_from_start.push_back(i);
                open_set.push_back(V);
                open_set_updated = true;

#ifdef DEBUG
                cout << "open set in: " << i << ", " << connectivity_matrix[n.vertex_no][i] << endl;
#endif

            }
        }
    }
    return open_set_updated;
}

int Graph::update_closed_set()
{
    vector<Vertex>::iterator iter;
    float min = open_set.begin()->cost_from_start;
    for (iter = open_set.begin(); iter != open_set.end(); iter++)
    {
        if ((*iter).cost_from_start < min)
        {
            min = (*iter).cost_from_start;                     //get the min value in open set
        }
    }
    for (iter = open_set.begin(); iter != open_set.end(); iter++)
    {
        if ((*iter).cost_from_start == min)
        {
            closed_set.push_back(*iter);                      //find the min one, add it to the closed set
#ifdef DEBUG
                cout << "closed set in: " << (*iter).vertex_no << ", " << (*iter).cost_from_start << endl;
#endif
            open_set.erase(iter);
            break;
        }
    }
    return closed_set.back().vertex_no;
}

void Graph::dijkstra_algorithm(int s, int t)
{
    if (closed_set.empty() == true)
    {
        Vertex V;
        V.vertex_no = s;
        V.cost_from_start = 0;
        V.path_from_start.push_back(s);
        closed_set.push_back(V);
    }
    int current = s;
    if ((false == update_open_set(closed_set.back())) && (open_set.empty() == true))
    {
        return;                                 //stop when open set is not updated and it is empty
    }
    else
    {
        current = update_closed_set();
    }
    if (current == t)
    {
        return;                                //stop when destination is included in closed set
    }
    else
    {
        dijkstra_algorithm(current, t);
    }
}
