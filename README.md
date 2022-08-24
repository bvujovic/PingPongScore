# PingPongScore

Transmitter (ATtiny85, STX882, buttons, LIR2032) sends signals to receiver (Arduino Nano, SRX882, TM1637) that keeps and displays ping pong (table tennis) score.

A Game is played to 11 points; must be won by two points.


## Transmitter
![Transmitter](https://github.com/bvujovic/PingPongScore/blob/main/docs/prototype_transmitter.jpg)
Transmitter - prototype

![Transmitter](https://github.com/bvujovic/PingPongScore/blob/main/docs/finished_transmitter.jpg)
Transmitter - finished

## Receiver
![Receiver](https://github.com/bvujovic/PingPongScore/blob/main/docs/prototype_receiver.jpg)


## TODO
- [x] Moving code for signal recognition to a new class
- [x] Improving code comments
- [ ] Displaying score on 2 TM1637s