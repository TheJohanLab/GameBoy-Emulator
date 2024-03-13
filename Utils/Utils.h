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

typedef struct s_interrupt_flags {
    u8 Vblank_IR : 1;
    u8 LCD_STAT_IR : 1;
    u8 Timer_IR : 1;
    u8 SerialTransferCompletion_IR : 1;
    u8 Joypad_IR : 1;
    u8 others : 2;
    u8 InterruptMasterEnableFlag : 1;

} s_interrupt_flags;

typedef union u_interrup_flags {
    u8 byte;
    s_interrupt_flags flags;
}interrupt_flags;