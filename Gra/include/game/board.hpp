#ifndef BOARD_HPP_
#define BOARD_HPP_
#include <vector>
//#include "game/bot.hpp"

struct Field {
    int x;
    int y;

    Field(int x_n, int y_n);
    Field();
};

struct Fields {
    int x;
    int y;
    int x1=999;
    int y1=999;
    int captured_value;
    std::vector< Field > Captured_Fields;

    Fields (int x_n, int y_n, int x1_n, int y1_n);
    Fields ();
};

struct Moves {
    std::vector< Fields > fields;

    Moves(int x_n, int y_n, int x1_n, int y1_n);
    Moves(Fields fields);
    Moves();

    void add(int x_n, int y_n, int x1_n, int y1_n);
    void add_captured(int x_n, int y_n);
};

class Board
{
  public:
    bool chosen_fields[8][8];
    bool possible_fields[8][8];
    int board[8][8];
    bool if_pawn_chosen=false;
    bool if_field_chosen=false;
    bool possible_capture=false;
    bool color_=true;
    int x=0,y=0,x1=0,y1=0,x_captured=0,y_captured=0,chosen_pawn;
    int tie_count=0, white, black;

    //inicjalizacja planszy
    void init();

    //void execGame();
    void reset_possible_moves();

    void move_pawn();

    //usunięcie wyborów gracza/bota po wykonaniu ruchu
    void clear_choices();

    //usunięcie wyborów gracza po wciśnięciu prawego przycisku myszy
    void clear_choices_right_click();

    //Zwrócenie wszystkich dostępnych ruchów danego koloru
    Moves Get_All_Possible_Moves();
    
    //Sprawdzenie dostępnych ruchów dla danego pionka
    void check_possible_moves(int x, int y, Moves &moves, bool color);

    //Sprawdzenie czy jest możliwe zbicie dla danego pionka
    bool Check_Possible_Capture(int x, int y, bool color);

    //Sprawdzenie czy jest możliwe zbicie dla danego koloru
    bool Check_Possible_Capture_(bool color);

    //Dodanie do klasy moves wszystkich możliwych zbić
    void Get_Capture_Moves(int x, int y, int moves_count, bool color, Moves &moves, Fields &fields_);

    //zbicie z użyciem współrzędnych
    void Capture(int x, int y, int x_c, int y_c, int x1, int y1);

    //zbicie z użyciem struktury moves
    void Capture_all(Moves moves);

    //zbicie z użyciem struktury Fields
    void Capture_all_From_Fields(Fields fields);
    
    //ocena aktualnego stanu planszy
    int Evaluate_Board();

    //Sprawdzenie aktualnego stanu gry
    int Check_End_Game();
};

#endif /* GAME_BOARD_HPP_ */
