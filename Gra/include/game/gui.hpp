#ifndef GUI_HPP_
#define GUI_HPP_

#include <SDL.h>
#include <SDL_ttf.h>
#include "game/board.hpp"
#include "game/bot.hpp"

class Gui
{
  public:
    bool init();
    void execGame();
    void handleMouseButtonDown(SDL_Event& event);

    // Sprawdzanie czy wybrane pole jest polem z dostępnym pionkiem i wybranie go
    int Find_Field_with_pawn(int x, int y, Board &board);

    //Sprawdzenie czy wybrane pole jest możliwe do przesunięcia i wybranie go
    void Find_Field_without_pawn(int x, int y, Board &board);

    void draw_possibilities(Moves moves);

    // zmiana ustawień gry po wyborze gracza p
    void change_settings(int x,int y);

    //Wyświetlanie wybranych przez użytkownika ustawień gry
    void draw_settings();

    //włączanie podpowiedzi
    bool enable_possible_fields=true;
    
    bool enable_player_vs_player=false;
    int difficulty=6;

    //aktualny stan rozgrywki 
    int State_of_game=0;
    

    Gui();


  private:
    void draw();

    bool gameIsRunning = false;

    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    TTF_Font* font = nullptr;
    TTF_Font* font_big = nullptr;
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
