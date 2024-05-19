#pragma once

#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

const u16 instructionAmount = 512;

const u16 kiB = 1024;
const u8 HRAMSize = 127;


// Screen refresh
const int cyclesPerFrame = 70224;
const double timePerFrame = 1.0 / 60.0;

const u16 SCREEN_WIDTH = 160;
const u16 SCREEN_HEIGHT = 144;

// PPU cycle modes
const u8 PPU_HBLANK = 0x00;
const u8 PPU_VBLANK = 0x01;
const u8 PPU_OAM_SCAN = 0x02;
const u8 PPU_DRAWING = 0x03;

// PPU cycles modes durations (in dots - 1 dot = 1 cycle) 456 dots per line
#define PPU_HBLANK_DOTS 204
#define PPU_VBLANK_DOTS 456
#define PPU_OAM_SCAN_DOTS 80
#define PPU_DRAWING_DOTS 172

typedef struct s_flags {
    u8 r : 4;
    u8 C : 1;
    u8 H : 1;
    u8 N : 1;
    u8 Z : 1;
}s_flags;

typedef union u_flags {
	u8 F;
	s_flags flags;
}flags;

typedef struct RGB{
    u8 R;
    u8 G;
    u8 B;
}gb_palette;


