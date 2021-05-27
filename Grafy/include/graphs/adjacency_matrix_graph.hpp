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
  virtual int get_Weight(int i, int j) override;
  std::vector<int> neighbours(int i) override;
  virtual bool check_zero(int i, int j) override;
  
};

std::ostream& operator<<(std::ostream& os, const AdjacencyMatrixGraph& Matrix);

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
