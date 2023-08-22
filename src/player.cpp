#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include <player.hpp>
#include <constants.hpp>

Player::Player(int x, int y, SDL_KeyCode up, SDL_KeyCode down)
    : up(up), down(down)
{
    yVelocity = 0;

    ySpeed = 7;

    srcRect = {29, 94, 4, 14};

    dstRect = {
        x,
        y,
        srcRect.w * SCALE_FACTOR,
        srcRect.h * SCALE_FACTOR,
    };

    score = 0;
}

void Player::render()
{
    SDL_RenderCopy(renderer, loaded_texture, &srcRect, &dstRect);
}

void Player::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {

        if (e.key.keysym.sym == up)
            yVelocity -= ySpeed;
        else if (e.key.keysym.sym == down)
            yVelocity += ySpeed;
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        if (e.key.keysym.sym == up)
            yVelocity += ySpeed;
        else if (e.key.keysym.sym == down)
            yVelocity -= ySpeed;
    }
}

void Player::move()
{
    dstRect.y += yVelocity;

    if (dstRect.y < 0)
        dstRect.y = 0;
    else if ((dstRect.y + dstRect.h) > SCREEN_HEIGHT)
        dstRect.y = SCREEN_HEIGHT - dstRect.h;
}

SDL_Rect *Player::getDstRect()
{
    return &dstRect;
}

int Player::getScore()
{
    return score;
}

void Player::setScore(int newScore)
{
    score = newScore;
}