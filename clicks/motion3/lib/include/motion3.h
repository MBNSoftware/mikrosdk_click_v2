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
 * \brief This file contains API for Motion 3 Click driver.
 *
 * \addtogroup motion3 Motion 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MOTION3_H
#define MOTION3_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define MOTION3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MOTION3_RETVAL  uint8_t

#define MOTION3_OK           0x00
#define MOTION3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup enable_disable   Enable Disable
 * \{
 */
#define MOTION3_ENABLE                     0
#define MOTION3_DISABLE                    1
#define MOTION3_INTERRUPT_DETECT           1
#define MOTION3_INTERRUPT_NOT_DETECT       0
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */
 
/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t en;
  

    // Input pins 

    digital_in_t int_pin;

} motion3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t int_pin;

} motion3_cfg_t;

/** \} */ // End types group

// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void motion3_cfg_setup ( motion3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MOTION3_RETVAL motion3_init ( motion3_t *ctx, motion3_cfg_t *cfg );

/**
 * @brief Generic function for setting en pin status.
 *
 * @param ctx      Click object.
 * @param state    State of the pin.
 *
 * @description This function for setting en pin status.
 */
void motion3_set_en_pin ( motion3_t *ctx, uint8_t state );

/**
 * @brief Generic function for reading int pin status.
 *
 * @param ctx  Click object.
 * 
 * @return Pin status
 *
 * @description This function for reading int pin status.
 */
uint8_t motion3_get_int ( motion3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MOTION3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
