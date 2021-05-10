#include "graphs/generate_graphs.hpp"

//Funkcja do tworzenia plików z grafami o danych parametrach
void generate_parameters(std::vector<int> Verticies, std::vector<int> Density, std::vector<std::vector<std::string>>file_names, std::vector<std::vector<std::string>>file_names_N)
{   
    int Full_Density_Edges[Verticies.size()];                            
    int Edges[Verticies.size()][Density.size()];  

    for (int i = 0; i < Verticies.size(); i++)                              
    {
        //oblicznie ilości krawędzi przy pełnym grafie
        Full_Density_Edges[i] = (Verticies[i] * (Verticies[i] - 1))/2; 
        for (int j = 0; j < Density.size(); j++)
        {
            //obliczanie ilości krawędzi przy różnych gęstościach grafu
            Edges[i][j] = Density[j] * Full_Density_Edges[i] /100;
            generate_and_save(Verticies[i], Edges[i][j], file_names[i][j]);


            bool BF=false;
            while(!BF)  //Upewnienie się, że wygenerowany graf nie ma negative circle
            {
            generate_and_save_negative(Verticies[i], Edges[i][j], file_names_N[i][j]);
            std::ifstream inputStream{file_names_N[i][j]};
            auto graph = AdjacencyMatrixGraph::createGraph(inputStream);
            int sourceIndex;
            inputStream >> sourceIndex;
            ShortestPathResult result;
            BF=bellmanFord(*graph, sourceIndex, result);
            }
        }
    }
}


void generate_and_save(int Vertices, int Edges, std::string file_name)
{
    std::fstream os;
    os.open(file_name, std::ios_base::out);      
    os.close();
    os.open(file_name, std::ios_base::out);

    int Extra_Edges, Vertex_Index, j, k;
    Extra_Edges = Edges - Vertices + 1;
    Vertex_Index=Vertices; 
    j=0;
    srand (time(NULL));

    os<<Vertices<<" "<<Edges<<" "<<std::endl;
    for(int i = 0; i < Vertices - 1; i++)
        os<<i<<" "<<i+1<<" "<<rand()%(Vertices*10)<<std::endl;  //wygenerowanie kosztu

    while(j < Extra_Edges) ///wypisujemy pozostale krawdzie w zaleznosci od wypelnienia
    {
        k = 0;
        while(j < Extra_Edges && k < Vertex_Index - 2)
        {
            os<<Vertex_Index - 1<<" "<<k<<" "<<rand()%(Vertices*10)+1<<std::endl;
            k++;
            j++;
        }
        Vertex_Index--;
    }
    os<<rand()%Vertices<<std::endl;
    os.close();          
}

void generate_and_save_negative(int Vertices, int Edges, std::string file_name)
{
    std::fstream os;
    os.open(file_name, std::ios_base::out);       
    os.close();
    os.open(file_name, std::ios_base::out);

    int Extra_Edges, Vertex_Index, j, k;
    Extra_Edges = Edges - Vertices + 1;
    Vertex_Index=Vertices; 
    j=0;
    srand (time(NULL));

    os<<Vertices<<" "<<Edges<<" "<<std::endl;
    for(int i = 0; i < Vertices - 1; i++)
        os<<i<<" "<<i+1<<" "<<rand()%(Vertices*10)-rand()%(Vertices)+1<<std::endl; //wygenerowanie kosztu z możliwością kosztu ujemnego

    while(j < Extra_Edges) ///wypisujemy pozostale krawdzie w zaleznosci od wypelnienia
    {
        k = 0;
        while(j < Extra_Edges && k < Vertex_Index - 2)
        {
            os<<Vertex_Index - 1<<" "<<k<<" "<<rand()%(Vertices*10)-(rand()%Vertices)+1<<std::endl;
            k++;
            j++;
        }
        Vertex_Index--;
    }
    os<<rand()%Vertices<<std::endl;
    os.close();         
}
