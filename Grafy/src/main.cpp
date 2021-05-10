#include <iostream>
#include "graphs/timer.hpp"
#include "graphs/shortest_path_algorithms.hpp"
#include "graphs/generate_graphs.hpp"
#include "graphs/adjacency_list_graph.hpp"
#include "graphs/adjacency_matrix_graph.hpp"
#include <vector>



int main(int argc, char* argv[])
{   

    std::fstream os;
    os.open("pomiary.txt", std::ios_base::out);
    os.close();
    os.open("pomiary.txt", std::ios_base::out);


    Timer timer;
    bool BF;
    std::vector<int> Verticies = {10, 50, 100, 500, 1000}; //Parametry podane w intrukcji
    std::vector<int> Density = {100, 75, 50, 25};

    //nazwy plików z tylko dodatnimi kosztami
    std::vector<std::vector<std::string>>file_names = {{"graph_10_100.txt", "graph_10_75.txt", "graph_10_50.txt", "graph_10_25.txt"},
                                                        {"graph_50_100.txt", "graph_50_75.txt", "graph_50_50.txt", "graph_50_25.txt"},
                                                        {"graph_100_100.txt", "graph_100_75.txt", "graph_100_50.txt", "graph_100_25.txt"},
                                                        {"graph_500_100.txt", "graph_500_75.txt", "graph_500_50.txt", "graph_500_25.txt"},
                                                        {"graph_1000_100.txt", "graph_1000_75.txt", "graph_1000_50.txt", "graph_1000_25.txt"},
                                                        };

    //nazwy plików gdzie występują ujemne koszty
    std::vector<std::vector<std::string>>file_names_N = {{"graph_N_10_100.txt", "graph_N_10_75.txt", "graph_N_10_50.txt", "graph_N_10_25.txt"},
                                                        {"graph_N_50_100.txt", "graph_N_50_75.txt", "graph_N_50_50.txt", "graph_N_50_25.txt"},
                                                        {"graph_N_100_100.txt", "graph_N_100_75.txt", "graph_N_100_50.txt", "graph_N_100_25.txt"},
                                                        {"graph_N_500_100.txt", "graph_N_500_75.txt", "graph_N_500_50.txt", "graph_N_500_25.txt"},
                                                        {"graph_N_1000_100.txt", "graph_N_1000_75.txt", "graph_N_1000_50.txt", "graph_N_1000_25.txt"},
                                                        };

    generate_parameters(Verticies, Density, file_names, file_names_N); // Wygenerowanie plików z grafami
    

    // Pomiar czasu działania wszystkich możliwych konfiguracji zadania

    std::cout<<"Duration of Dijkstra algorithm with adjacency Matrix:"<<std::endl<<std::endl;
    for(int i = 0; i < Density.size(); i++)                              
    {
        for (int j = 0; j < Verticies.size(); j++)
        {
            std::ifstream inputStream{file_names[j][i]};
            auto graph = AdjacencyMatrixGraph::createGraph(inputStream);
            int sourceIndex;
            inputStream >> sourceIndex;
            ShortestPathResult result;

            std::cout<<"Verticies: "<<Verticies[j]<<", Graph density: "<<Density[i]<<std::endl;
            timer.start();
            dijkstra(*graph, sourceIndex, result);
            timer.stop();
            os<<timer.msInterval()<<std::endl;
            std::cout << "time: " << timer.msInterval() <<"ms"<< std::endl<<std::endl;
        }
        os<<std::endl;
    }

    os<<std::endl;
    std::cout<<std::endl<<std::endl<<"Duration of Dijkstra algorithm with adjacency List:"<<std::endl<<std::endl;
    for(int i = 0; i < Density.size(); i++)                              
    {
        for (int j = 0; j < Verticies.size(); j++)
        {
            std::ifstream inputStream{file_names_N[j][i]};
            auto graph = AdjacencyListGraph::createGraph(inputStream);
            int sourceIndex;
            inputStream >> sourceIndex;
            ShortestPathResult result;

            std::cout<<"Verticies: "<<Verticies[j]<<", Graph density: "<<Density[i]<<std::endl;
            timer.start();
            dijkstra(*graph, sourceIndex, result);
            timer.stop();
            os<<timer.msInterval()<<std::endl;
            std::cout << "time: " << timer.msInterval() <<"ms"<< std::endl<<std::endl;
        }
        os<<std::endl;
    }

    os<<std::endl;
    std::cout<<"Duration of Bellman-Ford algorithm with adjacency Matrix:"<<std::endl<<std::endl;
    for(int i = 0; i < Density.size(); i++)                              
    {
        for (int j = 0; j < Verticies.size(); j++)
        {
            std::ifstream inputStream{file_names_N[j][i]};
            auto graph = AdjacencyMatrixGraph::createGraph(inputStream);
            int sourceIndex;
            inputStream >> sourceIndex;
            ShortestPathResult result;

            std::cout<<"Verticies: "<<Verticies[j]<<", Graph density: "<<Density[i]<<std::endl;
            timer.start();
            BF=bellmanFord(*graph, sourceIndex, result);
            timer.stop();
            if(BF==true)
            {
                os<<timer.msInterval()<<std::endl;
                std::cout << "time: " << timer.msInterval() <<"ms"<< std::endl<<std::endl;
            }
            else
            std::cout << "time: " << timer.msInterval() <<"ms   "<<"Negative circle"<< std::endl<<std::endl;
        }
        os<<std::endl;
    }

    os<<std::endl;
    std::cout<<"Duration of Bellman-Ford algorithm with adjacency List:"<<std::endl<<std::endl;
    for(int i = 0; i < Density.size(); i++)                              
    {
        for (int j = 0; j < Verticies.size(); j++)
        {
            std::ifstream inputStream{file_names_N[j][i]};
            auto graph = AdjacencyListGraph::createGraph(inputStream);
            int sourceIndex;
            inputStream >> sourceIndex;
            ShortestPathResult result;

            std::cout<<"Verticies: "<<Verticies[j]<<", Graph density: "<<Density[i]<<std::endl;
            timer.start();
            BF=bellmanFord(*graph, sourceIndex, result);
            timer.stop();
            if(BF==true)
            {
                os<<timer.msInterval()<<std::endl;
                std::cout << "time: " << timer.msInterval() <<"ms"<< std::endl<<std::endl;
            }
            else
            std::cout <<"Negative circle"<< std::endl<<std::endl;
        }
        os<<std::endl;
    }

    os.close();  
    return 0;
}
