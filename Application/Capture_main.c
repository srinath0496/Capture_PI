#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "bcm2835.h"
#include "typedef.h"
#include "Capture_main.h"
void main()
{
    UINT_8 recv_buf;
    printf("Ram Medical Monitors\n");
    /* BCM driver Initialise*/
    if(bcm_driver_init())
    {
        printf("Driver Failed to Initialise\n");
        exit(1);
    }
    else
    {
        ads1298_gpio_init();
        spi_init();
        ads1298_init();

        while(1)
        {
            printf("Press any key to write\n");
            getchar();
            //spi_select(CS1);
            //spi_rdwr();
            //spi_deselect(CS1);
            bcm2835_gpio_clr(RPI_GPIO_P1_22); //CS1
            bcm2835_spi_transfer(0x20);
            //printf("The Receive value is %X\n",recv_buf);
            bcm2835_delayMicroseconds(5);
            recv_buf =  bcm2835_spi_transfer(0x00);
            bcm2835_delayMicroseconds(5);
            recv_buf =  bcm2835_spi_transfer(0x00);
            printf("The Receive value is %X\n",recv_buf);
            bcm2835_delayMicroseconds(1);
            bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
        }
    }
}

UINT_8 bcm_driver_init()
{
    UINT_8 t,w;
    int i;
    if(!bcm2835_init())
    {
        printf("GPIO driver not Initialise\n");
        return 1;
    }
    else
    {
        printf("Driver Initialise\n");
        bcm2835_gpio_fsel(RPI_GPIO_P1_18, BCM2835_GPIO_FSEL_OUTP); //SPI_START
        bcm2835_gpio_fsel(RPI_GPIO_P1_15, BCM2835_GPIO_FSEL_OUTP); //PIN reset
        bcm2835_gpio_fsel(RPI_GPIO_P1_22, BCM2835_GPIO_FSEL_OUTP); //CS1
        bcm2835_gpio_clr(RPI_GPIO_P1_18);  //SPI_START
        bcm2835_gpio_clr(RPI_GPIO_P1_15); // PIN RESET
        bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
        bcm2835_delay(5);
        printf("Configuration Completed\n");

    }
    return 0;
}

UINT_8 spi_init()
{
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
        bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);
        bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_512);
        //bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
        //bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0,LOW);
        bcm2835_delay(1);
    }
    return 0;
}

UINT_8 ads1298_gpio_init()
{
    bcm2835_gpio_set(RPI_GPIO_P1_15); //Set the RESET Pin to HIGH
    bcm2835_delay(1000);
    bcm2835_gpio_clr(RPI_GPIO_P1_15); //Set the RESET Pin to LOW
    bcm2835_delay(1000);
    bcm2835_gpio_set(RPI_GPIO_P1_15); //Set the RESET Pin to HIGH
    bcm2835_delay(100);
    bcm2835_gpio_clr(RPI_GPIO_P1_22); //CS1
    bcm2835_delay(1000);
    bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
    return 0;
}

UINT_8 ads1298_init()
{
    bcm2835_gpio_clr(RPI_GPIO_P1_22); //CS1
    bcm2835_spi_transfer(0x11);
    bcm2835_delay(10);
    bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
    //printf("The read ID is %X\n",bcm2835_spi_transfer(0x20));
    return 0;
}
