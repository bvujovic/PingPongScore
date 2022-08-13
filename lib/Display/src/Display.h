#pragma once

#include <TM1637Display.h>
#include "Score.h"

class Display
{
private:
    TM1637Display *display1;
    TM1637Display *display2;
    Score &score;
    uint32_t msPhaseStart = 0;
    static const int itvDisplayTime;

    enum Phase
    {
        NONE,
        SCORE,
        SERVE
    } phase;

    // void addDisplay(uint8_t clk, uint8_t dio, uint8_t brightness);

    static void displayOneSide(TM1637Display *disp, int points, uint8_t segments[], int idxSeg);

public:
    Display(Score &score) : score(score) {}
    void addDisplay1(uint8_t clk, uint8_t dio, uint8_t brightness);
    void addDisplay2(uint8_t clk, uint8_t dio, uint8_t brightness);

    void displayScore(uint32_t ms);
    void displayServe();
    void refresh(uint32_t ms);
};
