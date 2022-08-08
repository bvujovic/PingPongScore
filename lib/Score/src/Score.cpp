#include "Score.h"

Score::Score()
{
    resetScore();
}

void Score::changeServe()
{
    serveCurrent = (Side)!serveCurrent;
    if (homePoints == 0 && awayPoints == 0)
        serveStarted = serveCurrent;
}

void Score::resetScore()
{
    homePoints = awayPoints = 0;
    serveStarted = serveCurrent = Home;
}

void Score::pointWon(Side side)
{
    if (side == Home)
        homePoints++;
    if (side == Away)
        awayPoints++;
    serveCurrent = (Side)(((homePoints + awayPoints) / 2) % 2);

    
}
