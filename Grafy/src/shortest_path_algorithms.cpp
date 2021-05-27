#include "graphs/shortest_path_algorithms.hpp"
#define INF 999999

void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    int i,j,k,u,sptr,Weight, *Stack;
    Stack= new int[graph.Vertex_Quantity];
    sptr=0;
    std::vector<int> cost(graph.Vertex_Quantity, INF);
    std::vector<int> path(graph.Vertex_Quantity, -1);
    std::vector<bool> sets(graph.Vertex_Quantity, 0);
    
    cost[sourceIndex] = 0; //zerowy koszt dojścia do wierzchołka startowego

    for( k = 0; k < graph.Vertex_Quantity; k++ )
    {
        for( j = 0; sets[j]; j++ );
        for( u = j++; j < graph.Vertex_Quantity; j++ )
            if( !sets[j] && (cost[j] < cost[u] )) 
                u = j;

        sets[u]=true; //oznaczenie wierzchołka jako użytego (z obliczona ścieżką)

        for(int j : graph.neighbours(u))
        {
            Weight = graph.get_Weight(u,j);

            if(!sets[j] && graph.check_zero(u,j) && cost[j] > (cost[u] + Weight) 
            && cost[u] != INF)
            {
                cost[j] = cost[u] + Weight;
                path[j] = u;
            }
        }
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
    int k, i,j,sptr, *Stack, Weight;
    bool negative_circle;
    Stack= new int[graph.Vertex_Quantity];
    sptr=0;
    std::vector<int> cost(graph.Vertex_Quantity, INF);
    std::vector<int> path(graph.Vertex_Quantity, -1);

    cost[sourceIndex] = 0;  //zerowy koszt dojścia do wierzchołka startowego
    
    for( k = 1; k < graph.Vertex_Quantity; k++ )
    {
        for(int i = 0; i < graph.Vertex_Quantity; i++)
        {   
            for(int j : graph.neighbours(i))
            {
                Weight = graph.get_Weight(i,j);

                if (cost[j]>cost[i]+Weight && graph.check_zero(i,j))
                {
                    cost[j] = cost[i] + Weight;
                    path[j] = i;
                }
            }    
        }
    }

    //sprawdzanie negative circle
    for(int k = 1; k < graph.Vertex_Quantity; k++)
    {
        for(int i = 0; i < graph.Vertex_Quantity; i++)
        {
            for(int j : graph.neighbours(i))
            {
                Weight = graph.get_Weight(i,j);

                if(graph.check_zero(i,j) && cost[j] > (cost[i] + Weight) )
                {   
                    return false;
                }
            }
        }
    }

    //if(graph.Check_Negative(cost)!=true)
    //return false;

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
