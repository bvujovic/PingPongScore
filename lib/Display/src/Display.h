#pragma once

#include <TM1637Display.h>
#include "Score.h"

// Displaying the Score on a TM1637 display.
class Display
{
private:
    TM1637Display *display;          // TM1637 display object (pointer)
    Score &score;                    // reference to Score object
    uint32_t msPhaseStart = 0;       // time (msec) of the last phase change
    static const int itvDisplayTime; // how long (msec) should score or serve stay on the screen

    // What is on the display: score, who is serving, nothing.
    enum Phase
    {
        NONE,  // display is clear
        SCORE, // current score is displayed
        SERVE  // who is serving
    } phase;

    // displaying one side (home or away) of the score
    static void displayOneSide(TM1637Display *disp, int points, uint8_t segments[], int idxSeg);

public:
    Display(Score &score) : score(score) {}
    
    // initializing TM1637 display
    void setDisplay(uint8_t clk, uint8_t dio, uint8_t brightness);

    // display current score; parameter <- millis()
    void displayScore(uint32_t ms);
    // display which side (home or away) serves next
    void displayServe();
    // this method should be called in the loop(); parameter <- millis()
    void refresh(uint32_t ms);
};
