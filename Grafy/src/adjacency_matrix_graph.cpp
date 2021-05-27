#include "graphs/adjacency_matrix_graph.hpp"
#define INF 999999
#define N_INF -999999

//Stworzenie macierzy sąsiedztwa z wczytanego grafu
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
    for (int i=0; i<Matrix.Vertex_Quantity; i++)   
    {
        for(int j=0; j<Matrix.Vertex_Quantity; j++)
        {
            os<<Matrix.Matrix[i][j]<<" "; 
        }
        os<<std::endl;
    }
    return os;
}

std::vector<int> AdjacencyMatrixGraph::neighbours(int i)
{
    std::vector<int> neighbours;
    for(int j = 0; j < this->Vertex_Quantity; j++)    
    {
        neighbours.push_back(j);
    }
    return neighbours;
}

int AdjacencyMatrixGraph::get_Weight(int i, int j)
{
   return this->Matrix[i][j]; 
}

bool AdjacencyMatrixGraph::check_zero(int i, int j)
{ 
    if(this->Matrix[i][j] != 0)
    return true;
    else
    return false;
}

