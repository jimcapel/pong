#pragma once

#include <SDL2/SDL.h>
#include <constants.hpp>

CollisionType collisionCheck(SDL_Rect *entityOne, SDL_Rect *entityTwo);
