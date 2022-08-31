#pragma once

typedef unsigned long ulong;

// Action of the transmitter device - button [double] click.
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

// Object of this class decodes signals that are received and gives back the command if there is any.
class SignalDecoder
{
private:
    int cntHome = 0;         // counter for home button pulses (4ms)
    int cntMiddle = 0;       // counter for middle button pulses (5ms)
    int cntAway = 0;         // counter for away button pulses (6ms)
    ulong msLastSignal = 0;  // time (msec) of the last received pulse
    ulong msLastCommand = 0; // time (msec) of the last interpreted command (sequence of pulses)
    Command cmdLast = None;  // last interpreted command
    // T ulong puls[10]; // can be used for testing values of received pulses

    // max time (msec) between 2 commands (clicks) that are interpreted as one (double click)
    static const int itvMaxForDoubleClick;

    // setting the last command and the time it's received
    void setLastCommand(Command cmd, ulong ms);
    // is number of same pulses Ok: 5 +/-1
    static bool pulseCountOk(int cnt) { return cnt >= 4 && cnt <= 6; }
    // counting sequences of pulses: 4ms, 5ms and 6ms for home, middle and away buttons/commands
    void pulseCount(ulong pulse, ulong ms);
    // based on button click (home/middle/away) method returns Command (single or double click)
    Command returnCommand(Command click1, Command click2, ulong ms);

public:
    // this method should be called in the loop()
    // pulse gets its value from pulseIn(); ms gets its value from millis()
    Command refresh(ulong pulse, ulong ms);
};
