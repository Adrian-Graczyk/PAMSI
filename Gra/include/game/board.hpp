#ifndef BOARD_HPP_
#define BOARD_HPP_
#include <vector>

struct Field{
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

    void init();
    void execGame();
    void move_pawn();
    void clear_choices();
    void reset_possible_moves();
    void Capture(int x, int y, int x_c, int y_c, int x1, int y1);
    void Capture_all(Moves moves);
    void Get_Capture_Moves(int x, int y, bool color, Moves &moves, Fields &fields_);
    void check_possible_moves(int x, int y, Moves &moves, bool color);
    bool Check_Possible_Capture(int x, int y, bool color);
    bool Check_Possible_Capture_(bool color);


  private:
};

#endif /* GAME_BOARD_HPP_ */
