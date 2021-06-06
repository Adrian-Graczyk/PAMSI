#ifndef BOT_HPP_
#define BOT_HPP_
#include <vector>
#include <memory>
#include "game/board.hpp"

//klasa węzła tworzącego drzewo rozwiązań
class Node {
    public:
    Moves moves;
    Fields fields;
    std::vector< Node > childs{};
    bool color;
    Board board;
    int value;
    
    Node( int depth, Board board_, bool color_, Fields fields_ = Fields(0,0,0,0) );
};

int max(int a, int b);

int min(int a, int b);

int min_max(Node& node, int depth, bool isMaximizingPlayer, int alpha, int beta);

//Funkcja zwracające najlepszy możliwy ruch wybrany 
//algorytmem min_max
Fields choose_best_move(int max_depth, Board board);

#endif /* GAME_BOT_HPP_ */
