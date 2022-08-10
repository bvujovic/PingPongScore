#include <Arduino.h>

typedef unsigned long ulong;

const byte pinIn = 11;
const byte pinLed = 4;
ulong pul, lastPul;
ulong msLastSignal = 0;
ulong cnt1 = 0, cnt2 = 0, cnt3 = 0;
const ulong itvMaxForDoubleClick = 500;
ulong msLastCommand = 0;
int cmdLast = 0;

#include "Score.h"
Score score;

#include <TM1637Display.h>
TM1637Display display = TM1637Display(A1, A0); // (CLK, DIO)
ulong msDisplayScore = 0;

void scoreToDisplay();
void scoreToSerial();
void setLastCommand(int _cmdLast, ulong _msLastCommand);

void setup()
{
  pinMode(pinIn, INPUT);
  pinMode(pinLed, OUTPUT);

  display.setBrightness(3);
  scoreToDisplay();
  Serial.begin(9600);
  Serial.println("Ping-pong Score started");
}

ulong puls[10];

void loop()
{
  pul = pulseIn(pinIn, LOW);
  // if (pul > 3900 && pul < 4000)
  //   Serial.println(pul);

  // if (pul > 3888 && pul < 3952)
  if (pul > 3950 && pul < 4000)
  {
    // puls[cnt1] = pul;
    cnt1++;
    msLastSignal = millis();
  }
  // if (pul > 4860 && pul < 4940)
  if (pul > 4940 && pul < 5000)
  {
    // puls[cnt2] = pul;
    cnt2++;
    msLastSignal = millis();
  }

  // if (pul > 5832 && pul < 5928)
  if (pul > 5920 && pul < 5980)
  {
    // puls[cnt3] = pul;
    cnt3++;
    msLastSignal = millis();
  }

  if (cmdLast != 0 && millis() > msLastCommand + itvMaxForDoubleClick)
  {
    if (cmdLast == 1)
      score.pointWon(Home);
    if (cmdLast == 2)
      score.pointWon(Away);
    scoreToSerial();
    cmdLast = 0;
    msLastCommand = 0;
  }

  if (msLastSignal > 0 && millis() > msLastSignal + 5)
  {
    if (cnt1 >= 4 && cnt1 <= 6)
    {
      if (millis() < msLastCommand + itvMaxForDoubleClick)
      {
        score.undoLastPoint();
        scoreToSerial();
      }
      else
        setLastCommand(1, millis());
    }
    if (cnt2 >= 4 && cnt2 <= 6)
    {
      if (millis() < msLastCommand + itvMaxForDoubleClick)
      {
        score.undoLastPoint();
        scoreToSerial();
      }
      else
        setLastCommand(2, millis());
    }
    if (cnt3 >= 4 && cnt3 <= 6)
    {
      // T
      //  for (size_t i = 0; i < cnt3; i++)
      //  {
      //    Serial.print(puls[i]);
      //    Serial.print(' ');
      //  }
      //  Serial.println();

      if (millis() < msLastCommand + itvMaxForDoubleClick)
        score.reset();
      scoreToSerial();
      msLastCommand = millis();
    }
    cnt1 = cnt2 = cnt3 = 0;
    msLastSignal = 0;
  }
  lastPul = pul;

  if (msDisplayScore > 0 && millis() > msDisplayScore + 1000 && !score.isMatchOver())
  {
    // prikaz ko servira
    if (score.getServe() == Home)
    {
      const uint8_t HOME_BALL[] = {SEG_C | SEG_D | SEG_E | SEG_G, SEG_DP, 0, 0}; // |o :  |
      display.setSegments(HOME_BALL);
    }
    else
    {
      const uint8_t AWAY_BALL[] = {0, SEG_DP, 0, SEG_C | SEG_D | SEG_E | SEG_G}; // |  : o|
      display.setSegments(AWAY_BALL);
    }
    delay(1000);
    msDisplayScore = 0;
    display.clear();
  }
}

void scoreToSerial()
{
  Serial.print(score.getHomePoints());
  Serial.print(':');
  Serial.print(score.getAwayPoints());
  Serial.print('\t');
  if (!score.isMatchOver())
    Serial.println(score.getServe() == Home ? 'H' : 'A');
  else
    Serial.println(score.getHomePoints() > score.getAwayPoints() ? "Home Won!" : "Away Won!");
  setLastCommand(0, 0);
  scoreToDisplay();
}

void scoreToDisplay()
{
  // B
  //  int digits = score.getHomePoints() * 100 + score.getAwayPoints();
  //  display.showNumberDecEx(digits, 0b01000000, true);

  uint8_t segmets[4];
  //todo napraviti od ovoga funkciju koja prima broj poena koji prikazuje i stranu Home/Away
  int home = score.getHomePoints();
  if (home < 10)
  {
    segmets[0] = display.encodeDigit(home);
    segmets[1] = SEG_DP;
  }
  else
  {
    segmets[0] = display.encodeDigit(home / 10);
    segmets[1] = display.encodeDigit(home % 10) | SEG_DP;
  }
  int away = score.getAwayPoints();
  if (away < 10)
  {
    segmets[2] = 0;
    segmets[3] = display.encodeDigit(away);
  }
  else
  {
    segmets[2] = display.encodeDigit(away / 10);
    segmets[3] = display.encodeDigit(away % 10);
  }
  display.setSegments(segmets);

  msDisplayScore = millis();
}

void setLastCommand(int _cmdLast, ulong _msLastCommand)
{
  cmdLast = _cmdLast;
  msLastCommand = _msLastCommand;
}