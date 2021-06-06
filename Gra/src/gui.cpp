#include "game/gui.hpp"
#include <iostream>

#define Empty 0
#define White_Pawn 1
#define Black_Pawn 2
#define White_King 3
#define Black_King 4
#define Hard_Difficulty 8
#define Medium_Difficulty 6
#define Easy_Difficulty 1


Gui::Gui()
{
    
}
Board board;
bool color_=true;


bool Gui::init()
{
    board.init();

    int rendererFlags = SDL_RENDERER_ACCELERATED, windowFlags = 0;
    constexpr auto SCREEN_WIDTH = 1280;
    constexpr auto SCREEN_HEIGHT = 1024;

    if(SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
    {
        return false;
    }

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              windowFlags);

    if(!window)
    {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    surface = SDL_GetWindowSurface(window);

    font = TTF_OpenFont("../data/zai_DrukarniaPolska.ttf", 42);
    font_big = TTF_OpenFont("../data/zai_DrukarniaPolska.ttf", 220);
    black_king = SDL_LoadBMP("../data/black_king.bmp");
    black_pawn = SDL_LoadBMP("../data/black_pawn.bmp");
    white_king = SDL_LoadBMP("../data/white_king.bmp");
    white_pawn = SDL_LoadBMP("../data/white_pawn.bmp");
    frame = SDL_LoadBMP("../data/frame.bmp");
    dark_field = SDL_LoadBMP("../data/dark_field.bmp");
    board_texture = SDL_LoadBMP("../data/board.bmp");
    desk = SDL_LoadBMP("../data/desk.bmp");

    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 164,116,73));
    SDL_Rect deskRect = {0, 0, 60, 60};
    SDL_BlitSurface(desk, nullptr, surface, &deskRect);
    SDL_Color fontColor = {255, 255, 255};
    SDL_Surface* text = TTF_RenderText_Blended(font, "CHECKERS", fontColor);
    SDL_Rect textRect = {550, 15, text->w, text->h};
    SDL_BlitSurface(text, nullptr, surface, &textRect);
    SDL_FreeSurface(text);

    return surface && font;
}

void Gui::execGame()
{
    gameIsRunning = true;
    
    while(gameIsRunning)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {   
            //Ruch bota
            if(board.color_== false && enable_player_vs_player==false)
            {
                Moves moves;
                Fields best_fields;
                best_fields=choose_best_move(difficulty, board);
                board.x = best_fields.x;
                board.x1 = best_fields.x1;
                board.y = best_fields.y;
                board.y1 = best_fields.y1;
                board.chosen_fields[board.x][board.y]=true;
                board.if_pawn_chosen=true;
                board.chosen_pawn=board.board[board.x][board.y];
                board.chosen_fields[board.x1][board.y1]=true;
                board.if_field_chosen=true;
                board.move_pawn();
                board.Capture_all_From_Fields(best_fields);
                board.clear_choices();
                State_of_game=board.Check_End_Game();
                board.possible_capture=board.Check_Possible_Capture_(board.color_);
                color_=true;
            }
            else
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                        gameIsRunning = false;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        handleMouseButtonDown(event);
                        break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_RETURN)
                        {
                            // zatwierdzenie ruchu gracza jeśli nie wybrał punktu spoza planszy
                            if(board.x1==0 && board.y1==0){}
                            else
                            {
                                Moves moves;
                                board.check_possible_moves(board.x, board.y, moves, board.color_);
                                board.move_pawn();
                                board.Capture_all(moves);
                                board.clear_choices();
                                State_of_game=board.Check_End_Game();

                                // Sprawdzenie czy jest możliwe bicie w następnym ruchu
                                board.possible_capture=board.Check_Possible_Capture_(board.color_);
                            }
                        }
                        break;
                }
                color_= false;
            }
            
        }
        draw();
    }

    SDL_Quit();
    TTF_Quit();
}

void Gui::draw()
{
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 164,116,73));
    SDL_Rect deskRect = {0, 0, 60, 60};
    SDL_BlitSurface(desk, nullptr, surface, &deskRect);
    SDL_Rect boardRect = {0, 70, 60, 60};
    SDL_BlitSurface(board_texture, nullptr, surface, &boardRect);

    //rysowanie pionków oraz zaznaczonych pól
    for ( int i = 0; i < 8; i++ ) 
    {
        for ( int j = 0; j < 8; j++ ) 
        {

            if(board.board[i][j]==White_Pawn)
            {
                if(board.chosen_fields[i][j]==true || (board.possible_fields[i][j]==true && enable_possible_fields==true))
                {
                    SDL_Rect frameRect = {59+(102*j),131+(101*i), 60, 60};
                    SDL_BlitSurface(frame, nullptr, surface, &frameRect);
                }
                SDL_Rect imageRect = {63+(102*j),135+(101*i), 60, 60};
                SDL_BlitSurface(white_pawn, nullptr, surface, &imageRect);
            }
            else if(board.board[i][j]==Black_Pawn)
            {   
                if(board.chosen_fields[i][j]==true || (board.possible_fields[i][j]==true && enable_possible_fields==true))
                {
                    SDL_Rect frameRect = {59+(102*j),131+(101*i), 60, 60};
                    SDL_BlitSurface(frame, nullptr, surface, &frameRect);
                }
                SDL_Rect imageRect = {63+(102*j),135+(101*i), 60, 60};
                SDL_BlitSurface(black_pawn, nullptr, surface, &imageRect);
            }
            else if(board.board[i][j]==White_King)
            {   
                if(board.chosen_fields[i][j]==true || (board.possible_fields[i][j]==true && enable_possible_fields==true))
                {
                    SDL_Rect frameRect = {59+(102*j),131+(101*i), 60, 60};
                    SDL_BlitSurface(frame, nullptr, surface, &frameRect);
                }
                SDL_Rect imageRect = {63+(102*j),135+(101*i), 60, 60};
                SDL_BlitSurface(white_king, nullptr, surface, &imageRect);
            }
            else if(board.board[i][j]==Black_King)
            {   
                if(board.chosen_fields[i][j]==true || (board.possible_fields[i][j]==true && enable_possible_fields==true))
                {
                    SDL_Rect frameRect = {59+(102*j),131+(101*i), 60, 60};
                    SDL_BlitSurface(frame, nullptr, surface, &frameRect);
                }
                SDL_Rect imageRect = {63+(102*j),135+(101*i), 60, 60};
                SDL_BlitSurface(black_king, nullptr, surface, &imageRect);
            }
            else
            {
                if((board.chosen_fields[i][j]==true && (i+j)%2!=0) || (board.possible_fields[i][j]==true && enable_possible_fields==true))
                {
                    SDL_Rect frameRect = {59+(102*j),131+(101*i), 60, 60};
                    SDL_BlitSurface(frame, nullptr, surface, &frameRect);

                    SDL_Rect imageRect = {63+(102*j),135+(101*i), 60, 60};
                    SDL_BlitSurface(dark_field, nullptr, surface, &imageRect);
                }
            }
        }
    }

    draw_settings();

    

    SDL_UpdateWindowSurface(window);
}



void Gui::draw_possibilities(Moves moves)
{
    for(auto &i : moves.fields)
    {
        board.possible_fields[i.x1][i.y1]=true;
    }
}

void Gui::handleMouseButtonDown(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {   
        //wybranie pionka 
        if(board.if_pawn_chosen==false)
        {
            Moves moves;
            board.reset_possible_moves();
            Find_Field_with_pawn(event.button.x, event.button.y, board);
            board.check_possible_moves(board.x, board.y, moves, board.color_);
            draw_possibilities(moves);
        }
        //wybranie pola, do którego chcemy przesunąć pionka
        else if(board.if_field_chosen==false)
        {
            Find_Field_without_pawn(event.button.x, event.button.y, board);
        }

        change_settings(event.button.x, event.button.y);
    }

    //usunięcie wyboru złego pionka
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        board.clear_choices_right_click();
    }
    
}


// Sprawdzanie czy wybrane pole jest polem z dostępnym pionkiem i wybranie go
int Gui::Find_Field_with_pawn(int x, int y, Board &board)
{
    int pawn;
    for ( int i = 0; i < 8; i++ ) 
    {
        for ( int j = 0; j < 8; j++ ) 
        {
            if(x > 59+(102*j) && x < 161+(102*j) && 
               y > 131+(101*i) && y < 232+(101*i)
               && board.board[i][j]!=Empty)
            {
                if(board.color_)
                {
                    if(board.board[i][j]==White_Pawn || board.board[i][j]==White_King)
                    {
                        if(board.possible_capture)
                        {
                            if(board.Check_Possible_Capture(i, j, board.color_))
                            {
                                board.chosen_fields[i][j]=true;
                                board.x=i;
                                board.y=j;
                                board.if_pawn_chosen=true;
                                board.chosen_pawn=board.board[i][j];
                            }
                        }
                        else
                        {
                            board.chosen_fields[i][j]=true;
                            board.x=i;
                            board.y=j;
                            board.if_pawn_chosen=true;
                            board.chosen_pawn=board.board[i][j];
                        }
                    }
                }
                else
                {
                    if(board.board[i][j]==Black_Pawn || board.board[i][j]==Black_King)
                    {
                        if(board.possible_capture)
                        {
                            if(board.Check_Possible_Capture(i, j, board.color_))
                            {
                                board.chosen_fields[i][j]=true;
                                board.x=i;
                                board.y=j;
                                board.if_pawn_chosen=true;
                                board.chosen_pawn=board.board[i][j];
                            }
                        }
                        else
                        {
                            board.chosen_fields[i][j]=true;
                            board.x=i;
                            board.y=j;
                            board.if_pawn_chosen=true;
                            board.chosen_pawn=board.board[i][j];
                        }
                    }
                }
               
            }
        }
    }
    return pawn;
}

//Sprawdzenie czy wybrane pole jest możliwe do przesunięcia i wybranie go
void Gui::Find_Field_without_pawn(int x, int y, Board &board)
{
    for ( int i = 0; i < 8; i++ ) 
    {
        for ( int j = 0; j < 8; j++ ) 
        {
            if(x > 59+(102*j) && x < 161+(102*j) && 
               y > 131+(101*i) && y < 232+(101*i)
               && board.possible_fields[i][j]==true)
            {
                board.chosen_fields[i][j]=true;
                board.x1=i;
                board.y1=j;
                board.if_field_chosen=true;
            }  
        }
    }
}

// zmiana ustawień gry po wyborze gracza 
void Gui::change_settings(int x, int y)
{
    if(x > 1050 && x < 1200 && y > 170 && y < 220)
    difficulty=Easy_Difficulty;

    if(x > 1050 && x < 1200 && y > 240 && y < 290)
    difficulty=Medium_Difficulty;

    if(x > 1050 && x < 1200 && y > 310 && y < 360)
    difficulty=Hard_Difficulty;

    if(x > 1050 && x < 1200 && y > 500 && y < 550)
    enable_possible_fields=!enable_possible_fields;

    if(x > 970 && x < 1200 && y > 700 && y < 750)
    enable_player_vs_player=!enable_player_vs_player;

    if(x > 1050 && x < 1200 && y > 900 && y < 950)
    {
        board.init();
        board.clear_choices_right_click();
        board.clear_choices();
    }
    
}


//Wyświetlanie wybranych przez użytkownika ustawień gry
void Gui::draw_settings()
{
    SDL_Color fontColor_White = {255, 255, 255};
    SDL_Color fontColor_Black = {0, 0, 0};

    SDL_Color fontColor_Gray = {87, 89, 93};

    SDL_Surface* text2 = TTF_RenderText_Blended(font, "Easy", fontColor_White);
    SDL_Surface* text3 = TTF_RenderText_Blended(font, "Medium", fontColor_White);
    SDL_Surface* text4 = TTF_RenderText_Blended(font, "Hard", fontColor_Gray);
    SDL_Surface* text5 = TTF_RenderText_Blended(font, "Hints", fontColor_White);
    SDL_Surface* text6 = TTF_RenderText_Blended(font, "Player vs Player", fontColor_White);


    SDL_Surface* text1 = TTF_RenderText_Blended(font, "Difficulty:", fontColor_White);
    SDL_Rect textRect = {1020, 70, text1->w, text1->h};
    SDL_BlitSurface(text1, nullptr, surface, &textRect);
    SDL_FreeSurface(text1);

    if(difficulty==Easy_Difficulty)
    text2 = TTF_RenderText_Blended(font, "Easy", fontColor_White);
    else
    text2 = TTF_RenderText_Blended(font, "Easy", fontColor_Gray);
    textRect = {1050, 170, text2->w, text2->h};
    SDL_BlitSurface(text2, nullptr, surface, &textRect);
    SDL_FreeSurface(text2);

    if(difficulty==Medium_Difficulty)
    text3 = TTF_RenderText_Blended(font, "Medium", fontColor_White);
    else
    text3 = TTF_RenderText_Blended(font, "Medium", fontColor_Gray);
    textRect = {1050, 240, text3->w, text3->h};
    SDL_BlitSurface(text3, nullptr, surface, &textRect);
    SDL_FreeSurface(text3);

    if(difficulty==Hard_Difficulty)
    text4 = TTF_RenderText_Blended(font, "Hard", fontColor_White);
    else
    text4 = TTF_RenderText_Blended(font, "Hard", fontColor_Gray);
    textRect = {1050, 310, text4->w, text4->h};
    SDL_BlitSurface(text4, nullptr, surface, &textRect);
    SDL_FreeSurface(text4);

    if(enable_possible_fields)
    text5 = TTF_RenderText_Blended(font, "Hints", fontColor_White);
    else
    text5 = TTF_RenderText_Blended(font, "Hints", fontColor_Gray);
    textRect = {1050, 500, text5->w, text5->h};
    SDL_BlitSurface(text5, nullptr, surface, &textRect);
    SDL_FreeSurface(text5);

    if(enable_player_vs_player)
    text6 = TTF_RenderText_Blended(font, "Player vs Player", fontColor_White);
    else
    text6 = TTF_RenderText_Blended(font, "Player vs Player", fontColor_Gray);
    textRect = {970, 700, text6->w, text6->h};
    SDL_BlitSurface(text6, nullptr, surface, &textRect);
    SDL_FreeSurface(text6);

    
    SDL_Surface* text7 = TTF_RenderText_Blended(font, "Reset", fontColor_White);
    textRect = {1050, 900, text7->w, text7->h};
    SDL_BlitSurface(text7, nullptr, surface, &textRect);
    SDL_FreeSurface(text7);


    if(State_of_game==1)
    {
        SDL_Surface* text8 = TTF_RenderText_Blended(font_big, "WHITE WINS!", fontColor_White);
        textRect = {50, 400, text8->w, text8->h};
        SDL_BlitSurface(text8, nullptr, surface, &textRect);
        SDL_FreeSurface(text8);
    }

    if(State_of_game==2)
    {
        SDL_Surface* text9 = TTF_RenderText_Blended(font_big, "BLACK WINS!", fontColor_Black);
        textRect = {50, 400, text9->w, text9->h};
        SDL_BlitSurface(text9, nullptr, surface, &textRect);
        SDL_FreeSurface(text9);
    }

    if(State_of_game==-1)
    {
        SDL_Surface* text10 = TTF_RenderText_Blended(font_big, "TIE!", fontColor_Gray);
        textRect = {300, 400, text10->w, text10->h};
        SDL_BlitSurface(text10, nullptr, surface, &textRect);
        SDL_FreeSurface(text10);
    }


}
