#include <Arduino.h>

typedef unsigned long ulong;

const byte pinIn = 11;
const byte pinLed = 4;
ulong pulse;

#include "Score.h"
Score score;

#include "Display.h"
Display display(score);

#include "SignalDecoder.h"
SignalDecoder signalDec;

void scoreToSerial();
void setLastCommand(int _cmdLast, ulong _msLastCommand);

void setup()
{
  pinMode(pinIn, INPUT);
  pinMode(pinLed, OUTPUT);

  display.addDisplay1(A1, A0, 3);
  display.displayScore(millis());
  Serial.begin(9600);
  Serial.println("Ping-pong Score started!");
}

void loop()
{
  pulse = pulseIn(pinIn, LOW);
  Command cmd = signalDec.refresh(pulse, millis());

  if (cmd == HomeClick)
    score.pointWon(Home);
  else if (cmd == MiddleClick)
    ;
  else if (cmd == AwayClick)
    score.pointWon(Away);
  else if (cmd == HomeClick2)
    score.pointRetracted(Home);
  else if (cmd == MiddleClick2)
    score.reset();
  else if (cmd == AwayClick2)
    score.pointRetracted(Away);

  // switch (cmd)
  // {
  // case Home1:
  //   score.pointWon(Home);
  //   break;
  // case Middle1:
  //   break;
  // case Away1:
  //   score.pointWon(Away);
  //   break;
  // case Home2:
  //   score.pointRetracted(Home);
  //   break;
  // case Middle2:
  //   score.reset();
  //   break;
  // case Away2:
  //   score.pointRetracted(Away);
  //   break;
  // case None:
  //   break;
  // }
  if (cmd != None)
    display.displayScore(millis());

  display.refresh(millis());
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
  display.displayScore(millis());
}
