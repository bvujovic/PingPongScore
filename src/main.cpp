#include <Arduino.h>

typedef unsigned long ulong;

const byte pinIn = 11;
const byte pinLed = 4;
ulong pul, lastPul;
ulong msLastSignal = 0;
ulong cnt1 = 0, cnt2 = 0, cnt3 = 0;

#include "Score.h"
Score score;

void displayResult();

void setup()
{
  pinMode(pinIn, INPUT);
  pinMode(pinLed, OUTPUT);

  Serial.begin(9600);
  Serial.println("Ping-pong Score started");
}

void loop()
{
  pul = pulseIn(pinIn, LOW);

  if (pul > 3888 && pul < 3952)
  {
    cnt1++;
    msLastSignal = millis();
  }
  if (pul > 4860 && pul < 4940)
  {
    cnt2++;
    msLastSignal = millis();
  }
  if (pul > 5832 && pul < 5928)
  {
    cnt3++;
    msLastSignal = millis();
  }

  if (msLastSignal > 0 && millis() > msLastSignal + 20) //* probati ovo sa +5 umesto +20 msec
  {
    if (cnt1 >= 4 && cnt1 <= 6)
    {
      // Serial.println(String("cmd1: ") + cnt1);
      score.pointWon(Home);
      displayResult();
    }
    if (cnt2 >= 4 && cnt2 <= 6)
    {
      // Serial.println(String("cmd2: ") + cnt2);
      score.pointWon(Away);
      displayResult();
    }
    if (cnt3 >= 4 && cnt3 <= 6)
    {
      // Serial.println(String("cmd3: ") + cnt3);
      displayResult();
    }

    cnt1 = cnt2 = cnt3 = 0;
    msLastSignal = 0;
  }

  lastPul = pul;
}

void displayResult()
{
  Serial.print(score.getHomePoints());
  Serial.print(':');
  Serial.print(score.getAwayPoints());
  Serial.println();
  Serial.println(score.getServe() == Home ? 'H' : 'A');
}
