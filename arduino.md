# Wire Protocols

* We should run some measurements to see what the per-byte tranmission delay is,
  and whether its necessary to do message, framing, checksums or error
  correction, etc.

The conductor arduino is connected to all the player arduino boards through
uni-directional RS485 serial connections, byte oriented, broadcast mode,
possibly somewhat unreliable. So bytes sent by the conductor are received by
all/most players, in order.

The conductor arduino is connected to the conductor laptop by USB, and each
player arduino is connected to a player laptop by USB. These are bi-directional
serial connections and are likely reliable.

# RS485 

For now, here's the supported on-wire RS485 message formats...

    BEAT: [ 0xBE | ssssssxx ]
    0xBE = preamble and start-of-message marker
    ssssss = 6 bits, a sequence number (0-63) for keeping time
    xx = 2 bits, representing color 1-4 (00=1=green, 01=2=red, 10=3=blue, 11=4=yellow)

Conductor normally sends out a BEAT messages at a steady rate to achieve a
certain beats-per-minute rate. Each beat is numbered (0 to 63), and each has a
color (green, red, blue, or yellow). So we might send this sequence at 120 beats
per minute (one BEAT each 500 ms) in an 8-beat 1-2-3, 1-2, 1-2-3 repeating
pattern, where the incrementing sequence numbers are arbitrary:

    ... BEAT 1 43, BEAT 2 44, BEAT 3 45, BEAT 1 46, BEAT 2 47, BEAT 1 48, BEAT 2 49, BEAT 3 50, ...
    ...   one    -   two    -  three   ,    one   -    two   ,    one   -   two    -   three  , ...

Conductor can send out a BPM message to control the expected beats-per-minute
rate. This could enable the player boards to compensate for missed BEAT
messages, and perhaps to better lock on to the desired rate to adjust for
slightly delayed BEAT messages. (NOT YET IMPLEMENTED)

    BPM: [ 0xAC | bmp | count | pattern ... | 0xCD ]
    0xAC = preamble and start-of-message marker
    bpm = 8 bits, where 0 means "disable", and 1-255 is a beats-per-minute rate.
    count = number of beats that make up a pattern
    pattern = 2 bit color value for each beat, packed into big-endian bytes
    0xCD = end-of-message marker

Conductor can send out a LIST message, whith arbitrary data in the form of an list of numbers.
This is not intepreted in any way, but could be used to pass song-specific
information to player laptops. (NOT YET IMPLEMENTED)

    MSG: [ 0xE3 | count | payload ... | 0x3D ]
    0xE3 = preamble and start-of-message marker
    count = number of payload bytes
    payload = list of numbers, each fitting in one byte
    0x3D = end-of-message marker

# Conductor USB

For now, here's the format for conductor laptop to arduino messages....

Configure the beats-per-minute rate and pattern: `set 120 1 2 3 1 2 1 2 3\n`
If currently beating, this takes effect after the next beat. If the rate is 0,
the rate is not changed, only the pattern. If pattern is missing/empty, then the
previously set pattern will be retained, only the rate will be changed. If the
rate and pattern are missing, the rate and pattern are set back to default
values.

Start beating: `start\n`

Stop beating: `stop\n`

Reset beat sequence number and pattern offset, retaining same rate and pattern: `reset\n`

Send arbitrary list of integers (0-255): `data 1 5 7 0 0 0 99 33 42\n` (NOT YET IMPLEMENTED)

# Player USB
