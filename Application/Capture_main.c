#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "bcm2835.h"
void main()
{
    printf("Ram Medical Monitors\n");
    /* BCM driver Initialise*/
    if(bcm_driver_init())
    {
        printf("Driver Failed to Initialise\n");
        exit(1);
    }
    else
    {
        while(1)
        {
            printf("Press any key to write\n");
            getchar();
            spi_select(CS1);
            spi_rdwr();
            spi_deselect(CS1);
    }
}

UINT_8 bcm_driver_init()
{
    if(!bcm2835_init())
    {
        printf("GPIO driver not Initialise\n");
        return 1;
    }
    else
    {
        printf("Driver Initialise\n");
        if(!bcm2835_spi_begin())
        {
            printf("The SPI device failed to start\n");
            return 1;
        }
        else
        {
            printf("The SPI device started\n");
            printf("Configuring the SPI interface");
            bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
            bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
            bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_2048);
            bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
            bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0,LOW);

        }
    }
    return 0;
}

UINT_8 spi_select(UINT_8 chip_sel)
{
    bcm2835_spi_
}
