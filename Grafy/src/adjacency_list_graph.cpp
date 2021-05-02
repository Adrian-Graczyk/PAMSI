#include "graphs/adjacency_list_graph.hpp"


Graph_Connection::Graph_Connection(int Cost, int End)
{
EndVertexIndex = End;
cost = Cost;
}

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

/*void AdjacencyListGraph::Dijkstra_Shortest(int sourceIndex, ShortestPathResult& result)
{
    int i,j,u;
    std::vector<int> cost(this->Vertex_Quantity, 999999);
    std::vector<int> path(this->Vertex_Quantity, -1);
    std::vector<bool> sets(this->Vertex_Quantity, 0);
  
    std::vector<Graph_Connection> connection;
  
    // Insert source itself in Set and initialize its
    // distance as 0.
    connection.push_back(Graph_Connection(0,sourceIndex));
    cost[sourceIndex] = 0;
  
    for( i = 0; i < this->Vertex_Quantity; i++ )
    {
        // Szukamy wierzchołka w Q o najmniejszym koszcie 
        for( j = 0; sets[j]; j++ );
            for( u = j++; j < this->Vertex_Quantity; j++ )
                if( !sets[j] && (cost[j] < cost[u] )) 
                    u = j;

        sets[u]=true;

        std::vector<Graph_Connection>::iterator k;
        for( k = this->List[u].begin(); k!=this->List[u].end(); ++k)
        {

            int v = (*k).EndVertexIndex;
            int weight = (*k).cost;

            if (!sets[v] && (cost[v]>cost[u]+weight))
            {
                cost[v] = cost[u] + weight;
                path[v]=u;
            }
        }


    }
}*/

void AdjacencyListGraph::Find_path_Dijkstra(std::vector<int>& cost, std::vector<bool>& sets,std::vector<int>& path)
{
    int j, u;
    for( j = 0; sets[j]; j++ );
        for( u = j++; j < this->Vertex_Quantity; j++ )
            if( !sets[j] && (cost[j] < cost[u] )) 
                u = j;

        sets[u]=true;

    std::vector<Graph_Connection>::iterator k;
    for( k = this->List[u].begin(); k!=this->List[u].end(); ++k)
    {

        int v = (*k).EndVertexIndex;
        int weight = (*k).cost;

        if (!sets[v] && (cost[v]>cost[u]+weight))
        {
            cost[v] = cost[u] + weight;
            path[v]=u;
        }
    }
}

void AdjacencyListGraph::Find_path_Bellman_Ford(std::vector<int>& cost, std::vector<bool>& sets,std::vector<int>& path)
{
   
    for(int i=0; i< this->Vertex_Quantity; i++)
    {
        std::vector<Graph_Connection>::iterator k;
        for(k = this->List[i].begin(); k!=this->List[i].end(); ++k)
        {
            int v = (*k).EndVertexIndex;
            int weight = (*k).cost;

            if (cost[v]>cost[i]+weight)
            {
                cost[v] = cost[i] + weight;
                path[v]=i;
            }
        }
    }
    
}

bool AdjacencyListGraph::Check_Negative(std::vector<int>& cost)
{
    for(int i=0; i< this->Vertex_Quantity; i++)
    {
        std::vector<Graph_Connection>::iterator k;
        for(k = this->List[i].begin(); k!=this->List[i].end(); ++k)
        {
            int v = (*k).EndVertexIndex;
            int weight = (*k).cost;

            if(cost[v]>cost[i]+weight)
            return false;
        }
    }
    
    return true;
}