#include "graphs/graph.hpp"


bool Graph::check_zero(int i, int j)
{
    return 0;
}

std::vector<int> Graph::neighbours(int i)
{
    std::vector<int> tmp;
    return tmp;
}

int Graph::get_Weight(int i, int j)
{
    return 0;
}

//Tworzenie grafu z pliku
Graph Graph::createGraph(std::istream& is)
{
    Graph graph;
    int V1, V2, cost;
  
    is >> graph.Vertex_Quantity;
    is >> graph.Edge_Quantity;
    
    for(int i=0; i<graph.Edge_Quantity; i++)   
    {
        std::vector<int> vector;
        is >> V1;
        is >> V2;
        is >> cost;

        vector.push_back(V1);
        vector.push_back(V2);
        vector.push_back(cost);

        graph.graph.push_back(vector);
    }

    return graph;
}

std::ostream& operator<<(std::ostream& os, const Graph& graph)
{
    for (int i=0; i<graph.Edge_Quantity; i++)  
    {
        for(int j=0; j<3; j++)
        {
            os<<graph.graph[i][j]<<" "; 
        }
        os<<std::endl;
    }
    return os;
}