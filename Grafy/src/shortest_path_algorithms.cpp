#include "graphs/shortest_path_algorithms.hpp"
#define INF 999999

void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    int i,j,sptr, *Stack;
    Stack= new int[graph.Vertex_Quantity];
    sptr=0;
    std::vector<int> cost(graph.Vertex_Quantity, INF);
    std::vector<int> path(graph.Vertex_Quantity, -1);
    std::vector<bool> sets(graph.Vertex_Quantity, 0);
    
    cost[sourceIndex] = 0; //zerowy koszt dojścia do wierzchołka startowego

    for( i = 0; i < graph.Vertex_Quantity; i++ )
    {
        graph.Find_path_Dijkstra(cost,sets,path);
    }

    //dodanie wyników algorytmu dijkstry do klasy VertexResult
    for( i = 0; i < graph.Vertex_Quantity; i++ )
    {
        VertexResult VertexResult;

        for( j = i; j > -1; j = path[j]) 
        Stack[sptr++] = j;

        while(sptr) 
        VertexResult.path.push_back(Stack [ --sptr ]);

        VertexResult.cost=cost[i];

        result[i]=VertexResult;
    } 
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    int i,j,sptr, *Stack;
    bool negative_circle;
    Stack= new int[graph.Vertex_Quantity];
    sptr=0;
    std::vector<int> cost(graph.Vertex_Quantity, INF);
    std::vector<int> path(graph.Vertex_Quantity, -1);
    std::vector<bool> sets(graph.Vertex_Quantity, 0);
    
    cost[sourceIndex] = 0;  //zerowy koszt dojścia do wierzchołka startowego

    for( i = 1; i < graph.Vertex_Quantity; i++ )
    {
        graph.Find_path_Bellman_Ford(cost,sets,path);

    }

    if(graph.Check_Negative(cost)!=true)
    return false;

    //dodanie wyników algorytmu Bellmana Forda do klasy VertexResult
    for( i = 0; i < graph.Vertex_Quantity; i++ )
    {
        VertexResult VertexResult;

        for( j = i; j > -1; j = path[j])
        {   
            Stack[sptr++] = j;
        }
        
        while(sptr) 
        VertexResult.path.push_back(Stack [ --sptr ]);

        VertexResult.cost=cost[i];

        result[i]=VertexResult;
    }
    return true;
}
