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