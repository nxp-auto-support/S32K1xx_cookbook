/*
 * Copyright (c) 2014 - 2016, Freescale Semiconductor, Inc.
 * Copyright (c) 2016 - 2018, NXP.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TFT_LCD_H_
#define TFT_LCD_H_

/* TFT LCD Size */
#define TFT_WIDTH		(240)
#define TFT_HEIGHT      (320)

/* TFT Orientation Selection */
//#define TFT_ORIGIN 	(0x48)  			/* (Portrait) Origin at upper left */
#define TFT_ORIGIN 		(0x28)  			/* (Landscape) Origin at upper right */
//#define TFT_ORIGIN 	(0x88)  			/* (Portrait) Origin at bottom right */
//#define TFT_ORIGIN 	(0xE8)  			/* (Landscape) Origin at bottom left */

/* Color Definitions */
#define BLACK           (0x0000)
#define BLUE            (0x001F)
#define RED             (0xF800)
#define GREEN           (0x07E0)
#define CYAN            (0x07FF)
#define MAGENTA         (0xF81F)
#define YELLOW          (0xFFE0)
#define WHITE           (0xFFFF)

/* LCD Font Array */
#define TFT_FONT \
{\
    0x00, 0x00, 0x00, 0x00, 0x00,   /* 0x00 */\
    0x3E, 0x5B, 0x4F, 0x5B, 0x3E,   /* 0x01 */\
    0x3E, 0x6B, 0x4F, 0x6B, 0x3E,   /* 0x02 */\
    0x1C, 0x3E, 0x7C, 0x3E, 0x1C,   /* 0x03 */\
    0x18, 0x3C, 0x7E, 0x3C, 0x18,   /* 0x04 */\
    0x1C, 0x57, 0x7D, 0x57, 0x1C,   /* 0x05 */\
    0x1C, 0x5E, 0x7F, 0x5E, 0x1C,   /* 0x06 */\
    0x00, 0x18, 0x3C, 0x18, 0x00,   /* 0x07 */\
    0xFF, 0xE7, 0xC3, 0xE7, 0xFF,   /* 0x08 */\
    0x00, 0x18, 0x24, 0x18, 0x00,   /* 0x09 */\
    0xFF, 0xE7, 0xDB, 0xE7, 0xFF,   /* 0x0A */\
    0x30, 0x48, 0x3A, 0x06, 0x0E,   /* 0x0B */\
    0x26, 0x29, 0x79, 0x29, 0x26,   /* 0x0C */\
    0x40, 0x7F, 0x05, 0x05, 0x07,   /* 0x0D */\
    0x40, 0x7F, 0x05, 0x25, 0x3F,   /* 0x0E */\
    0x5A, 0x3C, 0xE7, 0x3C, 0x5A,   /* 0x0F */\
    0x7F, 0x3E, 0x1C, 0x1C, 0x08,   /* 0x10 */\
    0x08, 0x1C, 0x1C, 0x3E, 0x7F,   /* 0x11 */\
    0x14, 0x22, 0x7F, 0x22, 0x14,   /* 0x12 */\
    0x5F, 0x5F, 0x00, 0x5F, 0x5F,   /* 0x13 */\
    0x06, 0x09, 0x7F, 0x01, 0x7F,   /* 0x14 */\
    0x00, 0x66, 0x89, 0x95, 0x6A,   /* 0x15 */\
    0x60, 0x60, 0x60, 0x60, 0x60,   /* 0x16 */\
    0x94, 0xA2, 0xFF, 0xA2, 0x94,   /* 0x17 */\
    0x08, 0x04, 0x7E, 0x04, 0x08,   /* 0x18 */\
    0x10, 0x20, 0x7E, 0x20, 0x10,   /* 0x19 */\
    0x08, 0x08, 0x2A, 0x1C, 0x08,   /* 0x1A */\
    0x08, 0x1C, 0x2A, 0x08, 0x08,   /* 0x1B */\
    0x1E, 0x10, 0x10, 0x10, 0x10,   /* 0x1C */\
    0x0C, 0x1E, 0x0C, 0x1E, 0x0C,   /* 0x1D */\
    0x30, 0x38, 0x3E, 0x38, 0x30,   /* 0x1E */\
    0x06, 0x0E, 0x3E, 0x0E, 0x06,   /* 0x1F */\
    0x00, 0x00, 0x00, 0x00, 0x00,   /* 0x20 */\
    0x00, 0x00, 0x5F, 0x00, 0x00,   /* 0x21 */\
    0x00, 0x07, 0x00, 0x07, 0x00,   /* 0x22 */\
    0x14, 0x7F, 0x14, 0x7F, 0x14,   /* 0x23 */\
    0x24, 0x2A, 0x7F, 0x2A, 0x12,   /* 0x24 */\
    0x23, 0x13, 0x08, 0x64, 0x62,   /* 0x25 */\
    0x36, 0x49, 0x56, 0x20, 0x50,   /* 0x26 */\
    0x00, 0x08, 0x07, 0x03, 0x00,   /* 0x27 */\
    0x00, 0x1C, 0x22, 0x41, 0x00,   /* 0x28 */\
    0x00, 0x41, 0x22, 0x1C, 0x00,   /* 0x29 */\
    0x2A, 0x1C, 0x7F, 0x1C, 0x2A,   /* 0x2A */\
    0x08, 0x08, 0x3E, 0x08, 0x08,   /* 0x2B */\
    0x00, 0x80, 0x70, 0x30, 0x00,   /* 0x2C */\
    0x08, 0x08, 0x08, 0x08, 0x08,   /* 0x2D */\
    0x00, 0x00, 0x60, 0x60, 0x00,   /* 0x2E */\
    0x20, 0x10, 0x08, 0x04, 0x02,   /* 0x2F */\
    0x3E, 0x51, 0x49, 0x45, 0x3E,   /* 0x30 */\
    0x00, 0x42, 0x7F, 0x40, 0x00,   /* 0x31 */\
    0x72, 0x49, 0x49, 0x49, 0x46,   /* 0x32 */\
    0x21, 0x41, 0x49, 0x4D, 0x33,   /* 0x33 */\
    0x18, 0x14, 0x12, 0x7F, 0x10,   /* 0x34 */\
    0x27, 0x45, 0x45, 0x45, 0x39,   /* 0x35 */\
    0x3C, 0x4A, 0x49, 0x49, 0x31,   /* 0x36 */\
    0x41, 0x21, 0x11, 0x09, 0x07,   /* 0x37 */\
    0x36, 0x49, 0x49, 0x49, 0x36,   /* 0x38 */\
    0x46, 0x49, 0x49, 0x29, 0x1E,   /* 0x39 */\
    0x00, 0x00, 0x14, 0x00, 0x00,   /* 0x3A */\
    0x00, 0x40, 0x34, 0x00, 0x00,   /* 0x3B */\
    0x00, 0x08, 0x14, 0x22, 0x41,   /* 0x3C */\
    0x14, 0x14, 0x14, 0x14, 0x14,   /* 0x3D */\
    0x00, 0x41, 0x22, 0x14, 0x08,   /* 0x3E */\
    0x02, 0x01, 0x59, 0x09, 0x06,   /* 0x3F */\
    0x3E, 0x41, 0x5D, 0x59, 0x4E,   /* 0x40 */\
    0x7C, 0x12, 0x11, 0x12, 0x7C,   /* 0x41 */\
    0x7F, 0x49, 0x49, 0x49, 0x36,   /* 0x42 */\
    0x3E, 0x41, 0x41, 0x41, 0x22,   /* 0x43 */\
    0x7F, 0x41, 0x41, 0x41, 0x3E,   /* 0x44 */\
    0x7F, 0x49, 0x49, 0x49, 0x41,   /* 0x45 */\
    0x7F, 0x09, 0x09, 0x09, 0x01,   /* 0x46 */\
    0x3E, 0x41, 0x41, 0x51, 0x73,   /* 0x47 */\
    0x7F, 0x08, 0x08, 0x08, 0x7F,   /* 0x48 */\
    0x00, 0x41, 0x7F, 0x41, 0x00,   /* 0x49 */\
    0x20, 0x40, 0x41, 0x3F, 0x01,   /* 0x4A */\
    0x7F, 0x08, 0x14, 0x22, 0x41,   /* 0x4B */\
    0x7F, 0x40, 0x40, 0x40, 0x40,   /* 0x4C */\
    0x7F, 0x02, 0x1C, 0x02, 0x7F,   /* 0x4D */\
    0x7F, 0x04, 0x08, 0x10, 0x7F,   /* 0x4E */\
    0x3E, 0x41, 0x41, 0x41, 0x3E,   /* 0x4F */\
    0x7F, 0x09, 0x09, 0x09, 0x06,   /* 0x50 */\
    0x3E, 0x41, 0x51, 0x21, 0x5E,   /* 0x51 */\
    0x7F, 0x09, 0x19, 0x29, 0x46,   /* 0x52 */\
    0x26, 0x49, 0x49, 0x49, 0x32,   /* 0x53 */\
    0x03, 0x01, 0x7F, 0x01, 0x03,   /* 0x54 */\
    0x3F, 0x40, 0x40, 0x40, 0x3F,   /* 0x55 */\
    0x1F, 0x20, 0x40, 0x20, 0x1F,   /* 0x56 */\
    0x3F, 0x40, 0x38, 0x40, 0x3F,   /* 0x57 */\
    0x63, 0x14, 0x08, 0x14, 0x63,   /* 0x58 */\
    0x03, 0x04, 0x78, 0x04, 0x03,   /* 0x59 */\
    0x61, 0x59, 0x49, 0x4D, 0x43,   /* 0x5A */\
    0x00, 0x7F, 0x41, 0x41, 0x41,   /* 0x5B */\
    0x02, 0x04, 0x08, 0x10, 0x20,   /* 0x5C */\
    0x00, 0x41, 0x41, 0x41, 0x7F,   /* 0x5D */\
    0x04, 0x02, 0x01, 0x02, 0x04,   /* 0x5E */\
    0x40, 0x40, 0x40, 0x40, 0x40,   /* 0x5F */\
    0x00, 0x03, 0x07, 0x08, 0x00,   /* 0x60 */\
    0x20, 0x54, 0x54, 0x78, 0x40,   /* 0x61 */\
    0x7F, 0x28, 0x44, 0x44, 0x38,   /* 0x62 */\
    0x38, 0x44, 0x44, 0x44, 0x28,   /* 0x63 */\
    0x38, 0x44, 0x44, 0x28, 0x7F,   /* 0x64 */\
    0x38, 0x54, 0x54, 0x54, 0x18,   /* 0x65 */\
    0x00, 0x08, 0x7E, 0x09, 0x02,   /* 0x66 */\
    0x18, 0xA4, 0xA4, 0x9C, 0x78,   /* 0x67 */\
    0x7F, 0x08, 0x04, 0x04, 0x78,   /* 0x68 */\
    0x00, 0x44, 0x7D, 0x40, 0x00,   /* 0x69 */\
    0x20, 0x40, 0x40, 0x3D, 0x00,   /* 0x6A */\
    0x7F, 0x10, 0x28, 0x44, 0x00,   /* 0x6B */\
    0x00, 0x41, 0x7F, 0x40, 0x00,   /* 0x6C */\
    0x7C, 0x04, 0x78, 0x04, 0x78,   /* 0x6D */\
    0x7C, 0x08, 0x04, 0x04, 0x78,   /* 0x6E */\
    0x38, 0x44, 0x44, 0x44, 0x38,   /* 0x6F */\
    0xFC, 0x18, 0x24, 0x24, 0x18,   /* 0x70 */\
    0x18, 0x24, 0x24, 0x18, 0xFC,   /* 0x71 */\
    0x7C, 0x08, 0x04, 0x04, 0x08,   /* 0x72 */\
    0x48, 0x54, 0x54, 0x54, 0x24,   /* 0x73 */\
    0x04, 0x04, 0x3F, 0x44, 0x24,   /* 0x74 */\
    0x3C, 0x40, 0x40, 0x20, 0x7C,   /* 0x75 */\
    0x1C, 0x20, 0x40, 0x20, 0x1C,   /* 0x76 */\
    0x3C, 0x40, 0x30, 0x40, 0x3C,   /* 0x77 */\
    0x44, 0x28, 0x10, 0x28, 0x44,   /* 0x78 */\
    0x4C, 0x90, 0x90, 0x90, 0x7C,   /* 0x79 */\
    0x44, 0x64, 0x54, 0x4C, 0x44,   /* 0x7A */\
    0x00, 0x08, 0x36, 0x41, 0x00,   /* 0x7B */\
    0x00, 0x00, 0x77, 0x00, 0x00,   /* 0x7C */\
    0x00, 0x41, 0x36, 0x08, 0x00,   /* 0x7D */\
    0x02, 0x01, 0x02, 0x04, 0x02,   /* 0x7E */\
    0x3C, 0x26, 0x23, 0x26, 0x3C,   /* 0x7F */\
    0x1E, 0xA1, 0xA1, 0x61, 0x12,   /* 0x80 */\
    0x3A, 0x40, 0x40, 0x20, 0x7A,   /* 0x82 */\
    0x38, 0x54, 0x54, 0x55, 0x59,   /* 0x83 */\
    0x21, 0x55, 0x55, 0x79, 0x41,   /* 0x84 */\
    0x21, 0x54, 0x54, 0x78, 0x41,   /* 0x85 */\
    0x21, 0x55, 0x54, 0x78, 0x40,   /* 0x86 */\
    0x20, 0x54, 0x55, 0x79, 0x40,   /* 0x87 */\
    0x0C, 0x1E, 0x52, 0x72, 0x12,   /* 0x88 */\
    0x39, 0x55, 0x55, 0x55, 0x59,   /* 0x89 */\
    0x39, 0x54, 0x54, 0x54, 0x59,   /* 0x8A */\
    0x39, 0x55, 0x54, 0x54, 0x58,   /* 0x8B */\
    0x00, 0x00, 0x45, 0x7C, 0x41,   /* 0x8C */\
    0x00, 0x02, 0x45, 0x7D, 0x42,   /* 0x8D */\
    0x00, 0x01, 0x45, 0x7C, 0x40,   /* 0x8E */\
    0xF0, 0x29, 0x24, 0x29, 0xF0,   /* 0x8F */\
    0xF0, 0x28, 0x25, 0x28, 0xF0,   /* 0x90 */\
    0x7C, 0x54, 0x55, 0x45, 0x00,   /* 0x91 */\
    0x20, 0x54, 0x54, 0x7C, 0x54,   /* 0x92 */\
    0x7C, 0x0A, 0x09, 0x7F, 0x49,   /* 0x93 */\
    0x32, 0x49, 0x49, 0x49, 0x32,   /* 0x94 */\
    0x32, 0x48, 0x48, 0x48, 0x32,   /* 0x95 */\
    0x32, 0x4A, 0x48, 0x48, 0x30,   /* 0x96 */\
    0x3A, 0x41, 0x41, 0x21, 0x7A,   /* 0x97 */\
    0x3A, 0x42, 0x40, 0x20, 0x78,   /* 0x98 */\
    0x00, 0x9D, 0xA0, 0xA0, 0x7D,   /* 0x99 */\
    0x39, 0x44, 0x44, 0x44, 0x39,   /* 0x9A */\
    0x3D, 0x40, 0x40, 0x40, 0x3D,   /* 0x9B */\
    0x3C, 0x24, 0xFF, 0x24, 0x24,   /* 0x9C */\
    0x48, 0x7E, 0x49, 0x43, 0x66,   /* 0x9D */\
    0x2B, 0x2F, 0xFC, 0x2F, 0x2B,   /* 0x9E */\
    0xFF, 0x09, 0x29, 0xF6, 0x20,   /* 0x9F */\
    0xC0, 0x88, 0x7E, 0x09, 0x03,   /* 0xA0 */\
    0x20, 0x54, 0x54, 0x79, 0x41,   /* 0xA1 */\
    0x00, 0x00, 0x44, 0x7D, 0x41,   /* 0xA2 */\
    0x30, 0x48, 0x48, 0x4A, 0x32,   /* 0xA3 */\
    0x38, 0x40, 0x40, 0x22, 0x7A,   /* 0xA4 */\
    0x00, 0x7A, 0x0A, 0x0A, 0x72,   /* 0xA5 */\
    0x7D, 0x0D, 0x19, 0x31, 0x7D,   /* 0xA6 */\
    0x26, 0x29, 0x29, 0x2F, 0x28,   /* 0xA7 */\
    0x26, 0x29, 0x29, 0x29, 0x26,   /* 0xA8 */\
    0x30, 0x48, 0x4D, 0x40, 0x20,   /* 0xA9 */\
    0x38, 0x08, 0x08, 0x08, 0x08,   /* 0xAA */\
    0x08, 0x08, 0x08, 0x08, 0x38,   /* 0xAB */\
    0x2F, 0x10, 0xC8, 0xAC, 0xBA,   /* 0xAC */\
    0x2F, 0x10, 0x28, 0x34, 0xFA,   /* 0xAD */\
    0x00, 0x00, 0x7B, 0x00, 0x00,   /* 0xAE */\
    0x08, 0x14, 0x2A, 0x14, 0x22,   /* 0xAF */\
    0x22, 0x14, 0x2A, 0x14, 0x08,   /* 0xB0 */\
    0xAA, 0x00, 0x55, 0x00, 0xAA,   /* 0xB1 */\
    0xAA, 0x55, 0xAA, 0x55, 0xAA,   /* 0xB2 */\
    0x00, 0x00, 0x00, 0xFF, 0x00,   /* 0xB3 */\
    0x10, 0x10, 0x10, 0xFF, 0x00,   /* 0xB4 */\
    0x14, 0x14, 0x14, 0xFF, 0x00,   /* 0xB5 */\
    0x10, 0x10, 0xFF, 0x00, 0xFF,   /* 0xB6 */\
    0x10, 0x10, 0xF0, 0x10, 0xF0,   /* 0xB7 */\
    0x14, 0x14, 0x14, 0xFC, 0x00,   /* 0xB8 */\
    0x14, 0x14, 0xF7, 0x00, 0xFF,   /* 0xB9 */\
    0x00, 0x00, 0xFF, 0x00, 0xFF,   /* 0xBA */\
    0x14, 0x14, 0xF4, 0x04, 0xFC,   /* 0xBB */\
    0x14, 0x14, 0x17, 0x10, 0x1F,   /* 0xBC */\
    0x10, 0x10, 0x1F, 0x10, 0x1F,   /* 0xBD */\
    0x14, 0x14, 0x14, 0x1F, 0x00,   /* 0xBE */\
    0x10, 0x10, 0x10, 0xF0, 0x00,   /* 0xBF */\
    0x00, 0x00, 0x00, 0x1F, 0x10,   /* 0xC0 */\
    0x10, 0x10, 0x10, 0x1F, 0x10,   /* 0xC1 */\
    0x10, 0x10, 0x10, 0xF0, 0x10,   /* 0xC2 */\
    0x00, 0x00, 0x00, 0xFF, 0x10,   /* 0xC3 */\
    0x10, 0x10, 0x10, 0x10, 0x10,   /* 0xC4 */\
    0x10, 0x10, 0x10, 0xFF, 0x10,   /* 0xC5 */\
    0x00, 0x00, 0x00, 0xFF, 0x14,   /* 0xC6 */\
    0x00, 0x00, 0xFF, 0x00, 0xFF,   /* 0xC7 */\
    0x00, 0x00, 0x1F, 0x10, 0x17,   /* 0xC8 */\
    0x00, 0x00, 0xFC, 0x04, 0xF4,   /* 0xC9 */\
    0x14, 0x14, 0x17, 0x10, 0x17,   /* 0xCA */\
    0x14, 0x14, 0xF4, 0x04, 0xF4,   /* 0xCB */\
    0x00, 0x00, 0xFF, 0x00, 0xF7,   /* 0xCC */\
    0x14, 0x14, 0x14, 0x14, 0x14,   /* 0xCD */\
    0x14, 0x14, 0xF7, 0x00, 0xF7,   /* 0xCE */\
    0x14, 0x14, 0x14, 0x17, 0x14,   /* 0xCF */\
    0x10, 0x10, 0x1F, 0x10, 0x1F,   /* 0xD0 */\
    0x14, 0x14, 0x14, 0xF4, 0x14,   /* 0xD1 */\
    0x10, 0x10, 0xF0, 0x10, 0xF0,   /* 0xD2 */\
    0x00, 0x00, 0x1F, 0x10, 0x1F,   /* 0xD3 */\
    0x00, 0x00, 0x00, 0x1F, 0x14,   /* 0xD4 */\
    0x00, 0x00, 0x00, 0xFC, 0x14,   /* 0xD5 */\
    0x00, 0x00, 0xF0, 0x10, 0xF0,   /* 0xD6 */\
    0x10, 0x10, 0xFF, 0x10, 0xFF,   /* 0xD7 */\
    0x14, 0x14, 0x14, 0xFF, 0x14,   /* 0xD8 */\
    0x10, 0x10, 0x10, 0x1F, 0x00,   /* 0xD9 */\
    0x00, 0x00, 0x00, 0xF0, 0x10,   /* 0xDA */\
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   /* 0xDB */\
    0xF0, 0xF0, 0xF0, 0xF0, 0xF0,   /* 0xDC */\
    0xFF, 0xFF, 0xFF, 0x00, 0x00,   /* 0xDD */\
    0x00, 0x00, 0x00, 0xFF, 0xFF,   /* 0xDE */\
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F,   /* 0xDF */\
    0x38, 0x44, 0x44, 0x38, 0x44,   /* 0xE0 */\
    0x7C, 0x2A, 0x2A, 0x3E, 0x14,   /* 0xE1 */\
    0x7E, 0x02, 0x02, 0x06, 0x06,   /* 0xE2 */\
    0x02, 0x7E, 0x02, 0x7E, 0x02,   /* 0xE3 */\
    0x63, 0x55, 0x49, 0x41, 0x63,   /* 0xE4 */\
    0x38, 0x44, 0x44, 0x3C, 0x04,   /* 0xE5 */\
    0x40, 0x7E, 0x20, 0x1E, 0x20,   /* 0xE6 */\
    0x06, 0x02, 0x7E, 0x02, 0x02,   /* 0xE7 */\
    0x99, 0xA5, 0xE7, 0xA5, 0x99,   /* 0xE8 */\
    0x1C, 0x2A, 0x49, 0x2A, 0x1C,   /* 0xE9 */\
    0x4C, 0x72, 0x01, 0x72, 0x4C,   /* 0xEA */\
    0x30, 0x4A, 0x4D, 0x4D, 0x30,   /* 0xEB */\
    0x30, 0x48, 0x78, 0x48, 0x30,   /* 0xEC */\
    0xBC, 0x62, 0x5A, 0x46, 0x3D,   /* 0xED */\
    0x3E, 0x49, 0x49, 0x49, 0x00,   /* 0xEE */\
    0x7E, 0x01, 0x01, 0x01, 0x7E,   /* 0xEF */\
    0x2A, 0x2A, 0x2A, 0x2A, 0x2A,   /* 0xF0 */\
    0x44, 0x44, 0x5F, 0x44, 0x44,   /* 0xF1 */\
    0x40, 0x51, 0x4A, 0x44, 0x40,   /* 0xF2 */\
    0x40, 0x44, 0x4A, 0x51, 0x40,   /* 0xF3 */\
    0x00, 0x00, 0xFF, 0x01, 0x03,   /* 0xF4 */\
    0xE0, 0x80, 0xFF, 0x00, 0x00,   /* 0xF5 */\
    0x08, 0x08, 0x6B, 0x6B, 0x08,   /* 0xF6 */\
    0x36, 0x12, 0x36, 0x24, 0x36,   /* 0xF7 */\
    0x06, 0x0F, 0x09, 0x0F, 0x06,   /* 0xF8 */\
    0x00, 0x00, 0x18, 0x18, 0x00,   /* 0xF9 */\
    0x00, 0x00, 0x10, 0x10, 0x00,   /* 0xFA */\
    0x30, 0x40, 0xFF, 0x01, 0x01,   /* 0xFB */\
    0x00, 0x1F, 0x01, 0x01, 0x1E,   /* 0xFC */\
    0x00, 0x19, 0x1D, 0x17, 0x12,   /* 0xFD */\
    0x00, 0x3C, 0x3C, 0x3C, 0x3C,   /* 0xFE */\
    0x00, 0x00, 0x00, 0x00, 0x00    /* 0xFF */\
}

/* Public Function Prototypes */
void LCD_display9341_init  				(void);
void LCD_fill_screen       				(uint16_t color);
void LCD_flood            				(uint16_t color, uint32_t length);

void LCD_draw_pixel        				(int16_t x, int16_t y, uint16_t color);
void LCD_draw_line         				(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void LCD_draw_fast_horizontal_line    	(int16_t x, int16_t y, int16_t length, uint16_t color);
void LCD_draw_fast_vertical_line   		(int16_t x, int16_t y, int16_t length, uint16_t color);

void LCD_draw_char   					(int16_t x1, int16_t y1, int8_t chr, uint16_t fg_color, uint16_t bg_color, uint8_t size);
void LCD_draw_string  					(int16_t x1, int16_t y1, int8_t *chr, uint16_t fg_color, uint16_t bg_color, uint8_t size);

void LCD_draw_image         			(uint16_t pos_x, uint16_t pos_y, uint16_t size_x, uint16_t size_y, const uint8_t *image);
void LCD_draw_circle        			(int16_t  x0, int16_t  y0, int16_t  r, uint16_t color);
void LCD_draw_circle_helper  			(int16_t x0, int16_t y0, int16_t r, uint8_t corner_name, uint16_t color);
void LCD_draw_square        			(int16_t x, int16_t y, int16_t l, uint16_t color);
void LCD_draw_rectangle  				(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void LCD_draw_round_rectangle     		(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
void LCD_draw_triangle   				(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

void LCD_fill_image   					(const uint8_t *image);
void LCD_fill_circle       				(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void LCD_fill_circle_helper  			(int16_t x0, int16_t y0, int16_t r, uint8_t corner_name, int16_t delta, uint16_t color);
void LCD_fill_rectangle    				(int16_t x1, int16_t y1, int16_t w, int16_t h, uint16_t color);
void LCD_fill_round_rectangle  			(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
void LCD_fill_triangle  				(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

#endif /* TFT_LCD_H_ */
