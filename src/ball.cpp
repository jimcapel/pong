#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

#include <ball.hpp>
#include <constants.hpp>
#include <collision_check.hpp>

bool rightSide(int x) {
    if(x < SCREEN_WIDTH /2)
        return false;
    return true;
};

Ball::Ball(int x, int y, Player *playerOne, Player *playerTwo, Sounds *sounds)
    : playerOne(playerOne), playerTwo(playerTwo), sounds(sounds)
{
    // randomly start left or right
    xVelocity = (float)rand() / RAND_MAX > 0.5f ? -VELOCITY : VELOCITY;

    yVelocity = 0;

    srcRect = {73, 104, 4, 4};

    dstRect = {
        x,
        y,
        srcRect.w * SCALE_FACTOR,
        srcRect.h * SCALE_FACTOR
      };
}

void Ball::render()
{
    SDL_RenderCopy(renderer,  loaded_texture, &srcRect, &dstRect);
}


void Ball::move()
{
    bool side = rightSide(dstRect.x);

    //  if player one has scored
    if(dstRect.x > SCREEN_WIDTH)
    {
        dstRect.x = SCREEN_WIDTH / 2 - (2 * SCALE_FACTOR);
        dstRect.y = SCREEN_HEIGHT / 2 - (2 * SCALE_FACTOR);
        xVelocity = VELOCITY;
        yVelocity = 0;

        playerOne->setScore(playerOne->getScore() + 1);

        sounds->playScoredSound();

        return;
    }

    //  if player two has scored
    if(dstRect.x + dstRect.w < 0){
        dstRect.x = SCREEN_WIDTH / 2 - (2 * SCALE_FACTOR);
        dstRect.y = SCREEN_HEIGHT / 2 - (2 * SCALE_FACTOR);
        xVelocity = -VELOCITY;
        yVelocity = 0;

        playerTwo->setScore(playerTwo->getScore() + 1);

        sounds->playScoredSound();

        return;
    }


    //if ball goes out of bounds vertically, rebound
    if (dstRect.y < 0 || dstRect.y + dstRect.h > SCREEN_HEIGHT)
    {
      yVelocity = -yVelocity;
      dstRect.y += yVelocity;

      return;
    }

    // check for player collision and if collided, rebound

    CollisionType playerOneCollision = collisionCheck(&dstRect, playerOne->getDstRect());
    CollisionType playerTwoCollision = collisionCheck(&dstRect, playerTwo->getDstRect());

    if(playerOneCollision != no_collision) sounds->playPlayerOneSound();
    else if (playerTwoCollision != no_collision) sounds->playPlayerTwoSound();


    if (playerOneCollision == top || playerTwoCollision == top)
    {
        if(side){
             xVelocity = -DIAGONAL_VELOCITY;
        }else{
             xVelocity = DIAGONAL_VELOCITY;
        }

        dstRect.x += xVelocity;
        yVelocity = -DIAGONAL_VELOCITY ;
        dstRect.y += yVelocity;

    }
    else if(playerOneCollision == middle || playerTwoCollision == middle)
    {
      xVelocity = xVelocity < 0 ? VELOCITY : -VELOCITY;
      dstRect.x += xVelocity;

      yVelocity = 0;
      dstRect.y += yVelocity;
    }
    else if(playerOneCollision == bottom || playerTwoCollision == bottom)
    {
        if(side){
        xVelocity = -DIAGONAL_VELOCITY;
        }else{
        xVelocity = DIAGONAL_VELOCITY;
        }
        
        dstRect.x += xVelocity;
        yVelocity = DIAGONAL_VELOCITY;
        dstRect.y += yVelocity;
    }
    else
    {
        dstRect.x += xVelocity;
        dstRect.y += yVelocity;
    }

}
