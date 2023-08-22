#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_mixer.h>

#include <player.hpp>
#include <ball.hpp>
#include <collision_check.hpp>
#include <constants.hpp>
#include <score.hpp>
#include <sounds.hpp>

int main(int argc, char *args[])
{   
    // initialise sdl
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        printf("SDL_Init Error: %s", SDL_GetError());

    // create window
    window = SDL_CreateWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window)
        printf("SDL_CreateWindow Error: %s", SDL_GetError());
    else
    {
        // create renderer 

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!renderer)
            printf("SDL_CreateRenderer Error: %s", SDL_GetError());

        else
        {
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

            //  initialise PNG loading

            int img_flags = IMG_INIT_PNG;
            if (!(IMG_Init(img_flags) & img_flags))
                printf("SDL_image Error: %s", IMG_GetError());

            //  initialise SDL_mixer

            if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                printf("SDL_Mixer Error: %s", Mix_GetError());
        }
    }

    // load sprite sheet

    SDL_Surface * loadedSurface = IMG_Load("graphics/pong_sprite_sheet.png");

    if (!loadedSurface)
        printf("IMG_Load Error: %s", IMG_GetError());
    else
        loaded_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    bool running = true;

    SDL_Event e;

    Player playerOne(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2 - (7 * SCALE_FACTOR), SDLK_w, SDLK_s);

    Player playerTwo(SCREEN_WIDTH - SCREEN_WIDTH / 8 - 16, SCREEN_HEIGHT / 2 - (7 * SCALE_FACTOR), SDLK_UP, SDLK_DOWN);


    SDL_Rect halfWayLineSrc = {186, 0, 1, 2413};

    SDL_Rect halfWayLineDst = {(SCREEN_WIDTH /2) - 4 , 0, 2 * SCALE_FACTOR, SCREEN_HEIGHT};

    Sounds sounds;

    Score score(&playerOne, &playerTwo);

    Ball ball(SCREEN_WIDTH / 2 - (2 * SCALE_FACTOR), SCREEN_HEIGHT / 2 - (2 * SCALE_FACTOR), &playerOne, &playerTwo, &sounds);

    while (running)
    {
        // poll for new events
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                running = false;

            playerOne.handleEvent(e);
            playerTwo.handleEvent(e);
        }

        ball.move();

        playerOne.move();
        playerTwo.move();

        SDL_RenderClear(renderer);

        // render half way line 
        SDL_RenderCopy(renderer, loaded_texture, &halfWayLineSrc, &halfWayLineDst);

        score.renderScores();

        playerOne.render();
        playerTwo.render();

        ball.render();

        SDL_RenderPresent(renderer);
    }

    // free up mem &&quit
    sounds.cleanUp();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    window = NULL;
    renderer = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
