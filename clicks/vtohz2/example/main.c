/*!
 * \file 
 * \brief VToHz2 Click example
 * 
 * # Description
 * This appliaction enables usage of a converter for analog voltage input signal into a pulse wave signal of a certain frequency.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver, performs the device enable and
 * sets the pwm frequency. Also writes help with the possible instructions.
 * 
 * ## Application Task  
 * Checks which command be entered on UART and sets the pwm duty cycle depending on the entered command.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vtohz2.h"

// ------------------------------------------------------------------ VARIABLES

static vtohz2_t vtohz2;
static log_t logger;

static float duty_cycle = 0.5;
static int8_t perc_check = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    vtohz2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vtohz2_cfg_setup( &cfg );
    VTOHZ2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vtohz2_init( &vtohz2, &cfg );

    vtohz2_enable( &vtohz2, VTOHZ2_ENABLE );
    vtohz2_pwm_start( &vtohz2 );
}

void application_task ( void )
{
    //  Task implementation.
    
    uint8_t i;

    for ( i = 0; i < 15; i++ )
    {
        
            duty_cycle += ( uint32_t )vtohz2.pwm_period * 0.01;
            perc_check += 1;
    
         if ( duty_cycle > vtohz2.pwm_period)
        {
            duty_cycle = vtohz2.pwm_period;
            perc_check = 100;
        }
        
        vtohz2_set_duty_cycle ( &vtohz2, duty_cycle );
        log_printf( &logger, "PWM Duty is : %d %%\r\n", perc_check );
        
        Delay_ms( 100 );
        
    }
    for ( i = 0; i < 10; i++ )
    {
            duty_cycle -= ( uint32_t )vtohz2.pwm_period * 0.01;
            perc_check -= 1;
       
         if ( perc_check < 0 )
        {
            duty_cycle = 0;
            perc_check = 0;
        }
        
        vtohz2_set_duty_cycle ( &vtohz2, duty_cycle );
        log_printf( &logger, "PWM Duty is : %d %%\r\n", perc_check );
        
        Delay_ms( 100 );
        
    }
    for ( i = 0; i < 2; i++ )
    {
        
        
            duty_cycle += ( uint32_t )vtohz2.pwm_period * 0.1;
            perc_check += 10;
            
            if ( duty_cycle > vtohz2.pwm_period )
            {
                duty_cycle = vtohz2.pwm_period;
                perc_check = 100;
            }
        
        vtohz2_set_duty_cycle ( &vtohz2, duty_cycle );
        log_printf( &logger, "PWM Duty is : %d %%\r\n", perc_check );
        
        
    }
    for ( i = 0; i < 3; i++ )
    {
        
        
        duty_cycle -= ( uint32_t )vtohz2.pwm_period * 0.1;
        perc_check -= 10;
        
        
        if ( perc_check < 0 )
        {
            duty_cycle = 0;
            perc_check = 0;
        }
        
        vtohz2_set_duty_cycle ( &vtohz2, duty_cycle );
        log_printf( &logger, "PWM Duty is : %d %%\r\n", perc_check );
        
        Delay_ms( 100 );
    }
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


