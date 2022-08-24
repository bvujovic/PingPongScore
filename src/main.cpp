#include <Arduino.h>

typedef unsigned long ulong;

const byte pinIn = A4; // pin from which arduino reads pulses (data pin on SRX882)

#include "Score.h"
Score score;

#include "Display.h"
Display display(score);

#include "SignalDecoder.h"
SignalDecoder signalDec;

// T
//  void scoreToSerial()
//  {
//    Serial.print(score.getHomePoints());
//    Serial.print(':');
//    Serial.print(score.getAwayPoints());
//    Serial.print('\t');
//    if (!score.isGameOver())
//      Serial.println(score.getServe() == Home ? 'H' : 'A');
//    else
//      Serial.println(score.getHomePoints() > score.getAwayPoints() ? "Home Won!" : "Away Won!");
//    display.displayScore(millis());
//  }

void setup()
{
  pinMode(pinIn, INPUT);

  display.setDisplay(A1, A0, 3);
  display.displayScore(millis());
  // T
  //  Serial.begin(9600);
  //  Serial.println("Ping-pong Score started!");
}

void loop()
{
  // reading current pulse from SRX882
  ulong pulse = pulseIn(pinIn, LOW);
  Command cmd = signalDec.refresh(pulse, millis());

  // executing command got from signal decoder
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

  // after every command score should be displayed
  if (cmd != None)
    display.displayScore(millis());

  display.refresh(millis());
}
