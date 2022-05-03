#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

#include <ball.hpp>
#include <constants.hpp>
#include <collision_check.hpp>

Ball::Ball(int x, int y, Player *playerOne, Player *playerTwo, Sounds *sounds)
    : playerOne(playerOne), playerTwo(playerTwo), sounds(sounds)
{
    // start with ball heading toward player two
    xVelocity = VELOCITY;

    yVelocity = 0;

    srcRect = {73, 104, 4, 4};

    dstRect = {
        x,
        y,
        srcRect.w * SCALE_FACTOR,
        srcRect.h * SCALE_FACTOR
      };

    currentPlayer = CurrentPlayer::playerTwo;
}

void Ball::render()
{
    SDL_RenderCopy(renderer,  loaded_texture, &srcRect, &dstRect);
}


void Ball::move()
{
    //  if player one has scored
    if(dstRect.x > SCREEN_WIDTH)
    {
        sounds->playScoredSound();

        dstRect.x = SCREEN_WIDTH / 2 - (2 * SCALE_FACTOR);
        dstRect.y = SCREEN_HEIGHT / 2 - (2 * SCALE_FACTOR);
        xVelocity = VELOCITY;
        yVelocity = 0;

        playerOne->setScore(playerOne->getScore() + 1);


        currentPlayer = CurrentPlayer::playerTwo;

        return;
    }

    //  if player two has scored
    if(dstRect.x + dstRect.w < 0){
        sounds->playScoredSound();

        dstRect.x = SCREEN_WIDTH / 2 - (2 * SCALE_FACTOR);
        dstRect.y = SCREEN_HEIGHT / 2 - (2 * SCALE_FACTOR);
        xVelocity = -VELOCITY;
        yVelocity = 0;

        playerTwo->setScore(playerTwo->getScore() + 1);


        currentPlayer = CurrentPlayer::playerOne;

        return;
    }


    //if ball goes out of bounds vertically, rebound
    if (dstRect.y < 0 || dstRect.y + dstRect.h > SCREEN_HEIGHT)
    {
      yVelocity = -yVelocity;
      dstRect.y += yVelocity;

      return;
    }

    // change to use a state system, then only need to check for the other collision, also can replace side function with this. 
    // check for player collision and if collided, rebound

    Player * playerToCheck = currentPlayer == CurrentPlayer::playerOne ? playerOne : playerTwo;
 
    CollisionType collisionType = collisionCheck(&dstRect, playerToCheck->getDstRect());

    if(currentPlayer == CurrentPlayer::playerOne && collisionType != no_collision) sounds->playPlayerOneSound();
    else if (currentPlayer != CurrentPlayer::playerOne && collisionType != no_collision) sounds->playPlayerTwoSound();

     if (collisionType == top)
    {
        if(currentPlayer == CurrentPlayer::playerTwo){
             xVelocity = -DIAGONAL_VELOCITY;
        }else{
             xVelocity = DIAGONAL_VELOCITY;
        }

        dstRect.x += xVelocity;
        yVelocity = -DIAGONAL_VELOCITY ;
        dstRect.y += yVelocity;

        if(currentPlayer == CurrentPlayer::playerTwo)
        {
            currentPlayer = CurrentPlayer::playerOne;
        }else
        {
            currentPlayer = CurrentPlayer::playerTwo;
        }

    }
    else if(collisionType == middle)
    {
      xVelocity = xVelocity < 0 ? VELOCITY : -VELOCITY;
      dstRect.x += xVelocity;

      yVelocity = 0;
      dstRect.y += yVelocity;

      if(currentPlayer == CurrentPlayer::playerTwo)
        {
            currentPlayer = CurrentPlayer::playerOne;
        }else
        {
            currentPlayer = CurrentPlayer::playerTwo;
        }
    }
    else if(collisionType == bottom)
    {
        if(currentPlayer == CurrentPlayer::playerTwo){
        xVelocity = -DIAGONAL_VELOCITY;
        }else{
        xVelocity = DIAGONAL_VELOCITY;
        }
        
        dstRect.x += xVelocity;
        yVelocity = DIAGONAL_VELOCITY;
        dstRect.y += yVelocity;

        if(currentPlayer == CurrentPlayer::playerTwo)
        {
            currentPlayer = CurrentPlayer::playerOne;
        }else
        {
            currentPlayer = CurrentPlayer::playerTwo;
        }
    }
    else
    {
        dstRect.x += xVelocity;
        dstRect.y += yVelocity;
    }

}
