#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "bcm2835.h"
#include "typedef.h"
#include "Capture_main.h"
void main()
{
    UINT_8 recv_buf;
    UINT_8 option,chset;
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
            printf("Main Menu\n");
            printf("1. Device ID\n2.Configure Channel\n3.Start SPI_START\n4.Stop SPI_START\n5.Read Channel Data\n6.Exit\n");
            scanf("%d",&option);
            switch(option)
            {
                case 1:
                            printf("The Dev ID is %X\n",spi_read_byte(0x00));
                            break;
                case 2:
                            spi_write_byte(CONFIG1,SAMP_500_SPS);
                            bcm2835_delay(1);
                            spi_write_byte(CONFIG2,0x33);
                            bcm2835_delay(1000);
                            //spi_write_byte(CONFIG2,0xA3);
                                spi_write_byte(CH1SET,0x05);
                                chset = spi_read_byte(0x12);
                                printf("The read Channel 1 is %x\n",chset);
                                chset = spi_read_byte(0x13);
                                printf("The read Channel 1 is %x\n",chset);
                            break;
                case 3:
                            bcm2835_gpio_set(RPI_GPIO_P1_18);  //SPI_START
                            bcm2835_delay(5);
                            break;
                case 4:
                            bcm2835_gpio_clr(RPI_GPIO_P1_18);  //SPI_START
                            bcm2835_delay(5);
                            break;
                case 5:
                            spi_read_data();
                            break;
                    case 6:
                                bcm2835_close();
                                exit(1);
                    case 7:

                default:
                            break;
            }
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
    spi_send_cmd(SDATAC);
    bcm2835_delay(10);
    return 0;
}
