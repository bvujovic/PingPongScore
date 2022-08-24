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

    // 
    if (msLastSignal > 0 && ms > msLastSignal + 5)
    {
        if (pulseCountOk(cntHome))
        {
            if (msLastCommand > 0 && ms < msLastCommand + itvMaxForDoubleClick)
            {
                result = HomeClick2;
                setLastCommand(None, 0);
            }
            else
                setLastCommand(HomeClick, ms);
        }
        if (pulseCountOk(cntAway))
        {
            if (ms < msLastCommand + itvMaxForDoubleClick)
            {
                result = AwayClick2;
                setLastCommand(None, 0);
            }
            else
                setLastCommand(AwayClick, ms);
        }
        if (pulseCountOk(cntMiddle))
        {
            // T
            // for (size_t i = 0; i < cntMiddle; i++)
            // {
            //   Serial.print(pulses[i]);
            //   Serial.print(' ');
            // }
            // Serial.println();

            if (ms < msLastCommand + itvMaxForDoubleClick)
            {
                result = MiddleClick2;
                setLastCommand(None, 0);
            }
            else
                setLastCommand(MiddleClick, ms);
        }
        cntHome = cntMiddle = cntAway = 0;
        msLastSignal = 0;
    }

    // if itvMaxForDoubleClick msecs passed and there was no repeated signal (dblclick),
    // (first) command is accepted and returned as a result
    if (cmdLast != None && ms > msLastCommand + itvMaxForDoubleClick)
    {
        if (cmdLast == HomeClick)
            result = HomeClick;
        if (cmdLast == MiddleClick)
            result = MiddleClick;
        if (cmdLast == AwayClick)
            result = AwayClick;

        setLastCommand(None, 0);
        cmdLast = None;
        msLastCommand = 0;
    }

    return result;
}

void SignalDecoder::setLastCommand(Command cmd, ulong ms)
{
    cmdLast = cmd;
    msLastCommand = ms;
}
