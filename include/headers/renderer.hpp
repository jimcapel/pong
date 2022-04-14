#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Renderer
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    
public:
    Renderer(const char *title, int width, int height);

    SDL_Texture *load_texture(const char *p_file_path);
    // void render(Entity &p_entity);
    void display();
    void clear();
    void clean_up();
};