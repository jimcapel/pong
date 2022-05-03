#pragma once

#include <SDL2/SDL.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int SCALE_FACTOR;

extern const float VELOCITY;

extern const float DIAGONAL_VELOCITY;

extern const int SCORE_SPRITE_WIDTH;

extern const int SCORE_SPRITE_HEIGHT;

extern SDL_Renderer *renderer;

extern SDL_Texture *loaded_texture;

extern SDL_Window *window;

enum CollisionType {
    no_collision,
    top,
    middle,
    bottom,
  };

enum CurrentPlayer {
  playerOne,
  playerTwo
};
