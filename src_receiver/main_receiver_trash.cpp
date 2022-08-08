//#include <EEPROMing.h>
// EEPROMing ee;
#include <Arduino.h>
#include <Wire.h>

typedef unsigned long ulong;

const byte pinIn = 11; // ex 1
const byte pinLed = 4;
ulong pul, lastPul;

const byte cntPulses = 5;
#include <CircularBuffer.h>
CircularBuffer<ulong, cntPulses> lastPulses;           // poslednjih cntPulses pulseva
ulong targetPulses[] = {2675, 2000, 3000, 4000, 5000}; // sekvenca pulseva koju cekam

void requestEvent()
{
  for (int i = 0; i < cntPulses; i++)
    Wire.write(lastPulses[i] / 100);
}

void setup()
{
  //      ee.MemToDisplay(200);
  //      while(1)
  //        delay(100);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event

  pinMode(pinIn, INPUT);
  pinMode(pinLed, OUTPUT);
  //  ee.SetWritePos(200);

  Serial.begin(9600);
  Serial.println("starttt");
}

ulong msLastSignal = 0;
ulong cnt1 = 0, cnt2 = 0, cnt3 = 0;

void loop()
{
  pul = pulseIn(pinIn, LOW);

  if (pul > 3888 && pul < 3952)
  {
    cnt1++;
    msLastSignal = millis();
  }
  // 4863 - 4944
  if (pul > 4860 && pul < 4940)
  {
    cnt2++;
    // B Serial.println(pul);
    msLastSignal = millis();
  }
  if (pul > 5832 && pul < 5928)
  {
    cnt3++;
    msLastSignal = millis();
  }

  if (msLastSignal > 0 && millis() > msLastSignal + 20) //* probati ovo sa +5 umesto +20 msec
  {
    // B Serial.println();
    if (cnt1 >= 4 && cnt1 <= 6)
      Serial.println(String("cmd1: ") + cnt1);
    if (cnt2 >= 4 && cnt2 <= 6)
      Serial.println(String("cmd2: ") + cnt2);
    if (cnt3 >= 4 && cnt3 <= 6)
      Serial.println(String("cmd3: ") + cnt3);
    cnt1 = cnt2 = cnt3 = 0;
    msLastSignal = 0;
  }

  // if (pul != lastPul)
  // {
  //     // ee.Write(pul / 100);
  //     int cntHits = 0;
  //     lastPulses.push(pul);
  //     ulong lastTarget = targetPulses[cntPulses - 1];
  //     if (pul > lastTarget - 100 && pul < lastTarget + 200)
  //     {
  //         for (int i = 0; i < cntPulses; i++)
  //         {
  //             int diff = lastPulses[i] - targetPulses[i];
  //             if (diff > -100 && diff < 200)
  //                 cntHits++;
  //             else
  //                 break;
  //         }
  //     }
  //     if (cntHits == cntPulses)
  //     {
  //         digitalWrite(pinLed, true);
  //         delay(333);
  //         digitalWrite(pinLed, false);
  //     }

  //     // if (cntHits == cntPulses)
  //     // if (pul > 2675 - 100 && pul < 2675 + 200)

  //     //    int diff = lastPulses[0] - targetPulses[0];
  //     //    if (diff > -100 && diff < 200)
  //     //    {
  //     //      for (int i = 0; i < cntPulses; i++)
  //     //        ee.Write(lastPulses[i] / 100);
  //     //      digitalWrite(pinLed, true);
  //     //      delay(333);
  //     //      digitalWrite(pinLed, false);
  //     //    }
  //     //    cntHits = 0;
  // }
  lastPul = pul;
}

/*

  // #include <Arduino.h>

  //const int rxPin = 11;
  //const byte pinLed = LED_BUILTIN;
  const int rxPin = 0;
  const byte pinLed = 1;

  //void printResult(unsigned long sender, bool group, bool on, unsigned int recipient)
  //{
  //  Serial.println(millis());
  //  Serial.print("Sender ");
  //  Serial.println(sender);
  //  if (group)
  //    Serial.println("group command");
  //  Serial.println(on ? "on" : "off");
  //  Serial.print("recipient ");
  //  Serial.println(recipient);
  //  Serial.println();
  //}

  #include <EEPROMing.h>
  EEPROMing ee;

  unsigned long myPulseIn()
  {
  unsigned long x = pulseIn(rxPin, LOW, 1000000);  // *1.5
  //  if (x > 20000)
  //    ee.Write(1);
  //  else if (x > 2000)
  //    ee.Write(x / 100);
  return x;
  }

  void saveee(int id, unsigned long x)
  {
  ee.Write(id);
  if (x > 20000)
    ee.Write(1);
  else if (x > 2000)
    ee.Write(2);
  else if (x > 200)
    ee.Write(x / 10);
  else
    ee.Write(111);
  }

  void setup()
  {
  //  ee.MemToDisplay(50);
  //  while (1)
  //    delay(100);

  pinMode(rxPin, INPUT);
  pinMode(pinLed, OUTPUT);

  digitalWrite(pinLed, true);
  delay(200);
  digitalWrite(pinLed, false);
  ee.SetWritePos(50);
  }

  void loop()
  {
  int i = 0;
  unsigned long t = 0;

  byte prevBit = 0;
  byte bit = 0;

  unsigned long sender = 0;
  bool group = false;
  bool on = false;
  unsigned int recipient = 0;

  // latch 1
  while ((t < 9480 || t > 10350))
  {
    t = myPulseIn();
  }
  //  saveee(1, t);

  // latch 2
  while (t < 2550 || t > 2700)
  {
    t = myPulseIn();
  }
  //  saveee(2, t);
  i=1;
  //  // data
  //  while (i < 64)
  //  {
  //    //    Serial.print("data: ");
  //    //    Serial.println(i);
  //
  //    t = myPulseIn();
  //
  //    if (t > 200 && t < 365)
  //    {
  //      bit = 0;
  //    }
  //    else if (t > 1000 && t < 1360)
  //    {
  //      bit = 1;
  //    }
  //    else
  //    {
  //      bit = 0;
  //      saveee(i, t);
  //      i = 0;
  //      break;
  //    }
  //
  //    if (i % 2 == 1)
  //    {
  //      if ((prevBit ^ bit) == 0)
  //      { // must be either 01 or 10, cannot be 00 or 11
  //        // saveee(4, i);
  //        i = 0;
  //        break;
  //      }
  //
  //      if (i < 53)
  //      { // first 26 data bits
  //        sender <<= 1;
  //        sender |= prevBit;
  //      }
  //      else if (i == 53)
  //      { // 26th data bit
  //        group = prevBit;
  //      }
  //      else if (i == 55)
  //      { // 27th data bit
  //        on = prevBit;
  //      }
  //      else
  //      { // last 4 data bits
  //        recipient <<= 1;
  //        recipient |= prevBit;
  //      }
  //    }
  //
  //    prevBit = bit;
  //    ++i;
  //  }

  // interpret message
  if (i > 0)
  {
    //    Serial.print("i: ");
    //    Serial.println(i);
    //    printResult(sender, group, on, recipient);
    digitalWrite(pinLed, true);
    delay(200);
    digitalWrite(pinLed, false);
  }
  }

*/
