#include <SDL2/SDL.h>
#include <stdio.h>

#include <renderer.hpp>

Renderer::Renderer(const char *title, int width, int height)
    : window(NULL), renderer(NULL)
{

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window)
        printf("SDL_CreateWindow Error: %s", SDL_GetError());
    else
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!renderer)
            printf("SDL_CreateRenderer Error: %s", SDL_GetError());

        else
        {
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        }
    }
}

void Renderer::display()
{
    SDL_RenderPresent(renderer);
}

void Renderer::clear()
{
    SDL_RenderClear(renderer);
}

void Renderer::clean_up()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
}