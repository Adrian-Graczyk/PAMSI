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

  virtual void Find_path_Dijkstra(std::vector<int>& cost, std::vector<bool>& sets, std::vector<int>& path) override;
  virtual void Find_path_Bellman_Ford(std::vector<int>& cost, std::vector<bool>& sets, std::vector<int>& path) override;
  virtual bool Check_Negative(std::vector<int>& cost) override;
};

std::ostream& operator<<(std::ostream& os, const AdjacencyListGraph& List);


#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
