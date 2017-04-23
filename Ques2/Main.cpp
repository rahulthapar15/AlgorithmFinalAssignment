#include <iostream>
#include "Dijkstra.h"
using namespace std;

int main(int argc, char *argv[])
{
    Graph spare_Graph(50);
    spare_Graph.initiate_graph((float)0.2);

    float spare_sum = 0;  //the sum of shortest costs from 1 to 2, ..., 1 to 50 in graph with density 20%
    float dense_sum = 0;  //the sum of shortest costs from 1 to 2, ..., 1 to 50 in graph with density 40%
    float temp;
    int i;

  cout << "FROM\t TO \t COST\t\t PATH" << endl;
    for (i = 2; i <= spare_Graph.get_vertices(); i++)
    {
        temp = spare_Graph.get_shortest_path(1, i);
        if (temp > 0)
        {
            spare_sum += temp; //if there is a path, add to the sum
        }
    }

    return 0;
}
