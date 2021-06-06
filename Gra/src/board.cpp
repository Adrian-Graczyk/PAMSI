#include "game/board.hpp"

#define Empty 0
#define White_Pawn 1
#define Black_Pawn 2
#define White_King 3
#define Black_King 4

////////////////////////// Metody struktury Moves
Moves::Moves(int x_n, int y_n, int x1_n, int y1_n) 
{
    Fields field(x_n, y_n, x1_n, y1_n);
    fields.push_back(field);
}

Moves::Moves()
{
    std::vector< Fields > fields;
}

void Moves::add(int x_n, int y_n, int x1_n, int y1_n)
{
    Fields fields_n(x_n, y_n, x1_n, y1_n);
    fields.push_back(fields_n);
}

void Moves::add_captured(int x_n, int y_n)
{
    Field field_n(x_n, y_n);
}

////////////////// Metody struktury Fields
Fields::Fields (int x_n, int y_n, int x1_n, int y1_n) 
{
    x = x_n;
    y = y_n;
    x1 = x1_n;
    y1 = y1_n;
}

Fields::Fields () 
{
    x = 0;
    y = 0;
    x1 = 0;
    y1 = 0;
}

////////////////// Metody struktury Field
Field::Field(int x_n, int y_n) 
{
    x = x_n;
    y = y_n;
}

Field::Field() 
{
    x = 0;
    y = 0;
}

////////////////// Metody klasy Board


//inicjalizacja planszy
void Board::init()
{
    for ( int i = 0; i < 8; i++ ) 
        for ( int j = 0; j < 8; j++ )
            chosen_fields[i][j] = false; 

    for ( int i = 0; i < 8; i++ ) 
        for ( int j = 0; j < 8; j++ )
            possible_fields[i][j] = false; 

    for ( int i = 0; i < 8; i++ ) 
    {
        for ( int j = 0; j < 8; j++ ) 
        {
            if(i==0||i==1||i==2)
            {
                if(i%2==0 && j%2!=0)
                board[i][j]=Black_Pawn;
                if(i%2!=0 && j%2==0)
                board[i][j]=Black_Pawn;
            }
            else if(i==5||i==6||i==7)
            {
                if(i%2==0 && j%2!=0)
                board[i][j]=White_Pawn;
                if(i%2!=0 && j%2==0)
                board[i][j]=White_Pawn;
            }
            else board[i][j]=Empty;      
        }
    }
    color_=true;
}

void Board::reset_possible_moves()
{
    for ( int i = 0; i < 8; i++ ) 
        for ( int j = 0; j < 8; j++ )
            possible_fields[i][j] = false; 
}

void Board::move_pawn()
{
    board[x][y] = Empty;
    board[x1][y1] = chosen_pawn;

    if_pawn_chosen = false;
    if_field_chosen = false;

    if(x1==0 && chosen_pawn==White_Pawn)
    board[x1][y1]=White_King;

    if(x1==7 && chosen_pawn==Black_Pawn)
    board[x1][y1]=Black_King;


    if(color_==true)
    {
        color_=false;
    }
    else
    {
        color_=true;
    }
}

//usunięcie wyborów gracza/bota po wykonaniu ruchu
void Board::clear_choices()
{
    chosen_fields[x][y]=false;
    chosen_fields[x1][y1]=false;
    x = 0;
    x1 = 0;
    y = 0;
    y1 = 0;
    possible_capture=false;
    for ( int i = 0; i < 8; i++ )
    {
        for ( int j = 0; j < 8; j++ )
        {
            chosen_fields[i][j] = false; 
            possible_fields[i][j] = false;
        }
    }
}

//usunięcie wyborów gracza po wciśnięciu prawego przycisku myszy
void Board::clear_choices_right_click()
{
    chosen_fields[x][y]=false;
    chosen_fields[x1][y1]=false;
    if_pawn_chosen = false;
    if_field_chosen = false;
    x = 0;
    x1 = 0;
    y = 0;
    y1 = 0;
}

//Zwrócenie wszystkich dostępnych ruchów danego koloru
Moves Board::Get_All_Possible_Moves()
{
    Moves moves;
    for ( int i = 0; i < 8; i++ ) 
    {
        for ( int j = 0; j < 8; j++ ) 
        {
            if(color_)
            {
                if(board[i][j]==White_Pawn || board[i][j]==White_King)
                check_possible_moves(i, j, moves, color_);
            }
            else
            {
                if(board[i][j]==Black_Pawn || board[i][j]==Black_King)
                check_possible_moves(i, j, moves, color_);
            }
        }
    }
    return moves;
}

//Sprawdzenie dostępnych ruchów dla danego pionka
void Board::check_possible_moves(int x, int y, Moves &moves, bool color)
{
    if(possible_capture)
    {
        if(Check_Possible_Capture(x, y, color))
        {
            Fields fields_;
            Get_Capture_Moves(x, y, 0, color, moves, fields_);
        }
    }
    else
    {
        // Pawns
        if(board[x][y]==White_Pawn || board[x][y]==Black_Pawn)
        {
            if(color)
            {   
                if ( y > 0 && x > 0)
                if(board[x-1][y-1]==Empty)
                moves.add(x,y,x-1,y-1);
                if ( y < 7 && x > 0)
                if(board[x-1][y+1]==Empty)
                moves.add(x,y,x-1,y+1);
            }
            else
            {   
                if ( y > 0 && x < 7)
                if(board[x+1][y-1]==Empty)
                moves.add(x,y,x+1,y-1);
                if ( y < 7 && x < 7)
                if(board[x+1][y+1]==Empty)
                moves.add(x,y,x+1,y+1);
            }
        }

        //Kings
        if(board[x][y]==White_King || board[x][y]==Black_King)
        {
            for ( int a : {-1, 1} ) 
            {
                for ( int b : {-1, 1} ) 
                {
                    int i = x + a;
                    int j = y + b;
                    // move until there is an obstacle on a path
                    while ( i >= 0 && j >= 0 && i <= 7 && j <= 7 ) 
                    {
                        //if not capturing add those moves
                        if ( board[i][j] == Empty ) 
                        {
                            moves.add(x,y,i,j);
                        } 
                        else if ( color ) 
                        {
                            // break if an ally on path
                            if ( board[i][j] == White_Pawn || board[i][j] == White_King)
                                break;
                        } 
                        else 
                        {
                            // break if an ally on path
                            if (board[i][j] == Black_Pawn || board[i][j] == Black_King)
                                break;
                        }
                        i += a;
                        j += b;
                }   }
            }
        
        }
    } 
}

//Sprawdzenie czy jest możliwe zbicie dla danego pionka
bool Board::Check_Possible_Capture(int x, int y, bool color) 
{
    // Pawns
    if ( board[x][y] == White_Pawn || board[x][y] == Black_Pawn) 
    {
        for ( int a : {-1, 1} ) 
        {
            for ( int b : {-1, 1} ) 
            {
                int i = x + a;
                int j = y + b;

                if (i+a < 8 && i+a >= 0 && j+b < 8 && j+b >= 0) 
                {
                    if (color) 
                    {
                        if (board[i][j] == Black_Pawn || board[i][j] == Black_King)
                            if (board[i+a][j+b] == Empty)
                                return true;
                    } 
                    else 
                    {
                        if (board[i][j] == White_Pawn || board[i][j] == White_King)
                            if (board[i+a][j+b] == Empty)
                                return true;
                    }
                }
            }
        }
    }
    // Kings
    if ( board[x][y] == White_King || board[x][y] == Black_King) 
    {
        for ( int a : {-1, 1} ) 
        {
            for ( int b : {-1, 1} ) 
            {
                int i = x + a;
                int j = y + b;

                while(i+a < 8 && i+a >= 0 && j+b < 8 && j+b >= 0) 
                {
                    if (color) 
                    {
                        if (board[i][j] == Black_Pawn || board[i][j] == Black_King)
                            if (board[i+a][j+b] == Empty)
                                return true;
                            else
                                break;
                        if (board[i][j] == White_Pawn || board[i][j] == White_King)
                            break;
                    } 
                    else 
                    {
                        if (board[i][j] == White_Pawn || board[i][j] == White_King)
                            if (board[i+a][j+b] == Empty)
                                return true;
                            else
                                break;
                        if (board[i][j] == Black_Pawn || board[i][j] == Black_King)
                            break;
                    }
                    i=i+a;
                    j=j+b;
                }
            }
        }
    }
    return false;
}

//Sprawdzenie czy jest możliwe zbicie dla danego koloru 
bool Board::Check_Possible_Capture_(bool color)
{
    for ( int i = 0; i < 8; i++ ) 
    {
        for ( int j = 0; j < 8; j++ ) 
        {
            if(color)
            {
                if(board[i][j] == White_Pawn || board[i][j] == White_King)
                if(Check_Possible_Capture(i,j,color))
                return true;
            }
            else
            {
                if(board[i][j] == Black_Pawn || board[i][j] == Black_King)
                if(Check_Possible_Capture(i,j,color))
                return true;
            }
        }
    }
    return false;
}

//Dodanie do klasy moves wszystkich możliwych zbić
void Board::Get_Capture_Moves(int x, int y, int moves_count, bool color, Moves &moves, Fields &fields_) 
{   
    int moves_done=moves_count;
    // Pawns
    if(board[x][y] == White_Pawn || board[x][y] == Black_Pawn)
    {
        for ( int a : {-1, 1} ) 
        {
            for ( int b : {-1, 1} ) 
            {
                Board Board_copy = *this;
                int i = x + a;
                int j = y + b;
                if (i+a < 8 && i+a >= 0 && j+b < 8 && j+b >= 0) 
                {
                    if (color) 
                    {
                        if ( board[i][j] == Black_Pawn || board[i][j] == Black_King)
                            if ( board[i+a][j+b] == Empty)
                            {
                                Field field_n(i,j);
                                fields_.Captured_Fields.push_back(field_n);
                                Board_copy.Capture(x, y, i, j, i+a, j+b);
                                if(Board_copy.Check_Possible_Capture(i+a,j+b, color))
                                {
                                    Board_copy.Get_Capture_Moves(i+a, j+b, moves_done+1, color, moves, fields_);
                                }
                                else
                                {
                                    fields_.x=x;
                                    fields_.y=y;
                                    fields_.x1=i+a;
                                    fields_.y1=j+b;
                                    moves.fields.push_back(fields_);
                                }
                            }
                    }
                    else 
                    {
                        if ( board[i][j] == White_Pawn || board[i][j] == White_King)
                        {
                            if ( board[i+a][j+b] == Empty )
                            {   
                                Field field_n(i,j);
                                fields_.Captured_Fields.push_back(field_n);
                                Board_copy.Capture(x, y, i, j, i+a, j+b);
                                if(moves_done==0)
                                {
                                    fields_.x=x;
                                    fields_.y=y;
                                }
                                if(Board_copy.Check_Possible_Capture(i+a,j+b, color))
                                {
                                    Board_copy.Get_Capture_Moves(i+a, j+b, moves_done+1, color, moves, fields_);
                                }
                                else
                                {
                                    
                                    fields_.x1=i+a;
                                    fields_.y1=j+b;
                                    moves.fields.push_back(fields_);
                                }
                            }
                        }   
                    }
                }
            }
        }
    }

    // Kings
    if(board[x][y] == White_King || board[x][y] == Black_King)
    {
        for ( int a : {-1, 1} ) 
        {
            for ( int b : {-1, 1} ) 
            {
                Board Board_copy = *this;
                int i = x + a;
                int j = y + b;
                while (i+a < 8 && i+a >= 0 && j+b < 8 && j+b >= 0) 
                {
                    if (color) 
                    {
                        if ( board[i][j] == Black_Pawn || board[i][j] == Black_King)
                            if ( board[i+a][j+b] == Empty)
                            {
                                Field field_n(i,j);
                                fields_.Captured_Fields.push_back(field_n);
                                Board_copy.Capture(x, y, i, j, i+a, j+b);
                                if(Board_copy.Check_Possible_Capture(i+a,j+b, color))
                                {
                                    Board_copy.Get_Capture_Moves(i+a, j+b, moves_done+1, color, moves, fields_);
                                }
                                else
                                {
                                    while (i+a < 8 && i+a >= 0 && j+b < 8 && j+b >= 0) 
                                    {   
                                        if(board[i+a][j+b]!=Empty)
                                        break;
                                        else
                                        {
                                            fields_.x=x;
                                            fields_.y=y;
                                            fields_.x1=i+a;
                                            fields_.y1=j+b;
                                            moves.fields.push_back(fields_);
                                        }
                                        i += a;
                                        j += b;
                                    }
                                }
                            }
                    }
                    else 
                    {
                        if ( board[i][j] == White_Pawn || board[i][j] == White_King)
                        {
                            if ( board[i+a][j+b] == Empty )
                            {   
                                Field field_n(i,j);
                                fields_.Captured_Fields.push_back(field_n);
                                Board_copy.Capture(x, y, i, j, i+a, j+b);
                                if(Board_copy.Check_Possible_Capture(i+a,j+b, color))
                                {
                                    Board_copy.Get_Capture_Moves(i+a, j+b, moves_done+1, color, moves, fields_);
                                }
                                else
                                {
                                    while (i+a < 8 && i+a >= 0 && j+b < 8 && j+b >= 0) 
                                    {
                                        if(board[i+a][j+b]!=Empty)
                                        break;
                                        else
                                        {
                                            fields_.x=x;
                                            fields_.y=y;
                                            fields_.x1=i+a;
                                            fields_.y1=j+b;
                                            moves.fields.push_back(fields_);
                                        }
                                        i += a;
                                        j += b;
                                    }
                                }
                            }
                        }   
                    }
                    i += a;
                    j += b;
                }
            }
        }
    }   
    
}


//zbicie z użyciem współrzędnych
void Board::Capture(int x, int y, int x_c, int y_c, int x1, int y1) 
{
    board[x1][y1]=board[x][y];
    board[x][y]=Empty;
    board[x_c][y_c]=Empty;
}

//zbicie z użyciem struktury moves
void Board::Capture_all(Moves moves)
{
    for(auto &i : moves.fields)
    {
        for(auto &j : i.Captured_Fields)
        {
            if(i.x1==x1 && i.y1==y1)
            board[j.x][j.y]=Empty;
        }
    }
}

//zbicie z użyciem struktury Fields
void Board::Capture_all_From_Fields(Fields fields)
{
    for(auto &i : fields.Captured_Fields)
        {
            board[i.x][i.y]=Empty;
        }
}


//ocena aktualnego stanu planszy
int Board::Evaluate_Board()
{
    int value=0, score_w=0, score_b=0;
    
    for ( int i = 0; i < 8; i++ ) 
    {
        for ( int j = 0; j < 8; j++ ) 
        {
            if(board[i][j]==White_Pawn)
            {
                //if(Check_Possible_Capture(i,j, color_))
                    //score_w +=2;

                score_w += 20;
                if ( i == 7 ) 
                    score_w -=5;
                if ( i == 6 ) 
                    score_w -=2;
                if ( i == 5 )
                    score_w -=1;
                
            
                if ( j < 2 || j > 5 ) 
                {
                    score_w ++;
                    if ( j < 1 || j > 6 )
                        score_w ++;
                }
            }

            if(board[i][j]==White_King)
            {
               // if(Check_Possible_Capture(i,j, color_))
                  //  score_w +=2;

                score_w += 30;
                if ( j < 2 || j > 5 ) 
                {
                    score_w ++;
                    if ( j < 1 || j > 6 )
                        score_w ++;
                }
            }

            if(board[i][j]==Black_Pawn)
            {
                //if(Check_Possible_Capture(i,j, color_))
                  //  score_b +=2;

                score_b += 20;
                if ( i == 0 ) 
                    score_b -=5;
                if ( i == 1 ) 
                    score_b -=2;
                if ( i == 2 )
                    score_b --;
            
        
                if ( j < 2 || j > 5 ) 
                {
                    score_b ++;
                    if ( j < 1 || j > 6 )
                        score_b ++;
                }
            }

            if(board[i][j]==Black_King)
            {
                //if(Check_Possible_Capture(i,j, color_))
                  //  score_b +=2;

                score_b += 30;
                if ( j < 2 || j > 5 ) 
                {
                score_b ++;
                if ( j < 1 || j > 6 )
                    score_b ++;
                }
            } 
        }   
    }

    if(color_)
        value=score_b-score_w;
    else
        value=score_w-score_b;

    return value;
}

//Sprawdzenie aktualnego stanu gry
//wygrana białych 1
//wygrana czarnyh 2
//remis -1
int Board::Check_End_Game()
{
    int black_now=0, white_now=0;

    for ( int i = 0; i < 8; i++ ) 
    {
        for ( int j = 0; j < 8; j++ ) 
        {
            if(board[i][j]==White_Pawn || board[i][j]==White_King)
                white_now++;

            if(board[i][j]==Black_Pawn || board[i][j]==Black_King)
                black_now++;
        }
    }

    if(black_now==0)
    return 1;

    if(white_now==0)
    return 2;

    if(black_now==black && white_now==white)
    tie_count++;
    else
    tie_count=0;

    if(tie_count==15)
    return -1;

    black=black_now;
    white=white_now;

    return 0;
}