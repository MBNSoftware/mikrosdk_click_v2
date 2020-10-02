\mainpage Main Page
 
---
# Barometer 2 click

Barometer 2 Click is a digital barometer on a Click board™. Barometer 2 is equipped with the LPS35HW, an absolute piezoresistive pressure sensor with ceramic, water resistant package, manufactured using a proprietary technology.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/barometer2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/barometer-2-click>)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Barometer2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Barometer2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void barometer2_cfg_setup ( barometer2_cfg_t *cfg ); 
 
- Initialization function.
> BAROMETER2_RETVAL barometer2_init ( barometer2_t *ctx, barometer2_cfg_t *cfg );

- Click Default Configuration function.
> void barometer2_default_cfg ( barometer2_t *ctx );


#### Example key functions :

- Gets the pressure value.
> float barometer2_get_pressure ( barometer2_t *ctx, uint8_t press_format );
 
- Gets the temperature value.
> float barometer2_get_temperature ( barometer2_t *ctx, uint8_t temp_format );

- Resets the device.
> void barometer2_software_reset ( barometer2_t *ctx );

## Examples Description

> The example starts off with the initialization and configuration of the click and logger modules, tests the communication channel and reads and displays temperature and pressure values every second.

**The demo application is composed of two sections :**

### Application Init 

> Initializes and configures the click and logger modules and tests the communication for errors.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    barometer2_cfg_t cfg;
    
    uint8_t test;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    barometer2_cfg_setup( &cfg );
    BAROMETER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer2_init( &barometer2, &cfg );
    barometer2_default_cfg( &barometer2 );

    // Test communication

    test = barometer2_read_byte( &barometer2, BAROMETER2_REG_WHO_AM_I ); 

    if ( test == BAROMETER2_WHO_AM_I )
    {
        log_printf( &logger, "---- Communication OK!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Communication ERROR!!! ----\r\n" );
        for ( ; ; );
    } 

    // Software reset 

    barometer2_software_reset( &barometer2 );
    Delay_1sec();

    Delay_1sec( );
    log_printf( &logger, "---- Start Measurement ---- \r\n" );
}
  
```

### Application Task

> Reads and displays temperature and pressure values every second.

```c

void application_task ( )
{
    float temperature;
    float pressure;
     
    temperature = barometer2_get_temperature( &barometer2, BAROMETER2_TEMPERATURE_IN_CELSIUS );
    log_printf( &logger, " Temperature : %f ", temperature );

    pressure = barometer2_get_pressure( &barometer2, BAROMETER2_PRESSURE_DATA_IN_mBar );
    log_printf( &logger, " Pressure : %f \n", pressure );

    log_printf( &logger, "--------------------------\n" );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---