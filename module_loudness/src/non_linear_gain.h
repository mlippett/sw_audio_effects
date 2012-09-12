/******************************************************************************\
 * File:	non_linear_gain.h
 * Author: Mark Beaumont
 * Description: Definitions, types, and prototypes for module non_linear_gain
 *
 * Version: 3v3rc1
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

#ifndef _NON_LINEAR_GAIN_H_
#define _NON_LINEAR_GAIN_H_

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <print.h>
#include "types64bit.h"
#include "common_audio.h"

#ifndef NUM_GAIN_CHANS
#define NUM_GAIN_CHANS (2) // For test purposes
#endif // NUM_GAIN_CHANS

#define DEF_GAIN (1 << 2) // Default Gain. NB Currently only power-of-2

typedef struct GAIN_PARAM_TAG // Structure containing Gain parameters
{
	S32_T gain; // Maximum desired gain
} GAIN_PARAM_S;

/******************************************************************************/
S32_T use_loudness( // Call non-linear-gain for one sample
	S32_T inp_samp, // Input Sample
	S32_T cur_chan  // current channel
); // Return Filtered Output Sample
/******************************************************************************/

#ifdef __XC__
// XC File

/******************************************************************************/
void config_loudness( // Configure gain parameters. NB Must be called before use_loudness
	GAIN_PARAM_S &cur_param_s // Reference to structure containing gain parameters
);
/******************************************************************************/

#else //if __XC__
// 'C' File

/******************************************************************************/
void config_loudness( // Configure gain parameters. NB Must be called before use_loudness
	GAIN_PARAM_S * cur_param_ps // Pointer to structure containing gain parameters
);
/******************************************************************************/

#define MAX_ITERS 15 // Maximum allowed number of non-linear-gain iterations before timing breaks 

#define SAMP_BITS ((sizeof(SAMP_CHAN_T) << 3) - 1) // Bits used to hold magnitude of channel sample (e.g. 31)
#define MAX_SAMP (((S64_T)1 << SAMP_BITS) - 1) // Maximum sample value

#define MAGN_BITS 23 // Active magnitude bits (e.g. 23)
#define MAX_MAGN (((S32_T)1 << MAGN_BITS) - 1) // Maximum sample value
 
#define SCALE_BITS (SAMP_BITS - MAGN_BITS) // Bit-shift required to Scale samples from 32 to 24 bits
#define MAX_SCALE ((S32_T)1 << SCALE_BITS) // Maximum value of scale bits
#define HALF_SCALE (MAX_SCALE >> 1) // Half max. scale value (used for rounding)

#define NOISE_BITS 4 // Log2 of low-level Noise threshold
#define LO_BITS (NOISE_BITS << 1) // Log2 of low-level threshold
#define THRESHOLD (1 << LO_BITS) // Low-level Threshold

#define HI_BITS (MAGN_BITS - LO_BITS) // Number of sample bits above threshold 
#define MAX_HI (((S64_T)1 << HI_BITS) - 1) // Maximum value of hi-bits

#define FRAC_BITS 30 // Number of bits used to represent fractional part of coef_g
#define MAX_FRAC ((S64_T)1 << FRAC_BITS) // Max value of fractional bits
#define HALF_FRAC (MAX_FRAC >> 1) // Half of Max fractional value
 
typedef struct GAIN_CHAN_TAG // Structure containing gain data for one channel, updated every sample
{
	S64_T err_s[MAX_ITERS]; // array of diffusion errors for sample
	S64_T err_g[MAX_ITERS]; // array of diffusion errors for gain
} GAIN_CHAN_S;

typedef struct GAIN_TAG // Structure containing gain data for all channels
{
	GAIN_CHAN_S chan_s[NUM_GAIN_CHANS]; // Array of structures containing gain data for each channel
	S32_T num_iters; // number of applications of non-linear-gain transform
	U32_T coef_g; // coefficient for gain shaping
	S32_T init_done;	// Flag indicating gain-shaping is initialised
	S32_T params_set; // Flag indicating Parameters are set
} GAIN_S;

#endif // else __XC__

#endif /* _NON_LINEAR_GAIN_H_ */

// non_linear_gain.h
