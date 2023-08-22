#include <SDL2/SDL_mixer.h>

#include <sounds.hpp>

Sounds::Sounds()
{
    playerOneSound = Mix_LoadWAV("sounds/pongblipf-4.wav");
    playerTwoSound = Mix_LoadWAV("sounds/pongblipf-5.wav");

    scoredSound = Mix_LoadWAV("sounds/pongblipg-5.wav");
}

void Sounds::playPlayerOneSound()
{
    Mix_PlayChannel(-1, playerOneSound, 0);
}

void Sounds::playPlayerTwoSound()
{
    Mix_PlayChannel(-1, playerTwoSound, 0);
}

void Sounds::playScoredSound()
{
    Mix_PlayChannel(-1, scoredSound, 0);
}

void Sounds::cleanUp()
{
    Mix_FreeChunk(playerOneSound);
    Mix_FreeChunk(playerTwoSound);

    playerOneSound = NULL;
    playerTwoSound = NULL;
}