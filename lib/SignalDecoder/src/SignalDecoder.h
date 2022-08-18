#pragma once

// T #include <Arduino.h>

typedef unsigned long ulong;

enum Command
{
    None,         // no command is detected
    HomeClick,    // top/left button clicked once
    MiddleClick,  // middle button clicked once
    AwayClick,    // bottom/right button clicked once
    HomeClick2,   // top/left button double clicked
    MiddleClick2, // middle button double clicked
    AwayClick2,   // bottom/right button double clicked
};

class SignalDecoder
{
private:
    int cntHome = 0;
    int cntMiddle = 0;
    int cntAway = 0;
    ulong msLastSignal = 0;
    ulong msLastCommand = 0;
    // T ulong puls[10];
    Command cmdLast = None;

    static const int itvMaxForDoubleClick;

    void setLastCommand(Command cmd, ulong ms);
    static bool pulseCountOk(int cnt) { return cnt >= 4 && cnt <= 6; }
    void pulseCount(ulong pulse, ulong ms);

public:
    Command refresh(ulong pulse, ulong ms);
};
