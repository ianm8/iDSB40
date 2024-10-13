# iDSB40
This is a double sideband transceiver, single band (40m), but with a twist (or rather, inverse audio). This is not a new concept but you don't see it now very much. Also generates DSB, AM and CW (and SSB but this is experimental). The advantage over normal DSB is two SSB signals. The issue with DSB is you need to precisely tune to the centre frequency. If you do that with an SSB receiver that's ok, but if you do it with a direct conversion receiver then you can get phase cancellation. With this scheme you don't get that issue because you tune to the "outside" edge of the signal in the same way as an SSB signal. Another problem with DSB is you are effectively only getting half the power compared to SSB.
 
Why DSB at all? Well it's a much simpler circuit than SSB. Only two devices in the whole transceiver part (a quad op amp and an analog mixer). Because the audio is inverted, you don’t tune to the suppressed carrier you tune to the upper or lower sideband in exactly the same way as SSB. I’ve had some nice contacts and also reports of excellent audio (that was a big surprise). The other station doesn’t know it’s DSB especially if they don’t see the spectrum. But even with a spectrum display the other sideband is separated from the one you’re tuned to, so unless you pay particular attention you’ll probably just think it’s another signal!

# How does it work?
The way it works is essentially the usual DSB transceiver with a double balance mixer for both transmit and receive (so it’s a direct conversion receiver). The key difference is that the inverse audio is generated using DSP in the Pico. That signal is then mixed with the carrier giving two adjacent sidebands. First the mic signal is put through a low pass filter at 2400Hz. Then a BFO at 2700Hz is applied which generates an LSB (inverted) and USB (not inverted) signal centred at 2700Hz (this is the expected hehaviour of a double balanced mixer). Then another low pass filter removes the USB and leaves the LSB which is the inverted audio. That signal is then mixed in the double balanced mixer to give an LSB signal (which is now normal audio and not inverted) and a USB signal (which is now inverted audio) with a gap of a few hundred Hz in the middle.

![alt text](https://github.com/ianm8/iDSB40/blob/main/docs/iDSB40-1.jpg?raw=true)

![alt text](https://github.com/ianm8/iDSB40/blob/main/docs/iDSB40-2.jpg?raw=true)

![alt text](https://github.com/ianm8/iDSB40/blob/main/docs/iDSB40-PCB-Complete.jpg?raw=true)

![alt text](https://github.com/ianm8/iDSB40/blob/main/docs/iDSB40-Pico.jpg?raw=true)
