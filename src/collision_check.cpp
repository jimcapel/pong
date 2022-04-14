#include <SDL2/SDL.h>

#include <constants.hpp>

CollisionType collisionCheck(SDL_Rect *entityOne, SDL_Rect *entityTwo)
{
      if (entityOne->y > (entityTwo->y + entityTwo->h))
            return no_collision;

        // if entityOne_y + entityOne_h < entityTwo_y
        else if ((entityOne->y + entityOne->h) < entityTwo->y)
            return no_collision;

        // if entityOne_x > entityTwo_x + entityTwo_w
        else if (entityOne->x > (entityTwo->x + entityTwo->w))
            return no_collision;

        // if entityOne_x + entityOne_w < entityTwo_x
        else if ((entityOne->x + entityOne->w) < entityTwo->x)
            return no_collision;

        // else collided
        else
        {
            const float centreYBall = (entityOne->y + entityOne->y + entityOne->h) / 2.0;

            if(centreYBall <= entityTwo->y + (entityTwo->h * (1.0/3.0)))
            {
               
                return top;
            }
            else if (centreYBall <= entityTwo->y + (entityTwo->h * (2.0/3.0)))
            {
              
              return middle;
            }
           
            return bottom;
        }
}