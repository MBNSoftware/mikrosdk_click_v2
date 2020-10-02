/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "c8x8.h"
#include <string.h>

// ------------------------------------------------------------- PRIVATE MACROS 

#define C8X8_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static const uint8_t ascii_matrix[][ 10 ] = {

          { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0 },   // space -- 32
          { 0x00, 0x00, 0x0,  0x0,  0x60, 0xfa, 0xfa, 0x60, 0x0,  0x0 },   // ! -- 33
          { 0x00, 0x00, 0x0,  0xc0, 0xe0, 0x0,  0x0,  0xe0, 0xc0, 0x0 },   // " -- 34
          { 0x00, 0x00, 0x28, 0xfe, 0xfe, 0x28, 0xfe, 0xfe, 0x28, 0x0 },   // # -- 35
          { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0 },   // $ -- 36
          { 0x00, 0x00, 0x62, 0x66, 0xc,  0x18, 0x30, 0x66, 0x46, 0x0 },   // % -- 37
          { 0x00, 0x00, 0xc,  0x5e, 0xf2, 0xba, 0xec, 0x5e, 0x12, 0x0 },   // & -- 38
          { 0x00, 0x00, 0x0,  0x0,  0x20, 0xe0, 0xc0, 0x0,  0x0,  0x0 },   // ' -- 39
          { 0x00, 0x00, 0x0,  0x0,  0x38, 0x7c, 0xc6, 0x82, 0x0,  0x0 },   // ( -- 40
          { 0x00, 0x00, 0x0,  0x0,  0x82, 0xc6, 0x7c, 0x38, 0x0,  0x0 },   // ) -- 41
          { 0x00, 0x00, 0x10, 0x54, 0x7c, 0x38, 0x38, 0x7c, 0x54, 0x10},   // * -- 42
          { 0x00, 0x00, 0x0,  0x10, 0x10, 0x7c, 0x7c, 0x10, 0x10, 0x0 },   // + -- 43
          { 0x00, 0x00, 0x0,  0x0,  0x0,  0x18, 0x1c, 0x0,  0x0,  0x0 },   // , -- 44
          { 0x00, 0x00, 0x0,  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0 },   // - -- 45
          { 0x00, 0x00, 0x0,  0x0,  0x0,  0x6,  0x6,  0x0,  0x0,  0x0 },   // . -- 46
          { 0x00, 0x00, 0x6,  0xc,  0x18, 0x30, 0x60, 0xc0, 0x80, 0x0 },   // / -- 47

          { 0x00, 0x00, 0x7c, 0xfe, 0x8a, 0x92, 0xa2, 0xfe, 0x7c, 0x00},   // 0 -- 48
          { 0x00, 0x00, 0x0,  0x2,  0x42, 0xfe, 0xfe, 0x2,  0x2,  0x00},   // 1 -- 49
          { 0x00, 0x00, 0x42, 0xc6, 0x8e, 0x9a, 0x92, 0xf6, 0x66, 0x00},   // 2 -- 50
          { 0x00, 0x00, 0x22, 0x63, 0x49, 0x49, 0x49, 0x7F, 0x36, 0x00},   // 3 -- 51
          { 0x00, 0x00, 0x18, 0x38, 0x68, 0xca, 0xfe, 0xfe, 0xa,  0x0 },   // 4 -- 52
          { 0x00, 0x00, 0x0 , 0xf4, 0xf6, 0x92, 0x92, 0x92, 0x9e, 0x8c},   // 5 -- 53
          { 0x00, 0x00, 0x3c, 0x7e, 0xd2, 0x92, 0x92, 0x1e, 0xc,  0x00},   // 6 -- 54
          { 0x00, 0x00, 0x0,  0x0,  0x80, 0x9e, 0xb0, 0xe0, 0xc0, 0x0 },   // 7 -- 55
          { 0x00, 0x00, 0x6c, 0xfe, 0x92, 0x92, 0x92, 0xfe, 0x6c, 0x0 },   // 8 -- 56
          { 0x00, 0x00, 0x60, 0xf2, 0x92, 0x92, 0x96, 0xfc, 0x78, 0x0 },   // 9 -- 57//

          { 0x00, 0x00, 0x0,  0x0,  0x0,  0x66, 0x66, 0x0,  0x0,  0x0 },   // : -- 58
          { 0x00, 0x00, 0x0,  0x0,  0x0,  0x6c, 0x6e, 0x0,  0x0,  0x0 },   // ; -- 59
          { 0x00, 0x00, 0x0,  0x0,  0x10, 0x38, 0x6c, 0xc6, 0x82, 0x0 },   // < -- 60
          { 0x00, 0x00, 0x0,  0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x0 },   // = -- 61
          { 0x00, 0x00, 0x0,  0x82, 0xc6, 0x6c, 0x38, 0x10, 0x0,  0x0 },   // > -- 62
          { 0x00, 0x00, 0x40, 0xc0, 0x80, 0x9a, 0xba, 0xe0, 0x40, 0x0 },   // ? -- 63
          { 0x00, 0x00, 0x7c, 0xfe, 0x82, 0xba, 0xaa, 0xf8, 0x78, 0x0 },   // @ -- 64

          { 0x00, 0x00, 0x3e, 0x7e, 0xd0, 0x90, 0xd0, 0x7e, 0x3e, 0x0 },   // A -- 65
          { 0x00, 0x00, 0x82, 0xfe, 0xfe, 0x92, 0x92, 0xfe, 0x6c, 0x0 },   // B -- 66
          { 0x00, 0x00, 0x38, 0x7c, 0xc6, 0x82, 0x82, 0xc6, 0x44, 0x0 },   // C -- 67
          { 0x00, 0x00, 0x82, 0xfe, 0xfe, 0x82, 0xc6, 0x7c, 0x38, 0x0 },   // D -- 68
          { 0x00, 0x00, 0x82, 0xfe, 0xfe, 0x92, 0xba, 0x82, 0xc6, 0x0 },   // E -- 69
          { 0x00, 0x00, 0x82, 0xfe, 0xfe, 0x92, 0xb8, 0x80, 0xc0, 0x0 },   // F -- 70
          { 0x00, 0x00, 0x38, 0x7c, 0xc6, 0x82, 0x8a, 0xce, 0x4e, 0x0 },   // G -- 71
          { 0x00, 0x00, 0xfe, 0xfe, 0x10, 0x10, 0x10, 0xfe, 0xfe, 0x0 },   // H -- 72
          { 0x00, 0x00, 0x0,  0x0,  0x82, 0xfe, 0xfe, 0x82, 0x0,  0x0 },   // I -- 73
          { 0x00, 0x00, 0x0,  0xe,  0x2,  0x82, 0xfe, 0xfc, 0x80, 0x0 },   // J -- 74
          { 0x00, 0x00, 0x82, 0xfe, 0xfe, 0x10, 0x38, 0xee, 0xc6, 0x0 },   // K -- 75
          { 0x00, 0x00, 0x82, 0xfe, 0xfe, 0x82, 0x2,  0x6,  0xe,  0x0 },   // L -- 76
          { 0x00, 0x00, 0xfe, 0xfe, 0x70, 0x38, 0x70, 0xfe, 0xfe, 0x0 },   // M -- 77
          { 0x00, 0x00, 0xfe, 0xfe, 0x60, 0x30, 0x18, 0xfe, 0xfe, 0x0 },   // N -- 78
          { 0x00, 0x00, 0x7c, 0xfe, 0x82, 0x82, 0x82, 0xfe, 0x7c, 0x0 },   // O -- 79
          { 0x00, 0x00, 0x82, 0xfe, 0xfe, 0x92, 0x90, 0xf0, 0x60, 0x0 },   // P -- 80
          { 0x00, 0x00, 0x7c, 0xfe, 0x82, 0x82, 0x87, 0xff, 0x7d, 0x0 },   // Q -- 81
          { 0x00, 0x00, 0x82, 0xfe, 0xfe, 0x90, 0x98, 0xfe, 0x66, 0x0 },   // R -- 82
          { 0x00, 0x00, 0x44, 0xe6, 0xb2, 0x92, 0x9a, 0xce, 0x44, 0x0 },   // S -- 83
          { 0x00, 0x00, 0x0,  0xe0, 0xc2, 0xfe, 0xfe, 0xc2, 0xe0, 0x0 },   // T -- 84
          { 0x00, 0x00, 0xfc, 0xfe, 0x2,  0x2,  0x2,  0xfe, 0xfc, 0x0 },   // U -- 85
          { 0x00, 0x00, 0xf8, 0xfc, 0x6,  0x2,  0x6,  0xfc, 0xf8, 0x0 },   // V -- 86
          { 0x00, 0x00, 0xfc, 0xfe, 0x6,  0x1c, 0x6,  0xfe, 0xfc, 0x0 },   // W -- 87
          { 0x00, 0x00, 0xc6, 0xee, 0x38, 0x10, 0x38, 0xee, 0xc6, 0x0 },   // X -- 88
          { 0x00, 0x00, 0x0,  0xe0, 0xf2, 0x1e, 0x1e, 0xf2, 0xe0, 0x0 },   // Y -- 89
          { 0x00, 0x00, 0xe2, 0xc6, 0x8e, 0x92, 0xb2, 0xe6, 0xce, 0x0 },   // Z -- 90

          { 0x00, 0x00, 0x0,  0x0,  0xfe, 0xfe, 0x82, 0x82, 0x0,  0x0 },   // [ -- 91
          { 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xc,  0x6,  0x0 },   // \ -- 92
          { 0x00, 0x00, 0x0,  0x0,  0x82, 0x82, 0xfe, 0xfe, 0x0,  0x0 },   // ] -- 93
          { 0x00, 0x00, 0x10, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x10, 0x0 },   // ^ -- 94
          { 0x00, 0x00, 0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1 },   // _ -- 95
          { 0x00, 0x00, 0x0,  0x0,  0x80, 0xc0, 0x60, 0x20, 0x0,  0x0 },   // ` -- 96{}

          { 0x00, 0x00, 0x4,  0x2e, 0x2a, 0x2a, 0x3c, 0x1e, 0x2,  0x0 },   // a -- 97
          { 0x00, 0x00, 0x82, 0xfe, 0xfc, 0x22, 0x22, 0x3e, 0x1c, 0x0 },   // b -- 98
          { 0x00, 0x00, 0x1c, 0x3e, 0x22, 0x22, 0x22, 0x36, 0x14, 0x0 },   // c -- 99
          { 0x00, 0x00, 0x1c, 0x3e, 0x22, 0xa2, 0xfc, 0xfe, 0x2,  0x0 },   // d -- 100
          { 0x00, 0x00, 0x1c, 0x3e, 0x2a, 0x2a, 0x2a, 0x3a, 0x18, 0x0 },   // e -- 101
          { 0x00, 0x00, 0x12, 0x7e, 0xfe, 0x92, 0x90, 0xc0, 0x40, 0x0 },   // f -- 102
          { 0x00, 0x00, 0x19, 0x3d, 0x25, 0x25, 0x3f, 0x3e, 0x20, 0x0 },   // g -- 103
          { 0x00, 0x00, 0x82, 0xfe, 0xfe, 0x30, 0x20, 0x3e, 0x1e, 0x0 },   // h -- 104
          { 0x00, 0x00, 0x0,  0x0,  0x22, 0xbe, 0xbe, 0x2,  0x0,  0x0 },   // i -- 105
          { 0x00, 0x00, 0x0,  0x6,  0x7,  0x1,  0x1,  0xbf, 0xbe, 0x0 },   // j -- 106
          { 0x00, 0x00, 0x82, 0xfe, 0xfe, 0x8,  0x1c, 0x36, 0x22, 0x0 },   // k -- 107
          { 0x00, 0x00, 0x0,  0x0,  0x82, 0xfe, 0xfe, 0x2,  0x0,  0x0 },   // l -- 108
          { 0x00, 0x00, 0x3e, 0x3e, 0x30, 0x1e, 0x30, 0x3e, 0x1e, 0x0 },   // m -- 109
          { 0x00, 0x00, 0x20, 0x3e, 0x1e, 0x20, 0x20, 0x3e, 0x1e, 0x0 },   // n -- 110
          { 0x00, 0x00, 0x1c, 0x3e, 0x22, 0x22, 0x22, 0x3e, 0x1c, 0x0 },   // o -- 111
          { 0x00, 0x00, 0x21, 0x3f, 0x1f, 0x25, 0x24, 0x3c, 0x18, 0x0 },   // p -- 112
          { 0x00, 0x00, 0x18, 0x3c, 0x24, 0x25, 0x1f, 0x3f, 0x21, 0x0 },   // q -- 113
          { 0x00, 0x00, 0x22, 0x3e, 0x1e, 0x32, 0x20, 0x30, 0x10, 0x0 },   // r -- 114
          { 0x00, 0x00, 0x12, 0x3a, 0x2a, 0x2a, 0x2a, 0x2e, 0x24, 0x0 },   // s -- 115
          { 0x00, 0x00, 0x20, 0x20, 0xfc, 0xfe, 0x22, 0x26, 0x4,  0x0 },   // t -- 116
          { 0x00, 0x00, 0x3c, 0x3e, 0x2,  0x2,  0x3c, 0x3e, 0x2,  0x0 },   // u -- 117
          { 0x00, 0x00, 0x38, 0x3c, 0x6,  0x3,  0x6,  0x3c, 0x38, 0x0 },   // v -- 118
          { 0x00, 0x00, 0x3c, 0x3e, 0x6,  0x1c, 0x6,  0x3e, 0x3c, 0x0 },   // w -- 119
          { 0x00, 0x00, 0x22, 0x36, 0x1c, 0x8,  0x1c, 0x36, 0x22, 0x0 },   // x -- 120
          { 0x00, 0x00, 0x39, 0x3e, 0x5,  0x5,  0x5,  0x3f, 0x3e, 0x0 },   // y -- 121
          { 0x00, 0x00, 0x0,  0x32, 0x26, 0x2e, 0x3a, 0x32, 0x26, 0x0 }
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void set_speed ( c8x8_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c8x8_cfg_setup ( c8x8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

C8X8_RETVAL c8x8_init ( c8x8_t *ctx, c8x8_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = C8X8_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return C8X8_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, C8X8_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    ctx->speed_scroll = 0;

    return C8X8_OK;
}

void c8x8_default_cfg ( c8x8_t *ctx )
{
    // Click default configuration

    c8x8_write_cmd( ctx, C8X8_DECODE_MODE_REG, C8X8_NO_DECODE );
    c8x8_write_cmd( ctx, C8X8_INTENSITY_REG,   C8X8_INTENSITY_15 );
    c8x8_write_cmd( ctx, C8X8_SCAN_LIMIT_REG,  C8X8_DISPLAY_DIGIT_0_7 );
    c8x8_write_cmd( ctx, C8X8_SHUTDOWN_REG,    C8X8_NORMAL_OPERATION );

    c8x8_set_speed_scroll( ctx, C8X8_SPEED_MEDIUM );
    c8x8_display_refresh( ctx );
}

void c8x8_generic_transfer ( c8x8_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void c8x8_write_cmd ( c8x8_t *ctx, uint8_t cmd, uint8_t tx_data )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = cmd;
    tx_buf[ 1 ] = tx_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

void c8x8_display_refresh ( c8x8_t *ctx )
{
   uint8_t cnt;

   for ( cnt = 1; cnt < 9; cnt++ )
   {
        c8x8_write_cmd( ctx, cnt, 0x00 );
   }
}

void c8x8_set_speed_scroll ( c8x8_t *ctx, uint8_t speed )
{
    ctx->speed_scroll = speed;
}

void c8x8_display_string ( c8x8_t *ctx, char *p_array )
{
    uint8_t str_word[512];
    char wr_chr;
    uint8_t cnt;
    uint8_t i;
    uint8_t global_cnt = 0;
    uint8_t char_ascii;
    uint8_t position = 0;
    uint8_t col = 8;

    for ( i = 0; i < strlen( p_array ); i++ )
    {
        char_ascii = p_array[ i ] - 32;
        for ( cnt = 0; cnt < 10; cnt++ )
        {
            str_word[ global_cnt++ ] = ascii_matrix[ char_ascii ][ cnt ];
        }
    }

    while ( position < ( global_cnt - 8 ) )
    {
         for ( cnt = position; cnt < position + 8; cnt++ )
         {
             wr_chr = str_word[ cnt ];
             c8x8_write_cmd( ctx, col, wr_chr );
             col--;
         }
         col = 8;
         position++;
         set_speed( ctx );
     }
}


void c8x8_display_byte ( c8x8_t *ctx, char tx_byte )
{
    uint8_t cnt;
    uint8_t char_ascii;
    uint8_t position = 8;
    char wr_chr;

    char_ascii = tx_byte - 32;
    for ( cnt = 2; cnt < 10; cnt++ )
    {
        wr_chr = ascii_matrix[ char_ascii ][ cnt ];
        c8x8_write_cmd( ctx, position, wr_chr );
        position--;
    }
}

void c8x8_display_image ( c8x8_t *ctx, uint8_t *p_image )
{
    uint8_t cnt;
    uint8_t line;
    uint8_t position = 8;

    for ( cnt = 0; cnt < 8; cnt++ )
    {
        line = p_image[ cnt ];
        c8x8_write_cmd( ctx, position, line );
        position--;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void set_speed ( c8x8_t *ctx )
{
    switch ( ctx->speed_scroll )
    {
        case C8X8_SPEED_SLOW:
        {
           Delay_100ms();
           Delay_100ms();
           break;
        }
        case C8X8_SPEED_MEDIUM:
        {
           Delay_100ms();
           break;
        }
        case C8X8_SPEED_FAST:
        {
            Delay_10ms();
            Delay_10ms();
            Delay_10ms();
            break;
        }
        default:
        {
            Delay_100ms();
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
