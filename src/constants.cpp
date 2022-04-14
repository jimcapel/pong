#include <math.h>
#include <SDL2/SDL.h>

#include <constants.hpp>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int SCALE_FACTOR = 4;

const float VELOCITY = 12;

const float DIAGONAL_VELOCITY = sqrt(72);

const int SCORE_SPRITE_WIDTH = 16;

const int SCORE_SPRITE_HEIGHT = 33;

SDL_Renderer *renderer;

SDL_Texture *loaded_texture;

SDL_Window *window;