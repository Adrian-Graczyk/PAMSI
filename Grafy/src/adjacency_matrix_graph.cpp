#include "graphs/adjacency_matrix_graph.hpp"
#define INF 999999
#define N_INF -999999


std::unique_ptr<Graph> AdjacencyMatrixGraph::createGraph(std::istream& is)
{  
    int V1, V2, cost;
    Graph graph;
    graph = graph.createGraph(is);

    AdjacencyMatrixGraph Matrix;
    Matrix.Vertex_Quantity=graph.Vertex_Quantity;
    Matrix.Edge_Quantity=graph.Edge_Quantity;
    Matrix.Matrix.resize(Matrix.Vertex_Quantity, std::vector<int>(Matrix.Vertex_Quantity));
   
    for (int i=0; i<graph.Vertex_Quantity; i++)   ///zerujemy koszt wszystkich krawędzi
    {
        for(int j=0; j<graph.Vertex_Quantity; j++)
        {
            Matrix.Matrix[i][j] = 0;
        }
    }
    
    for (int i=0; i<graph.Edge_Quantity; i++)
    {
        V1 = graph.graph[i][0];       
        V2 = graph.graph[i][1];
        cost = graph.graph[i][2];
        Matrix.Matrix[V1][V2] = cost;  ///wpisujemy dane do macierzy sasiedztwa dla grafu skierowanego
    }

    return std::make_unique<AdjacencyMatrixGraph>(Matrix);
}

std::ostream& operator<<(std::ostream& os, const AdjacencyMatrixGraph& Matrix)
{
    for (int i=0; i<Matrix.Vertex_Quantity; i++)   ///zerujemy koszt wszystkich krawędzi
    {
        for(int j=0; j<Matrix.Vertex_Quantity; j++)
        {
            os<<Matrix.Matrix[i][j]<<" "; 
        }
        os<<std::endl;
    }
    return os;
}

void AdjacencyMatrixGraph::Find_path_Dijkstra(std::vector<int>& cost, std::vector<bool>& sets, std::vector<int>& path)
{
    int min_cost, min_index;
    min_cost=INF;
  
    for (int i = 0; i < this->Vertex_Quantity; i++)
    {
        if(sets[i] == false && cost[i] < min_cost)
        {
            min_cost = cost[i]; 
            min_index = i;
        }
    }
    
    sets[min_index]=true;

    for (int i = 0; i < this->Vertex_Quantity; i++)
    {
        if (!sets[i] && this->Matrix[min_index][i] && cost[min_index] 
        != INF && cost[min_index] + this->Matrix[min_index][i] < cost[i])
        {
            cost[i] = cost[min_index] + this->Matrix[min_index][i];
            path[i]=min_index;
        }     
    }
}

void AdjacencyMatrixGraph::Find_path_Bellman_Ford(std::vector<int>& cost, std::vector<bool>& sets,std::vector<int>& path)
{
    for(int i = 0; i < this->Vertex_Quantity; i++)
    {
        for(int j = 0; j < this->Vertex_Quantity; j++)    ///przeszukujemy macierz sasiedztwa w poszukiwaniu krawedzi dla
                                                            ///danego wierzcholka relaksujac kolejne krawedzie
        {
            if(cost[i] != INF && this->Matrix[i][j] != 0 && cost[j] > cost[i] + this->Matrix[i][j])
            {
                cost[j] = cost[i] + this->Matrix[i][j];
                path[j] = i;
            }
        }
    }
}

bool AdjacencyMatrixGraph::Check_Negative(std::vector<int>& cost)
{
    for(int k = 1; k < this->Vertex_Quantity; k++)
    {
        for(int i = 0; i < this->Vertex_Quantity; i++)
        {
            for(int j = 0; j < this->Vertex_Quantity; j++)
            {
                if(this->Matrix[i][j] && cost[j] > (cost[i] + this->Matrix[i][j]) )
                {
                    return false;
                }
            }
        }
    }
    return true;
}
