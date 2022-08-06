#include <RH_ASK.h>
RH_ASK rf; // pin 12
//#include <SPI.h>

// B const byte pinLed = LED_BUILTIN;
void ledOn(bool on) { digitalWrite(LED_BUILTIN, on); }

void setup()
{
  rf.init();
  pinMode(LED_BUILTIN, OUTPUT);
  // Serial.begin(9600);
  //  digitalWrite(LED_BUILTIN, false);
}

void loop()
{
  //  //B const char *msg = "...!";
  //  int secs = millis() / 1000;
  //  //T Serial.println(secs);
  //  char msg[7];
  //  itoa(secs, msg, 10); // int, string buffer, base
  //  // Serial.print((byte)msg[0]); Serial.print(" - "); Serial.println((int)msg[1]);
  //  // Serial.print(msg); Serial.print(" - "); Serial.println(strlen(msg));
  //  rf.send((uint8_t*)msg, strlen(msg));
  //  rf.waitPacketSent();

  char msg[] = {'a', 0};
  rf.send((uint8_t *)msg, 2);
  rf.waitPacketSent();

  ledOn(true);
  delay(200);
  ledOn(false);
  delay(4800);
}
