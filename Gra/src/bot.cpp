#include "game/bot.hpp"
#include <iostream>



Node::Node( int depth, Board board_,bool color_, Fields fields_ ) 
{
    color = color_;
    board = board_;
    fields = fields_;
    value = 0;

    if(depth==0)
    value = board.Evaluate_Board();
    
    if(depth!=0)
    {
        Moves moves;
        board.possible_capture=board.Check_Possible_Capture_(board.color_);
        moves = board.Get_All_Possible_Moves();

        //dla każdego dostępnego ruchu - wykonaj go oraz 
        //stwórz nowy węzeł z kopią planszy po tym ruchu
        for ( auto& k : moves.fields) 
        {   
            Board Board_copy = board;
            Board_copy.x = k.x;
            Board_copy.x1 = k.x1;
            Board_copy.y = k.y;
            Board_copy.y1 = k.y1;
            Board_copy.chosen_fields[k.x][k.y]=true;
            Board_copy.if_pawn_chosen=true;
            Board_copy.chosen_pawn=Board_copy.board[k.x][k.y];
            Board_copy.chosen_fields[k.x1][k.y1]=true;
            Board_copy.if_field_chosen=true;
            Board_copy.move_pawn();
            Board_copy.Capture_all_From_Fields(k);
            Board_copy.clear_choices();
            Board_copy.possible_capture=Board_copy.Check_Possible_Capture_(Board_copy.color_);
            Node Child(depth-1, Board_copy, Board_copy.color_, k);
            childs.push_back(Child);
        }
    }
}

int min_max( Node& node, int depth, bool isMaximizingPlayer, int alpha, int beta ) 
{
    int i=0;

    if(node.childs.size() == 0)
        return node.value;

    int value, minEval, maxEval;

    if(isMaximizingPlayer) 
    {
        maxEval = -100000;
        for ( auto& child : node.childs ) 
        {
            value = min_max(child, depth+1, false, alpha, beta);
            maxEval = max( maxEval, value);
            if (maxEval == value && depth == 0)
                node.fields = child.fields;
            alpha = max(alpha, minEval);
            if (beta <= alpha)
                break;
        }
        return maxEval;
    } 
    else 
    {
        minEval = 100000; 
        for ( auto& child : node.childs ) 
        {  
            value = min_max(child, depth+1, true, alpha, beta);
            minEval = min( minEval, value );
            if (minEval == value && depth == 0)
                node.fields = child.fields;
            beta = min(beta, minEval);
            if (beta <= alpha) 
                break;
        }
        return minEval;
    }   
}

int max(int a, int b) 
{
    if(a < b)
    return b;
    else
    return a;    
}

int min(int a, int b) 
{
    if(a < b)
    return a;
    else
    return b; 
}


//Funkcja zwracające najlepszy możliwy ruch wybrany algorytmem min_max
Fields choose_best_move(int max_depth, Board board)
{
    Node Tree(max_depth, board, false);
    int best_value=min_max( Tree, 0, false, -100000, 100000 );
    return Tree.fields;
}
