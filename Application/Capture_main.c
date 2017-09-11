#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "bcm2835.h"
#include "typedef.h"
#include "Capture_main.h"
#include "ADS1298.h"
void main()
{
    UINT_8 recv_buf,data;
    UINT_8 option,chset;
    UINT_16 i=0;
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
                            printf("The Dev ID is %X\n",spi_read_byte(ID));
                            break;
                case 2:
                            ads1298_chan_setup(8,8,1);
                            bcm2835_delay(5);
                            break;
                case 3:
                            //cm2835_gpio_set(RPI_GPIO_P1_18);  //SPI_START
                            spi_send_cmd(RDATAC);
                            bcm2835_delay(5);
                            break;
                case 4:
                            //cm2835_gpio_clr(RPI_GPIO_P1_18);  //SPI_START
                            ads1298_chan_setup(8,8,0);
                            bcm2835_delay(5);
                            break;
                case 5:
                //spi_send_cmd(RDATAC);
                bcm2835_delay(5);
                            for(i=0;i<60;i++)
                            spi_read_data(8,1,&data);
                       /*     while(data!=NULL)
                            {
                                printf("The Length of the data is %X\n",data[i++]);
                            }*/
                            
                            bcm2835_delay(5);
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
        bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);
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

UINT_8 ads1298_chan_setup(UINT_8 numChs,UINT_8 max_numChs,UINT_8 intTest)
{
    UINT_8 RLD_bits = 0,iter;
    spi_write_byte(GPIO,0x00);
    spi_write_byte(CONFIG1,HIGH_RES_1k_SPS);
    if(intTest)
    {
        spi_write_byte(CONFIG2,CONFIG2_const | INT_TEST_1HZ | TEST_AMP);
        for(iter=0;iter<numChs;++iter)
        {
            spi_write_byte(CH1SET+iter,TEST_SIGNAL | GAIN_X12);
        }
        for(iter=numChs;iter<max_numChs;++iter)
        {
            spi_write_byte(CH1SET+iter,PD_CH | SHORTED);
        }
    }
    spi_write_byte(CONFIG3,PD_REFBUF | CONFIG3_const);
    return 0;
}