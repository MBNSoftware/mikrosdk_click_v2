\mainpage Main Page
 
 

---
# Air quality 2 click

Air quality 2 click carries the iAQ-Core Indoor Air Quality sensor that measures VOC levels and provides CO2 equivalent and TVOC equivalent predictions.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/airquality2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/air-quality-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Airquality2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Airquality2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void airquality2_cfg_setup ( airquality2_cfg_t *cfg ); 
 
- Initialization function.
> AIRQUALITY2_RETVAL airquality2_init ( airquality2_t *ctx, airquality2_cfg_t *cfg );

- Click Default Configuration function.
> void airquality2_default_cfg ( airquality2_t *ctx );


#### Example key functions :

- Function write 8-bit data to 8-bit register on the iAQ-Core module.
> void airquality2_write_data ( airquality2_t *ctx, uint8_t address, uint8_t write_command );
 
- Reads all data information about the indoor air quality.
> uint8_t airquality2_get_all_data ( airquality2_t *ctx, uint16_t *value_co2, uint16_t *value_tvoc, int32_t *resistance );

## Examples Description

> This app measure indoor air quality.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    airquality2_cfg_setup( &cfg );
    AIRQUALITY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality2_init( &airquality2, &cfg );

    log_printf( &logger, "----------------------------------\r\n");
    log_printf( &logger, "           Air quality 2          \r\n");
    log_printf( &logger, "----------------------------------\r\n");
    Delay_100ms( );
}
  
```

### Application Task

> This is a example which demonstrates the use of Air quality 2 Click board.
> Read all data information about the indoor air quality
> from register on the iAQ-Core module, display Prediction Value CO2 [ ppm ],
> Prediction Value TVOC [ ppb ] and Resistance Value.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 5 sec.

```c

void application_task ( void )
{
    uint8_t status_info;
    uint16_t value_co2;
    uint16_t value_tvoc;
    int32_t resistance;

    status_info = airquality2_get_all_data( &airquality2, &value_co2, &value_tvoc, &resistance );
    Delay_100ms();

    log_printf( &logger, "       | Status : ");

    if ( status_info == AIRQUALITY2_STATUS_OK )
    {
        log_printf( &logger, "       | Status : OK     |\r\n");
    }
    if ( status_info == AIRQUALITY2_STATUS_BUSY )
    {
        log_printf( &logger, "       | Status : BUSY   |\r\n");
    }
    if ( status_info == AIRQUALITY2_STATUS_ERROR )
    {
        log_printf( &logger, "       | Status : ERROR  |\r\n");
    }
    if ( status_info == AIRQUALITY2_STATUS_RUNIN )
    {
        log_printf( &logger, "       | Status : RUNIN  |\r\n");
    }

    log_printf( &logger, "----------------------------------\r\n");

    log_printf( &logger, " CO2        : %d [ ppm ] \r\n", value_co2 );

    log_printf( &logger, " TVOC       : %d [ ppb ] \r\n", value_tvoc );

    log_printf( &logger, " Resistance : %d [ Ohm ] \r\n", resistance );

    log_printf( &logger, "----------------------------------\r\n");

    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Airquality2

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
