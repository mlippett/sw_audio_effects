Audio Long Delay-line Function Library
======================================

:scope: Early Development
:description: A SDRAM_Delay library using a user-configurable number of delay-taps, max 32_taps x 4_channels at 48 KHz audio.
:keywords: audio, dsp, delay, echo, SDRAM, Memory-slice
:boards: XA-SK-AUDIO, XA-SK-SDRAM

Features
--------

   * Offers programmable delay taps:
   * 8 taps for 4 channels at 192 KHz
   * Uses double-buffering to 'hide' latency of reading/writing to SDRAM
