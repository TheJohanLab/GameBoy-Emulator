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

const u16 SCREENWIDTH = 160;
const u16 SCREENHEIGHT = 144;


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

typedef struct s_interrupt_flag {
    u8 Vblank : 1;
    u8 LCD_STAT : 1;
    u8 Timer : 1;
    u8 SerialTransferCompletion : 1;
    u8 Joypad : 1;
    u8 others : 3;

} s_interrupt_flag;

typedef union u_interrup_flag {
    u8 byte;
    s_interrupt_flag flags;
}interrupt_flag;

