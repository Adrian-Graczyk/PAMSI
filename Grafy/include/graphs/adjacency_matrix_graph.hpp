#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>
#include <vector>

#include "graphs/graph.hpp"

class AdjacencyMatrixGraph : public Graph
{
  public:
  std::vector<std::vector<int>> Matrix;
  
  static std::unique_ptr<Graph> createGraph(std::istream& is);
  
  //metody przesłaniające odpowiednie metody wirtualne z klasy bazowej Graph
  virtual void Find_path_Dijkstra(std::vector<int>& cost, std::vector<bool>& sets, std::vector<int>& path) override;
  virtual void Find_path_Bellman_Ford(std::vector<int>& cost, std::vector<bool>& sets, std::vector<int>& path) override;
  virtual bool Check_Negative(std::vector<int>& cost) override;

};

std::ostream& operator<<(std::ostream& os, const AdjacencyMatrixGraph& Matrix);

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
