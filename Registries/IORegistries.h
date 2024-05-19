#pragma once

#include "../Utils/Utils.h"

// Interrupt Enable & Interrup Flag FFFF & FF0F
typedef struct s_interrupt_flag {
    u8 Vblank : 1;
    u8 LCD_STAT : 1;
    u8 Timer : 1;
    u8 SerialTransferCompletion : 1;
    u8 Joypad : 1;
    u8 NOT_USED : 3;

} s_interrupt_flag;

typedef union u_interrupt_flag {
    u8 byte;
    s_interrupt_flag flags;
}interrupt_flag;


//LCD Control FF40
typedef struct s_LCD_control {
    u8 BG_WindowEnable : 1;
    u8 OBJEnable : 1;
    u8 OBJSize : 1;
    u8 BGtileMap : 1;
    u8 BG_WindowTiles : 1;
    u8 windowEnable : 1;
    u8 windowTileMap : 1;
    u8 LCD_PPUEnable : 1;

} s_LCD_control;

typedef union u_LCD_control {
    u8 byte;
    s_LCD_control flags;
}LCD_control;

//LCD Status FF41
typedef struct s_LCD_status {
    u8 PPUMode : 2;
        // 0x00 : HBlank
        // 0x01 : VBlank
        // 0x02 : OAM Scan
        // 0x03 : Drawing Pixels
    u8 LYC_LY : 1;
    u8 mode0intSelect : 1;
    u8 mode1intSelect : 1;
    u8 mode2intSelect : 1;
    u8 LYCintSelect : 1;
    u8 NOT_USED : 2;

} s_LCD_status;

typedef union u_LCD_status {
    u8 byte;
    s_LCD_status flags;
}LCD_status;

//Palettes FF47
typedef struct s_BG_palette_data {
    u8 ID0 : 2;
    u8 ID1 : 2;
    u8 ID2 : 2;
    u8 ID3 : 2;

} s_BG_palette_data;

typedef union u_BG_palette_data {
    u8 byte;
    s_BG_palette_data flags;
}BG_palette_data;




