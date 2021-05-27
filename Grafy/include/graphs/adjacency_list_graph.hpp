#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <memory>

#include "graphs/graph.hpp"

struct Graph_Connection
{
  int EndVertexIndex;
  int cost;

  public:
  Graph_Connection(int Cost, int End);
  Graph_Connection(){}
};

class AdjacencyListGraph : public Graph
{
  public:
  std::vector<std::vector<Graph_Connection>> List;

  static std::unique_ptr<Graph> createGraph(std::istream& is);

  //metody przesłaniające odpowiednie metody wirtualne z klasy bazowej Graph
  virtual int get_Weight(int i, int j) override;
  std::vector<int> neighbours(int i) override;
  virtual bool check_zero(int i, int j) override;
  
};

std::ostream& operator<<(std::ostream& os, const AdjacencyListGraph& List);


#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
