#include "Score.h"

Score::Score()
{
    reset();
}

void Score::reset()
{
    isOver = false;
    homePoints = awayPoints = 0;
    serveStarted = serveCurrent = (Side)!serveStarted;
}

void Score::changeServe()
{
    serveStarted = (Side)!serveStarted;
    serveCurrent = (Side)!serveCurrent;
}

void Score::pointWon(Side side)
{
    if (isOver)
        return;

    if (side == Home)
        homePoints++;
    if (side == Away)
        awayPoints++;
    // B lastPointWon = side;

    calcIsMatchOver();
    calcWhoServesNext();
}

void Score::calcIsMatchOver()
{
    isOver = false;
    if ((homePoints >= 11 && awayPoints <= 9) || (awayPoints >= 11 && homePoints <= 9))
        isOver = true;
    else if (homePoints >= 10 && awayPoints >= 10 && (homePoints >= awayPoints + 2 || awayPoints >= homePoints + 2))
        isOver = true;
}

void Score::calcWhoServesNext()
{
    if (homePoints >= 10 && awayPoints >= 10)
        serveCurrent = (Side)(((homePoints + awayPoints)) % 2);
    else
        serveCurrent = (Side)(((homePoints + awayPoints) / 2) % 2);
    if (serveStarted == Away)
        serveCurrent = (Side)!serveCurrent;
}

void Score::pointRetracted(Side side)
{
    if (side == Home && homePoints > 0)
        homePoints--;
    if (side == Away && awayPoints > 0)
        awayPoints--;

    calcIsMatchOver();
    calcWhoServesNext();
}

// void Score::undoLastPoint()
// {
//     if ((lastPointWon == Home && homePoints == 0) || (lastPointWon == Away && awayPoints == 0))
//         return;
//     if (lastPointWon == Home)
//         homePoints--;
//     if (lastPointWon == Away)
//         awayPoints--;
//     calcWhoServesNext();
// }
