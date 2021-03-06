
# This variable should contain a space separated list of all
# the directories containing buildable applications (usually
# prefixed with the app_ prefix)
#
# If the variable is set to "all" then all directories that start with app_
# are built.
BUILD_SUBDIRS = app_slicekit_biquad app_slicekit_delay app_slicekit_loudness app_slicekit_reverb 

XMOS_MAKE_PATH ?= ..
include $(XMOS_MAKE_PATH)/xcommon/module_xcommon/build/Makefile.toplevel

# This variable should contain a space separated list of all
# the directories containing buildable applications (usually
# prefixed with the app_ prefix)
#
# If the variable is set to "all" then all directories that start with app_
# are built.
BUILD_SUBDIRS = app_slicekit_biquad app_slicekit_delay app_slicekit_loudness app_slicekit_reverb 

XMOS_MAKE_PATH ?= ..
include $(XMOS_MAKE_PATH)/xcommon/module_xcommon/build/Makefile.toplevel

Programming Guide
=================

Key Files
---------
   * ``non_linear_gain.c``: Contains 'C' function library
   * ``non_linear_gain.h``: Header file for 'C' function library

Usage
-----
There are 2 functions in the 'C' library, designed to be called from an *.xc file.
   * ``config_loudness()`` Called to do initial configuration of loudness parameters (e.g. max gain). WARNING: This must be called before ...
   * ``use_loudness()`` Called to apply gain to one audio-sample, designed to be called from an *.xc file.

Note well, after initialisation, ``config_loudness()`` can be called again as required to re-configure the gain.

To set the gain value, edit DEF_GAIN in the include file ``module_dsp_loudness/src/non_linear_gain.h`` e.g.

#define DEF_GAIN 4 // Default Gain.

Demo Applications
=================

Loudness Application For SliceKit Board (``app_slicekit_loudness``)
-------------------------------------------------------------------

This application uses module_dsp_loudness to apply non-linear gain to an audio-stream, 
passing through the SliceKit Core board.
The audio is connected to the board using the following Analogue ports:
   * Input 0/1 (Microphone mini-jack)
   * Output 0/1 (Headphone mini-jack)

Makefile
........

The Makefile is found in the top level directory of the application (e.g. ``app_slicekit_loudness``)

The application is for the Slicekit Core Board so the TARGET variable needs to be set in the Makefile: e.g.

TARGET = xp-skc-l2-single-xscope.xn

The number of channels supported in currently 2 or 4, this is set in auto_conf.h: e.g.

NUM_GAIN_CHANS = 2

Running the application with the Command Line Tools
...................................................

In the top level directory of the application (e.g. ``app_slicekit_loudness``)  type
   * xmake clean
   * xmake all

Connect the board to your PC using an XTAG-2

To start the demo type
   * xrun --io bin/app_slicekit_loudness.xe to start the demo

When listening to the output audio at 48kHz sample rate, you should hear the following ...
   * About 8 seconds of the effect (i.e. louder audio), followed by
   * About 8 seconds of the dry (un-effected) signal (i.e. quieter audio)

This cycle will repeat indefinitely.

Trouble-shooting
................

During initialisation, and when the system is reconfigured, 
there may be audible clicks in the audio. This is expected.

During the loud sections, there may be distortion. 
If this occurs, try turning down the volume of the audio source. 
(i.e. the volume level input to the application)

For excessive amounts of gain, (e.g. above 64) there will be distortion 
that can NOT easily be removed by turning down the input level.
Essentially, all volumes levels have been moved to the near maximum extent. 
This will create an output signal that swings quickly from maximum negative to
maximum positive signal levels. The resulting wave will have 'square wave' like
properties, sharp edges near the maximum(minimum) values that contain plenty of
high frequencies that manifest themselves as distortion.

