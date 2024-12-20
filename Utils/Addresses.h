#pragma once

//Registries
#define LCD_CONTROL 0xFF40
#define LCD_STATUS 0xFF41
#define LCD_STATUS 0xFF41
#define SCY 0xFF42
#define SCX 0xFF43
#define LY 0xFF44
#define LY_COMPARE 0xFF45
#define DMA 0xFF46
#define BG_PALETTE 0xFF47
#define OBP0 0xFF48
#define OBP1 0xFF49
#define WINDOW_Y 0xFF4A
#define WINDOW_X 0xFF4B

#define INTERRUPT_ENABLE 0xFFFF
#define INTERRUPT_FLAG 0xFF0F

#define VRAM_BEG_ADDRESS 0x8000
#define TILEMAPS_OFFSET 0x1800
#define OAM_BEG_ADDRESS 0xFE00

#define BOOT_ROM 0xFF50