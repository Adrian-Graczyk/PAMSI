#include "graphs/adjacency_list_graph.hpp"


Graph_Connection::Graph_Connection(int Cost, int End)
{
EndVertexIndex = End;
cost = Cost;
}

//Stworzenie listy sąsiedztwa z wczytanego grafu
std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)
{
    int V1;
    Graph graph;
    graph = graph.createGraph(is);
    Graph_Connection Connection;
    
    AdjacencyListGraph List;
    List.Vertex_Quantity=graph.Vertex_Quantity;
    List.Edge_Quantity=graph.Edge_Quantity;
    List.List.resize(List.Vertex_Quantity);

    for (int i=0; i<graph.Edge_Quantity; i++)
    {
        V1 = graph.graph[i][0];       
        Connection.EndVertexIndex = graph.graph[i][1];
        Connection.cost = graph.graph[i][2];
        List.List[V1].push_back(Connection); 
    }
    return std::make_unique<AdjacencyListGraph>(List);
}

std::ostream& operator<<(std::ostream& os, const AdjacencyListGraph& List)
{
    int k;
    Graph_Connection connection;
    os<<"Adjacency List:"<<std::endl;
    for (int i=0; i<List.Vertex_Quantity; i++)  
    {   
        k=List.List[i].size();
        os<<i<<"- ";
        for(int j=0; j<k; j++)
        {
            connection=List.List[i][j];
            os<<"("<<connection.EndVertexIndex<<", "<<connection.cost<<") ";
        }
        os<<std::endl;
    }
    return os;
}

std::vector<int> AdjacencyListGraph::neighbours(int i)
{
    std::vector<int> neighbours;
    std::vector<Graph_Connection>::iterator k;
    for(k = this->List[i].begin(); k!=this->List[i].end(); ++k)
    {
        neighbours.push_back((*k).EndVertexIndex);
    }
    return neighbours;
}

int AdjacencyListGraph::get_Weight(int i, int j)
{
    int weight;
    std::vector<Graph_Connection>::iterator k;
    for(k = this->List[i].begin(); k!=this->List[i].end(); ++k)
    {
        if(j==(*k).EndVertexIndex)
            weight = (*k).cost;
    }
    return weight;
}

bool AdjacencyListGraph::check_zero(int i, int j)
{
    return true;
}

