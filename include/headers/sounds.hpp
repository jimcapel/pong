#pragma once

#include <SDL2/SDL_mixer.h>

class Sounds
{
    Mix_Chunk *playerOneSound;
    Mix_Chunk *playerTwoSound;

    Mix_Chunk *scoredSound;

    public:
        Sounds();

        void playPlayerOneSound();
        void playPlayerTwoSound();

        void playScoredSound();

        void cleanUp();
};