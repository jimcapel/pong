#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <constants.hpp>
#include <player.hpp>
#include <sounds.hpp>

class Ball
{
    int xVelocity;
    int yVelocity;

    SDL_Rect srcRect;
    SDL_Rect dstRect;

    Player* playerOne;
    Player* playerTwo;

    Sounds *sounds;

    CurrentPlayer currentPlayer;

public:
    Ball(int x, int y, Player *playerOne, Player *playerTwo, Sounds *sounds);

    void render();
    void move();

};
