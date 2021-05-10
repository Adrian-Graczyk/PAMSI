#ifndef GENERATE_GRAPHS_HPP_
#define GENERATE_GRAPHS_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h> 
#include <time.h> 
#include "graphs/shortest_path_algorithms.hpp"
#include "graphs/generate_graphs.hpp"
#include "graphs/adjacency_list_graph.hpp"
#include "graphs/adjacency_matrix_graph.hpp"

void generate_parameters(std::vector<int> Verticies, std::vector<int> Density, std::vector<std::vector<std::string>>file_names, std::vector<std::vector<std::string>>file_names_N);
void generate_and_save(int Vertices, int Edges, std::string file_name);
void generate_and_save_negative(int Vertices, int Edges, std::string file_name);

#endif /* GENERATE_GRAPHS_HPP_ */
