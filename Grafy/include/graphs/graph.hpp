#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include <vector>
#include <memory>
#include <filesystem>
#include <fstream>
#include <iostream>


class Graph
{
  public:
  std::vector<std::vector<int>> graph;
  int Vertex_Quantity;
  int Edge_Quantity;

  Graph createGraph(std::istream& is);

  virtual void Find_path_Dijkstra(std::vector<int>& cost, std::vector<bool>& sets, std::vector<int>& path);
  virtual void Find_path_Bellman_Ford(std::vector<int>& cost, std::vector<bool>& sets, std::vector<int>& path);
  virtual bool Check_Negative(std::vector<int>& cost);
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);

#endif /* GRAPH_HPP_ */
