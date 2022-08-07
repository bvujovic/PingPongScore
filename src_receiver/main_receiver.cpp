#include <RH_ASK.h>
#include <SPI.h>
RH_ASK rf; // pin 11
long ms;

const byte pinLed = LED_BUILTIN;
void ledOn(bool on) { digitalWrite(pinLed, on); }

void setup()
{
  rf.init();
  Serial.begin(9600);
  Serial.println("Started.");
  pinMode(pinLed, OUTPUT);
}

void loop()
{
  uint8_t buf[100];
  uint8_t buflen;

  ms = millis();
  if (rf.recv(buf, &buflen))
  {
    ledOn(true);
    String s = String((char *)buf);
    Serial.println(s.substring(0, buflen));
    delay(5);
    Serial.println(millis() - ms);
    delay(100);
    ledOn(false);
    // Serial.println(s);
    //    int x = buf[0] * 256 + buf[1];
    //    Serial.println(x);
    //    Serial.print("buflen: "); Serial.println(buflen);
  }
  else
    delay(100);
}


// #include <Arduino.h>

// const byte pinLed = LED_BUILTIN;

// void setup()
// {
//   pinMode(pinLed, OUTPUT);
// }

// void loop()
// {
//   digitalWrite(pinLed, true);
//   delay(500);
//   digitalWrite(pinLed, false);
//   delay(500);
// }