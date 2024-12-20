#pragma once
#include <vector>

using u8 = uint8_t;

std::vector<u8> EmptyTile(16, 0);

std::vector<u8> nintendoLogo{
 0xF0,0xF0,0xF0,0xF0,0xFC,0xFC,0xFC,0xFC,
 0xFC,0xFC,0xFC,0xFC,0xF3,0xF3,0xF3,0xF3,
 0xF3,0xF3,0xF3,0xF3,0xF0,0xF0,0xF0,0xF0,
 0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
 0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,
 0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,
 0x3C,0x3C,0x3C,0x3C,0xFC,0xFC,0xFC,0xFC,
 0xFC,0xFC,0xFC,0xFC,0x3C,0x3C,0x3C,0x3C,
 0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
 0x00,0x00,0x00,0x00,0xF3,0xF3,0xF3,0xF3,
 0xF3,0xF3,0xF3,0xF3,0xF3,0xF3,0xF3,0xF3,
 0xF3,0xF3,0xF3,0xF3,0xF3,0xF3,0xF3,0xF3,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0xCF,0xCF,0xCF,0xCF,
 0xF3,0xF3,0xF3,0xF3,0xC3,0xC3,0xC3,0xC3,
 0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,
 0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,
 0x3F,0x3F,0x3F,0x3F,0x0F,0x0F,0x0F,0x0F,
 0xCF,0xCF,0xCF,0xCF,0xCF,0xCF,0xCF,0xCF,
 0xCF,0xCF,0xCF,0xCF,0xCF,0xCF,0xCF,0xCF,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0xC0,0xC0,0xC0,0xC0,0x0F,0x0F,0x0F,0x0F,
 0x3C,0x3C,0x3C,0x3C,0x3F,0x3F,0x3F,0x3F,
 0x3C,0x3C,0x3C,0x3C,0x0F,0x0F,0x0F,0x0F,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,
 0x3C,0x3C,0x3C,0x3C,0xFC,0xFC,0xFC,0xFC,
 0x00,0x00,0x00,0x00,0xFC,0xFC,0xFC,0xFC,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0xF3,0xF3,0xF3,0xF3,
 0xFC,0xFC,0xFC,0xFC,0xF0,0xF0,0xF0,0xF0,
 0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0xC0,
 0xF3,0xF3,0xF3,0xF3,0xF3,0xF3,0xF3,0xF3,
 0xF3,0xF3,0xF3,0xF3,0xF0,0xF0,0xF0,0xF0,
 0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
 0x03,0x03,0x03,0x03,0xFF,0xFF,0xFF,0xFF,
 0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,
 0xC3,0xC3,0xC3,0xC3,0xFF,0xFF,0xFF,0xFF,
 0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
 0xC0,0xC0,0xC0,0xC0,0xC3,0xC3,0xC3,0xC3,
 0xCF,0xCF,0xCF,0xCF,0xCF,0xCF,0xCF,0xCF,
 0xCF,0xCF,0xCF,0xCF,0xC3,0xC3,0xC3,0xC3,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0xFC,0xFC,0xFC,0xFC,
 0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
 0x0F,0x0F,0x0F,0x0F,0xFC,0xFC,0xFC,0xFC,
 0x3C,0x3C,0x42,0x42,0xB9,0xB9,0xA5,0xA5,
 0xB9,0xB9,0xA5,0xA5,0x42,0x42,0x3C,0x3C
};

const std::vector<u8> tile12{
	0b10101010, 0b01010101,
	0b10101010, 0b01010101,
	0b10101010, 0b01010101,
	0b10101010, 0b01010101,
	0b10101010, 0b01010101,
	0b10101010, 0b01010101,
	0b10101010, 0b01010101,
	0b10101010, 0b01010101
};

const std::vector<u8> tile22{
	0b00000000, 0b00000000,
	0b11100111, 0b11111111,
	0b11100111, 0b11111111,
	0b11100111, 0b11111111,
	0b11100111, 0b11111111,
	0b00000000, 0b00000000,
	0b11100111, 0b11111111,
	0b11100111, 0b11111111
};

const std::vector<u8> tileMapBoot{
	0, 0, 0, 0, 1, 3, 5, 7, 9 , 11, 13, 15, 17, 19, 21, 23, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};