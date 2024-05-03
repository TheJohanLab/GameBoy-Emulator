#pragma once

#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;

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


