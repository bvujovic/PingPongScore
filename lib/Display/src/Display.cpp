#include "Display.h"

const int Display::itvDisplayTime = 1000;

void Display::addDisplay1(uint8_t clk, uint8_t dio, uint8_t brightness)
{
    if (display1 != nullptr)
        delete display1;
    display1 = new TM1637Display(clk, dio);
    display1->setBrightness(brightness);
}

void Display::displayScore(uint32_t ms)
{
    msPhaseStart = ms;
    phase = SCORE;
    if (display1 != nullptr)
    {
        uint8_t segmets[4];
        displayOneSide(display1, score.getHomePoints(), segmets, 0);
        // B
        //  if (home < 10)
        //  {
        //      segmets[0] = display1->encodeDigit(home);
        //      segmets[1] = SEG_DP;
        //  }
        //  else
        //  {
        //      segmets[0] = display1->encodeDigit(home / 10);
        //      segmets[1] = display1->encodeDigit(home % 10) | SEG_DP;
        //  }
        displayOneSide(display1, score.getAwayPoints(), segmets, 2);
        // B
        //  if (away < 10)
        //  {
        //      segmets[2] = 0;
        //      segmets[3] = display1->encodeDigit(away);
        //  }
        //  else
        //  {
        //      segmets[2] = display1->encodeDigit(away / 10);
        //      segmets[3] = display1->encodeDigit(away % 10);
        //  }
        display1->setSegments(segmets);
    }
}

void Display::displayOneSide(TM1637Display *disp, int points, uint8_t segments[], int idxSeg)
{
    if (points < 10)
    {
        uint8_t digit = disp->encodeDigit(points);
        segments[idxSeg] = idxSeg == 0 ? digit : 0;
        segments[idxSeg + 1] = idxSeg == 0 ? SEG_DP : digit;
    }
    else
    {
        segments[idxSeg] = disp->encodeDigit(points / 10);
        segments[idxSeg + 1] = disp->encodeDigit(points % 10) | (idxSeg == 0 ? SEG_DP : 0);
    }
}

void Display::refresh(uint32_t ms)
{
    if (phase == SCORE && ms > msPhaseStart + itvDisplayTime)
    {
        displayServe();
        msPhaseStart = ms;
        phase = SERVE;
    }
    if (phase == SERVE && ms > msPhaseStart + itvDisplayTime)
    {
        if (display1 != nullptr)
            display1->clear();
        phase = NONE;
    }
}

void Display::displayServe()
{
    if (score.isMatchOver())
        return;
    const uint8_t ball = SEG_C | SEG_D | SEG_E | SEG_G;
    //B
    // if (score.getServe() == Home)
    // {
    //     const uint8_t HOME_BALL[] = {ball, SEG_DP, 0, 0}; // |o :  |
    //     display1->setSegments(HOME_BALL);
    // }
    // else
    // {
    //     const uint8_t AWAY_BALL[] = {0, SEG_DP, 0, ball}; // |  : o|
    //     display1->setSegments(AWAY_BALL);
    // }
    if (score.getServe() == Home)
        display1->setSegments((const uint8_t[]){ball, SEG_DP, 0, 0}); // |o :  |
    else
        display1->setSegments((const uint8_t[]){0, SEG_DP, 0, ball}); // |  : o|
}
