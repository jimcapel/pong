#include <SDL2/SDL.h>
#include <stdio.h>

#include <score.hpp>
#include <constants.hpp>

#include <player.hpp>

// gets number texture from sprite sheet
SDL_Rect getScoreRect(int score)
{
    if ( score == 0 )
    {
        return  { 4, 3, 16, 34 };
    }
    else if ( score == 1 )
    {
        return { 23, 3, 4,  34 };
    }
    else
    {
        //  adds on 19 pixels each time for every number after and inclusive of two in order to display correct score
        return {30 + (19 * (score - 2) ), 3, 16, 34 };
    }
};

Score::Score(Player *playerOne, Player *playerTwo):
    playerOne(playerOne), playerTwo(playerTwo)
{
    playerOneScoreDstRect = {SCREEN_WIDTH / 2 - ( (SCORE_SPRITE_WIDTH * 2  * 2) + 10) ,10,  SCORE_SPRITE_WIDTH * 2, SCORE_SPRITE_HEIGHT * 2 };
    playerTwoScoreDstRect =  {SCREEN_WIDTH / 2 + ( (SCORE_SPRITE_WIDTH * 2 ) + 10) ,10,  SCORE_SPRITE_WIDTH * 2, SCORE_SPRITE_HEIGHT * 2 };
}

void Score::renderScores()
{

    // reset scores if > 9
    if(playerOne->getScore() > 9 || playerTwo->getScore() > 9)
    {
        playerOne->setScore(0);
        playerTwo->setScore(0);
    }

    // player one score texture data
    SDL_Rect playerOneScoreSrcRect = getScoreRect(playerOne->getScore());
    // adds 8 extra pixels to account for width of number one sprite
    SDL_Rect playerOneScoreOneRect = {SCREEN_WIDTH / 2 - ( (SCORE_SPRITE_WIDTH  * 2) + 18), playerOneScoreDstRect.y, 4 * 2, playerOneScoreDstRect.h };
    SDL_Rect *playerOneScoreDstRectFinal = playerOne->getScore() == 1 ? &playerOneScoreOneRect : &playerOneScoreDstRect;

    // player two score texture data
    SDL_Rect playerTwoScoreSrcRect = getScoreRect(playerTwo->getScore());
    SDL_Rect playerTwoScoreOneRect = { playerTwoScoreDstRect.x, playerTwoScoreDstRect.y, 4 * 2, playerTwoScoreDstRect.h };
    SDL_Rect *playerTwoScoreDstRectFinal = playerTwo->getScore() == 1 ? &playerTwoScoreOneRect : &playerTwoScoreDstRect;

    // render both scores
    SDL_RenderCopy(renderer, loaded_texture, &playerOneScoreSrcRect,  playerOneScoreDstRectFinal);
    SDL_RenderCopy(renderer, loaded_texture, &playerTwoScoreSrcRect,  playerTwoScoreDstRectFinal);
}

