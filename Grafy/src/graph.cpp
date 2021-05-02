#include "graphs/graph.hpp"


void Graph::Find_path_Dijkstra(std::vector<int>& cost, std::vector<bool>& sets, std::vector<int>& path)
{

}

void Graph::Find_path_Bellman_Ford(std::vector<int>& cost, std::vector<bool>& sets, std::vector<int>& path)
{

}

bool Graph::Check_Negative(std::vector<int>& cost)
{
    return true;
}



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
    for (int i=0; i<graph.Edge_Quantity; i++)   ///zerujemy koszt wszystkich krawędzi
    {
        for(int j=0; j<3; j++)
        {
            os<<graph.graph[i][j]<<" "; 
        }
        os<<std::endl;
    }
    return os;
}