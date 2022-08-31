#include "SignalDecoder.h"

const int SignalDecoder::itvMaxForDoubleClick = 1000;

void SignalDecoder::pulseCount(ulong pulse, ulong ms)
{
    if (pulse > 3950 && pulse < 4000)
    {
        // T pulses[cntHome] = pulse;
        cntHome++;
        msLastSignal = ms;
    }
    if (pulse > 4940 && pulse < 5000)
    {
        // T pulses[cntMiddle] = pulse;
        cntMiddle++;
        msLastSignal = ms;
    }
    if (pulse > 5920 && pulse < 5980)
    {
        // T pulses[cntAway] = pulse;
        cntAway++;
        msLastSignal = ms;
    }
}

Command SignalDecoder::refresh(ulong pulse, ulong ms)
{
    Command result = None;
    pulseCount(pulse, ms);
    if (msLastSignal > 0 && ms > msLastSignal + 5)
    {
        if (pulseCountOk(cntHome))
            return returnCommand(HomeClick, HomeClick2, ms);
        if (pulseCountOk(cntMiddle))
            return returnCommand(MiddleClick, MiddleClick2, ms);
        if (pulseCountOk(cntAway))
            return returnCommand(AwayClick, AwayClick2, ms);
        cntHome = cntMiddle = cntAway = 0;
        msLastSignal = 0;
    }
    return result;
}

Command SignalDecoder::returnCommand(Command cmdClick, Command cmdClick2, ulong ms)
{
    cntHome = cntMiddle = cntAway = 0;
    msLastSignal = 0;
    if (cmdLast == cmdClick && msLastCommand > 0 && ms < msLastCommand + itvMaxForDoubleClick)
    {
        setLastCommand(None, 0);
        return cmdClick2;
    }
    setLastCommand(cmdClick, ms);
    return cmdClick;
}

void SignalDecoder::setLastCommand(Command cmd, ulong ms)
{
    cmdLast = cmd;
    msLastCommand = ms;
}
