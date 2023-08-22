#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player
{
    SDL_KeyCode up;
    SDL_KeyCode down;

    int ySpeed;
    int yVelocity;

    int score;

    SDL_Rect srcRect;
    SDL_Rect dstRect;

public:
    Player(int x, int y, SDL_KeyCode up, SDL_KeyCode down);

    SDL_Rect *getDstRect();

    void render();
    void handleEvent(SDL_Event &e);
    void move();

    int getScore();
    void setScore(int newScore);


};
