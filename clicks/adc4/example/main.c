/*!
 * \file 
 * \brief Adc4 Click example
 * 
 * # Description
 * This application is a converter from analog to digital multichannel 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes ADC 4 driver and setups working mode.
 * 
 * ## Application Task  
 * Sequential read of voltage. Information about
 * current voltage is logget to UART. Operation is repeated each second. Settings are set
 * to calculate and convert input voltage with internal referent voltage 2.5V.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adc4.h"

// ------------------------------------------------------------------ VARIABLES

static adc4_t adc4;
static log_t logger;
static uint16_t voltage;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc4_cfg_setup( &cfg );
    ADC4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc4_init( &adc4, &cfg );

    Delay_ms( 100 );

    adc4_default_cfg( &adc4 );

    voltage = 0;
}

void application_task ( )
{
    voltage = adc4_get_voltage( &adc4, ADC4_VREF_4000MV);

    if ( adc4.sing_bit == 1 )
    {
        log_printf( &logger, "Current Voltage : %d mV \r\n", voltage );
    }
    else
    {
        log_printf( &logger, "Current Voltage : - %d mV \r\n", voltage );
    }

    Delay_ms( 1000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
