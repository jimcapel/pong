#pragma once

#include <SDL2/SDL.h>

#include <player.hpp>

class Score
{
    Player *playerOne, *playerTwo;
    SDL_Rect playerOneScoreDstRect, playerTwoScoreDstRect;

    public: 
        Score(Player *playerOne, Player *playerTwo);

        void renderScores();

};

SDL_Rect getScoreRect(int score);

