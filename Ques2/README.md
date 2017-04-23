#### Ques 2

- [x] Generate a random graph with n > 10 nodes.
- [x] Generate random n^2/2 directly edges.
- [x] Assign a weight in the range (1, 10).
- [x] Apply Dijkstra’s algorithm.
- [x] Find out the single source shortest path.
---
##### Generate Random Graph
```C
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

##### Initializing Graph

void Graph::initiate_graph(float d, float min, float max)
{
    if (NULL == connectivity_matrix){
        cout << "Memory Allocate Failed!" <<endl;
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
```

##### Generate random cost edges
``` C
float random_generator(float lower, float upper)
{
  //Get random Cost
    int range = (int)upper * 10 - (int)lower * 10;
    int temp = rand() % range + (int)lower * 10;
    return (float)temp / 10;
}
```
##### Apply Dijkstra's Algorithm

```C
void Graph::dijkstra_algorithm(int s, int t){
    if (closed_set.empty() == true)    {
        Vertex V;
        V.vertex_no = s;
        V.cost_from_start = 0;
        V.path_from_start.push_back(s);
        closed_set.push_back(V);
    }
    int current = s;
    if ((false == update_open_set(closed_set.back())) && (open_set.empty() == true))    {
        return;  //stop when open set is not updated and it is empty
    }else{
        current = update_closed_set();
    }
    if (current == t){
        return;  //stop when destination is included in closed set
    } else{
        dijkstra_algorithm(current, t);
    }
}
```

##### Find Shortest Path

```C
float Graph::get_shortest_path(int s, int t){
    if ((s < 1) || (s > number_of_vertices))    {
        cout << "No Such Start Vertex " << s <<endl;
        return 0.0;
    }
    if ((t < 1) || (t > number_of_vertices))    {
        cout << "No Such End Vertex " << t <<endl;
        return 0.0;
    }
    if (s == t)    {
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

    for (iter = T.path_from_start.begin(); iter != T.path_from_start.end(); iter++){
        if (*iter != T.path_from_start.back()){
            cout << (*iter) + 1 << "->";
        }else{
                   cout << (*iter) + 1 <<endl;
        }
    }
    open_set.clear();
    closed_set.clear();
    return T.cost_from_start;
}
```
