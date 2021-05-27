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
  virtual int get_Weight(int i, int j);
  virtual bool check_zero(int i, int j);
  virtual std::vector<int> neighbours(int i);
  
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);

#endif /* GRAPH_HPP_ */
