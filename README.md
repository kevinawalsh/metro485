Global Metro
============

A cobbled-together midi clock synchronizer for a cluster of laptops runnning Max/MSP. The goal is to
allow a cluster of laptops all running Max/MSP -- a "laptop orchestra" -- to use a common global
clock source. This serves as a synchronized metronome and lets events be triggered in unison across
the orchestra.

Global Metro is build using:

* Hardware -- A custom-designed board connected to each laptop over USB. Each board has an Arduino
  Nano, RS485 serial tranceiver, and RJ45 jack, and are connected together using regular cat5
  cabling. One board is the conductor, responsible for setting the tempo, enabling or disabling
  beats, etc. The remaining boards are players, simply following the conductor's lead.

* Daemon -- a small bit of software running on each laptop, to communicate with the board.

* Patches -- Max8 components to interface between Max8/MSP and the daemon.

# Current Status

* player hardware - custom fabricated PCB (EasyEDA / JLPCB) with hand-soldered components
  - 3 breadboard prototypes tested
  - 17 PCBs made, 1 soldered
  - TODO: solder remaining PCBs
* conductor hardware - proto-PCB and hand-soldered components
  - 1 breadboard prototype with 3 RJ45 jacks tested
  - TODO: prototype with 15 RJ45 jacks
* daemon - prototypes in progress
  - prototype in Java
  - TODO: cleanup, add features, and document
* patches - prototypes in progress
  - prototype
  - TODO: cleanup, add features, and document

# Player Hardware

Block diagram:

    [cat5 from conductor board]
    | |
     \ \    +--------+
      \ \___|        |    +-------------------+    +----------+
       \____|  RJ45  |----| RS485 Transceiver |----| Magneto- |
            |        |    +-------------------+    | Isolator |
            +--------+                             +----------+
                                                        |
                                               +--------------+
                                               | Arduino Nano |==
                                               +--------------+  \\
                                                |   |   |   |     \\ 
                                               LED LED LED LED     [usb to laptop]
                                                   
RJ45 connector:

                     Player usage                   Ethernet usage
    pin 1 : N/C      unused                         TX Data +
    pin 2 : N/C      unused                         TX Data -
    pin 3 : RSGND    in reference ground            RX Data +
    pin 4 : RSA      in signal (+)                  Bidir1 Data + / PoE VCC / unused
    pin 5 : RSB      in signal (-)                  Bidir1 Data - / PoE VCC / unused
    pin 6 : RSVCC    in power (5v)                  RX Data -
    pin 7 : RSTE     in transmit enable             Bidir2 Data + / PoE GND / unused
    pin 8 : RSTX     out transmit request/data      Bidir2 Data - / PoE GND / unused

Notes:
* A regular "straight-through" cat5 cable should be used, not the less-common "cross-over" cable. A
  straight cable will have identical wire color ordering on both ends. If a cross-over cable is
  mistakenly used, the player board won't get power, which should hopefully mean it simply doesn't
  work and causes no harm.
* The player board has a 10k Ohm pull-down between `RSTE` and reference ground. This means the 
  player's RS485 transceiver is normally in receive mode, with the RSA/RSB data signals coming to player
  from the conductor. If the conductor brings RSTE high, then the RS485 transceiver switches to
  transmit mode, making the RSA/RSB data signals go from this player board to the conductor board. This
  feature isn't yet supported on the conductor board.
* RSTX allows the player to send a signal to the conductor board. This could be used to send data
  (probably unreliable, and distance could be an issue), or perhaps just a "request to send"
  indication. If the conductor pulls RSTE high so that the RS485 transceiver is in transmit mode, then
  RSTX is also used to drive the A/B signals, which would allow the player to send data more reliably
  to the conductor. Again, this isn't yet supported on the conductor board.

Arduino pinout and ports:

              Name     Player usage
    pin 1  :  TX1
    pin 2  :  RX0
    pin 3  :  RST
    pin 4  :  GND
    pin 5  :  D2       LED2 active low (green)
    pin 6  :  D3       LED3 active low (red)
    pin 7  :  D4       LED4 active low (blue)
    pin 8  :  D5       LED5 active low (yellow)
    pin 9  :  D6       broken out on PCB
    pin 10 :  D7
    pin 11 :  D8
    pin 12 :  D9       broken out on PCB
    pin 13 :  D10      broken out on PCB
    pin 14 :  D11      broken out on PCB
    pin 15 :  D12      broken out on PCB
    pin 16 :  D13      LED on Arduino Nano
    pin 17 :  3V3
    pin 18 :  AREF
    pin 19 :  A0       broken out on PCB
    pin 20 :  A1       broken out on PCB
    pin 21 :  A2       broken out on PCB
    pin 22 :  A3       broken out on PCB
    pin 23 :  A4       broken out on PCB
    pin 24 :  A5       broken out on PCB
    pin 25 :  A6       broken out on PCB
    pin 26 :  A7       broken out on PCB
    pin 27 :  +5V      VCC for LEDs and magneto-isolator, also broken out on PCB
    pin 28 :  RST
    pin 29 :  GND      GND for magneto-isolator, also broken out on PCB
    pin 30 :  VIN

Other notes on player board:

* The choice of RJ45 pinout for the player probably wasn't ideal. Should have matched PoE standards?
* The LED polarity on player board silkscreen as accidentally reversed. Short leg of LED (negative)
  should go in the hole marked "+".
* Player board resistor values: R1=0, R2=2.2k, R3=330 R4=330, R5=330
  (based on testing, Green LED is far brighter than all others, and 330 is
  plenty bright for the other colors).
* The R1 pulldown for RSTE should be 0 ohms, b/c the rs485 transceiver module has a 10k
  pullup on that same line. For v1.1 maybe this resistor should be removed,
  connecting DE/RE, RSTE (RJ45 pin 7), and RSGND (RJ45 pin 3), meaning that the
  player can never transmit using RS485. Alternatively, for v1.1 maybe the
  resistor should be removed, leaving leaving DE/RE connected only to RSTE (RJ45
  pin 7), in which case the coordinator must ground that line to avoid having
  both sides transmit. For v1.0 boards, R1 should be a jumper on the underside
  of the board, to allow for later modifications (e.g. removing entirely, or
  using a strong pulldown).
* Resistors should perhaps be mounted on underside of board, to allow for
  brightness leveling of LEDs?
* Player board PCB should get ground plane infills for v1.1?

# Conductor Hardware

* ADuM 1201 magneto-isolator needs about max 1.1mA on each of the VDD supplies,
  IA and IB are max 10uA,
  OA and OB can sink or source 11mA maximum
* Max485 module has 10k pullups on all pins, so we can leave the RE and DE pins floating,
  and the DI pin should only sink about 0.5mA. We should be able to support fanout 15 with a single
  magneto-isolator, but that's cutting it kind of close. Probably better to use two isolators.

Simplified circuit for trial:
* Each RS485 board (26-28 of them, half in tx mode, half in rx mode), could draw
  200 mA or more, since there are *two* 120ohm terminating resistors on each
  segment. This is more than the +5v pin on the nano can supply. So we really
  should use a separate supply to drive these.
* Do we need isolators? Maybe not? Let's try without them, with a single ground.

Block diagram:

    Unearthed    Arduino         Unearthed
     Laptop      Nano            Regulated       Many RS 485  
      USB ======= USB            Supply          Transceivers  Uplink RS485
                  D2 ->-------------------------> DI           Transeiver    OLED
                  D3 <---------------------------------------<- RO           Display
                  GND -------------- GND -------- GND --------- GND --------- GND
                  +5v ------------<- +5v ->------ VCC --------- VCC --------- VCC
                  D4 ->--LED--/\/\/---|                                ,----- SDA
                  D5 ->--LED--/\/\/---|                               / ,---- SCL
                  D6 ->--LED--/\/\/---|                              / /
                  D7 ->--LED--/\/\/---'                             / /
                  A4 ->--------------------------------------------' /
                  A5 ->---------------------------------------------'
                                                                         
