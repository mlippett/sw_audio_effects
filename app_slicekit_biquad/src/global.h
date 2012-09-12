/******************************************************************************\
 * Header:  global
 * File:    global.h
 * Author: Mark Beaumont
 * Description: Global Definitions, types, and prototypes for reverb app
 *
 * Version: 0v1
 * Build:
 *
 * The copyrights, all other intellectual and industrial
 * property rights are retained by XMOS and/or its licensors.
 * Terms and conditions covering the use of this code can
 * be found in the Xmos End User License Agreement.
 *
 * Copyright XMOS Ltd 2012
 *
 * In the case where this code is a modification of existing code
 * under a separate license, the separate license terms are shown
 * below. The modifications to the code are still covered by the
 * copyright notice above.
 *
\******************************************************************************/

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

// Core that Audio Slice is connected to 
#define AUDIO_IO_CORE 		1

// Audio sample frequency (Hz) 
#define SAMP_FREQ			48000

// Audio Slice hardware version 
#define AUDIO_SLICE_HW		1

#define I2S_CHANS_DAC 		2
#define I2S_CHANS_ADC 		2

// Audio clocking defines  
// Master clock defines (Hz) 
#define MCLK_FREQ_441       (512*44100)   // 44.1, 88.2 etc 
#define MCLK_FREQ_48        (512*48000)   // 48, 96 etc 

#if (SAMP_FREQ%22050==0)
#define MCLK_FREQ           MCLK_FREQ_441
#elif (SAMP_FREQ%24000==0)
#define MCLK_FREQ           MCLK_FREQ_48
#else
#error Unsupported sample frequency
#endif

// Bit clock divide 
#define BCLK_DIV        (MCLK_FREQ / (SAMP_FREQ * 64))


// Ports 
#if (AUDIO_SLICE_HW == 1)
#define PORT_I2S_DAC_DATA0	XS1_PORT_1D
#define PORT_I2S_DAC_DATA1  XS1_PORT_1M
#define PORT_I2S_ADC_DATA0  XS1_PORT_1I
#define PORT_I2S_ADC_DATA1	XS1_PORT_1L
#define PORT_I2S_LRCLK		XS1_PORT_1H
#define PORT_I2S_BCLK		XS1_PORT_1A
#define PORT_MCLK_IN		XS1_PORT_1E

#define PORT_GPIO			XS1_PORT_4E
#define PORT_I2C			XS1_PORT_4F

#else
#error currently not un-supported slice hw version
#endif
/*****************************************************************************/

#define I2S_PORTS_DAC 		(I2S_CHANS_DAC>>1)
#define I2S_PORTS_ADC 		(I2S_CHANS_ADC>>1)

#endif // ifndef _GLOBAL_H_ 
/*****************************************************************************/
// global.h
