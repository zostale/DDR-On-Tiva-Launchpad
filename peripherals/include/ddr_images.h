// Copyright (c) 2014-2016, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef __ECE353_IMAGES_H__
#define __ECE353_IMAGES_H__

#include <stdint.h>

typedef struct {
  uint16_t width;
  uint16_t height;
} IMAGE_INFO;

#define ARROWS_HEIGHT_PIXELS    39
#define ARROWS_WIDTH_PIXELS    39

/* Bitmap info for left_arrow */
extern const uint8_t left_arrowBitmaps[];

/* Bitmap info for right_arrow */
extern const uint8_t right_arrowBitmaps[];

/* Bitmap info for up_arrow */
extern const uint8_t up_arrowBitmaps[];

/* Bitmap info for down_arrow */
extern const uint8_t down_arrowBitmaps[];

extern const uint8_t rxModeBitmaps[];
extern const uint8_t rxModeWidthPixels;
extern const uint8_t rxModeHeightPixels;

extern const uint8_t txModeBitmaps[];
extern const uint8_t txModeWidthPixels;
extern const uint8_t txModeHeightPixels;

extern const uint8_t config2Bitmaps[];
extern const uint8_t config2WidthPixels;
extern const uint8_t config2HeightPixels;

extern const uint8_t bucky2Bitmaps[];
extern const uint8_t bucky2WidthPixels;
extern const uint8_t bucky2HeightPixels;

/* Bitmap info for ddrbw */
extern const uint8_t ddrbwBitmaps[];
extern const uint8_t ddrbwWidthPixels;
extern const uint8_t ddrbwHeightPixels;

extern const uint8_t sitkaSmall_12ptBitmaps[];

/* Bitmap info for ddrlogo */
extern const uint8_t ddrlogoBitmaps[];
extern const uint8_t ddrlogoWidthPixels;
extern const uint8_t ddrlogoHeightPixels;

/* Bitmap info for pause */
extern const uint8_t pauseBitmaps[];
extern const uint8_t pauseWidthPixels;
extern const uint8_t pauseHeightPixels;

/* Bitmap info for dance_Dance_Revolution */
extern const uint8_t dance_Dance_RevolutionBitmaps[];
extern const uint8_t dance_Dance_RevolutionWidthPixels;
extern const uint8_t dance_Dance_RevolutionHeightPixels;


/* Bitmap info for girl */
extern const uint8_t girlBitmaps[];
extern const uint8_t girlWidthPixels;
extern const uint8_t girlHeightPixels;


/* Bitmap info for win */
extern const uint8_t winBitmaps[];
extern const uint8_t winWidthPixels;
extern const uint8_t winHeightPixels;


/* Bitmap info for lOSEBITMAP */
extern const uint8_t lOSEBITMAPBitmaps[];
extern const uint8_t lOSEBITMAPWidthPixels;
extern const uint8_t lOSEBITMAPHeightPixels;


#endif
