#ifndef GUI_HPP_
#define GUI_HPP_

#include <SDL.h>
#include <SDL_ttf.h>
#include "game/board.hpp"

class Gui
{
  public:
    bool init();
    void execGame();
    void handleMouseButtonDown(SDL_Event& event);
    int Find_Field_with_pawn(int x, int y, Board &board);
    void Find_Field_without_pawn(int x, int y, Board &board);
    void draw_possibilities(Moves moves);
    bool enable_possible_fields=true;
    

    Gui();


  private:
    void draw();

    bool gameIsRunning = false;

    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    TTF_Font* font = nullptr;
    SDL_Surface* black_pawn = nullptr;
    SDL_Surface* black_king = nullptr;
    SDL_Surface* white_pawn = nullptr;
    SDL_Surface* white_king = nullptr;
    SDL_Surface* frame = nullptr;
    SDL_Surface* dark_field = nullptr;
    SDL_Surface* board_texture = nullptr;
    SDL_Surface* desk = nullptr;
};

#endif /* GAME_GUI_HPP_ */
