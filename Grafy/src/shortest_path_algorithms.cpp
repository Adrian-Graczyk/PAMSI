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
    
    cost[sourceIndex] = 0;

    for( i = 0; i < graph.Vertex_Quantity; i++ )
    {
        graph.Find_path_Dijkstra(cost,sets,path);

    }

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


   /* if(graph.Vertex_Quantity<15)
    {
        for( i = 0; i < graph.Vertex_Quantity; i++ )
        {
            std::cout << i << ": ";

            // Ścieżkę przechodzimy od końca ku początkowi, 
            // Zapisując na stosie kolejne wierzchołki

        for( j = i; j > -1; j = path[ j ] ) Stack [ sptr++ ] = j;

        // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

        while( sptr ) std::cout << Stack [ --sptr ] << " ";

        // Na końcu ścieżki wypisujemy jej koszt

        std::cout << "$" << cost [ i ] << std::endl;
        }
    }*/
  
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    int i,j,sptr, *Stack;
    Stack= new int[graph.Vertex_Quantity];
    sptr=0;
    std::vector<int> cost(graph.Vertex_Quantity, INF);
    std::vector<int> path(graph.Vertex_Quantity, -1);
    std::vector<bool> sets(graph.Vertex_Quantity, 0);
    
    cost[sourceIndex] = 0;

    for( i = 1; i < graph.Vertex_Quantity; i++ )
    {
        graph.Find_path_Bellman_Ford(cost,sets,path);

    }

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

    /*if(graph.Vertex_Quantity<15)
    {
        for( i = 0; i < graph.Vertex_Quantity; i++ )
        {
            std::cout << i << ": ";

            // Ścieżkę przechodzimy od końca ku początkowi, 
            // Zapisując na stosie kolejne wierzchołki

        for( j = i; j > -1; j = path[ j ] ) Stack [ sptr++ ] = j;

        // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

        while( sptr ) std::cout << Stack [ --sptr ] << " ";

        // Na końcu ścieżki wypisujemy jej koszt

        std::cout << "$" << cost [ i ] << std::endl;
        }
    }*/

    return graph.Check_Negative(cost);
}
