#include "Display.h"

const int Display::itvDisplayTime = 1000;

void Display::setDisplay(uint8_t clk, uint8_t dio, uint8_t brightness)
{
    if (display != nullptr)
        delete display;
    display = new TM1637Display(clk, dio);
    display->setBrightness(brightness);
}

void Display::displayScore(uint32_t ms)
{
    msPhaseStart = ms;
    phase = SCORE;
    if (display != nullptr)
    {
        uint8_t segmets[4];
        displayOneSide(display, score.getHomePoints(), segmets, 0);
        displayOneSide(display, score.getAwayPoints(), segmets, 2);
        display->setSegments(segmets);
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
        if (display != nullptr)
            display->clear();
        phase = NONE;
    }
}

void Display::displayServe()
{
    if (score.isGameOver())
        return;
    const uint8_t ball = SEG_C | SEG_D | SEG_E | SEG_G;
    if (score.getServe() == Home)
        display->setSegments((const uint8_t[]){ball, SEG_DP, 0, 0}); // |o :  |
    else
        display->setSegments((const uint8_t[]){0, SEG_DP, 0, ball}); // |  : o|
}
