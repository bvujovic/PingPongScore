//* This code is executing on Attiny85 w/ stx882 (transmitter).
//* Based on https://github.com/perja12/nexa_remote_control

#include <Arduino.h>
#include <avr/power.h>
#include <avr/sleep.h>

#define TX_PIN 0

#define CMD_NONE 0
#define CMD_1 1
#define CMD_2 2
#define CMD_3 3

// Pinout
// RESET PB5 (5/A0) *o**** VCC
//       PB3 (3/A3) ****** PB2 (2/A1)
//       PB4 (4/A2) ****** PB1 (1)
//              GND ****** PB0 (0)

volatile int cmd = CMD_NONE;

ISR(PCINT0_vect)
{
  cli();
  if (!bit_is_set(PINB, PB1))
    cmd = CMD_1;
  if (!bit_is_set(PINB, PB2))
    cmd = CMD_2;
  if (!bit_is_set(PINB, PB3))
    cmd = CMD_3;
}

void setup()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // Turn off ADC to save power.
  ADCSRA &= ~bit(ADEN);

  pinMode(PB1, INPUT_PULLUP);
  pinMode(PB2, INPUT_PULLUP);
  pinMode(PB3, INPUT_PULLUP);

  // Configure pin change interrupt.
  PCMSK |= _BV(PCINT1);
  PCMSK |= _BV(PCINT2);
  PCMSK |= _BV(PCINT3);
  GIFR |= bit(PCIF);  // clear any outstanding interrupts
  GIMSK |= bit(PCIE); // enable pin change interrupts
}

// Transmit HIGH/LOW and then delay for itv milliseconds.
void send(uint8_t val, uint8_t itv)
{
  digitalWrite(TX_PIN, val);
  delayMicroseconds(itv * 1000);
}

void loop()
{
  // Set TX_PIN to INPUT in order to save power.
  pinMode(TX_PIN, INPUT);

  // Enable interrupts again, go to sleep and wait for intterrupt.
  sei();
  go_to_sleep();

  cli(); // disable interupts
  if (cmd != CMD_NONE)
  {
    // Wakes up here.
    pinMode(TX_PIN, OUTPUT);

    for (int i = 0; i < 5; i++)
    {
      send(HIGH, 1);
      send(LOW, 3 + cmd);
    }
    send(HIGH, 1);

    // for (int i = 0; i < 4 + cmd * 2; i++)
    // {
    //   send(HIGH, 1);
    //   send(LOW, 5);
    // }
    // send(HIGH, 1);
  }
  // Avoid getting a new interrupt because of button bounce.
  delay(50);

  // if (cmd = CMD_1)
  // {
  //   // unsigned long ms = millis();
  //   // pinMode(PB1, INPUT);
  //   pinMode(PB1, INPUT_PULLUP);
  //   while (!digitalRead(PB1))
  //   {
  //     delay(10);
  //   }
  //   for (int i = 0; i < 4; i++)
  //   {
  //     send(HIGH, 1);
  //     send(LOW, 5);
  //   }
  // }
  // send(HIGH, 1);
  sei(); // enable interupts

  // unsigned long ms = millis();
  // while (!bit_is_set(PINB, PB3))
  //   delay(50);
  // if (millis() > ms + 500)
  // {
  //   cli(); // disable interupts
  //   for (int i = 0; i < 4; i++)
  //   {
  //     send(HIGH, 1);
  //     send(LOW, 5);
  //   }
  //   send(HIGH, 1);
  //   sei(); // enable interupts
  // }
  cmd = CMD_NONE;
}

void go_to_sleep()
{
  power_all_disable(); // power off ADC, Timer 0 and 1, serial interface
  sleep_enable();
  sleep_cpu();
  sleep_disable();
  power_all_enable(); // power everything back on
}