#include "game/gui.hpp"

#define Empty 0
#define White_Pawn 1
#define Black_Pawn 2
#define White_King 3
#define Black_King 4


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
    SDL_Surface* text = TTF_RenderText_Blended(font, "WARCABY", fontColor);
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
                        if(board.x1==0 && board.y1==0){}
                        else
                        {
                            Moves moves;
                            board.check_possible_moves(board.x, board.y, moves, board.color_);
                            board.move_pawn();
                            board.Capture_all(moves);
                            board.clear_choices();

                            board.possible_capture=board.Check_Possible_Capture_(board.color_);
                        }
                      
                    }
                    break;
            }
        }

        draw();
    }

    SDL_Quit();
    TTF_Quit();
}

void Gui::draw()
{
    SDL_Rect boardRect = {0, 70, 60, 60};
    SDL_BlitSurface(board_texture, nullptr, surface, &boardRect);

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
    if(board.if_pawn_chosen==false)
    {
        Moves moves;
        board.reset_possible_moves();
        Find_Field_with_pawn(event.button.x, event.button.y, board);
        board.check_possible_moves(board.x, board.y, moves, board.color_);
        draw_possibilities(moves);
    }
    else if(board.if_field_chosen==false)
    {
        Find_Field_without_pawn(event.button.x, event.button.y, board);
    }
    
}

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