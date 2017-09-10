#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "bcm2835.h"
#include "typedef.h"
#include "Capture_main.h"

UINT_8 spi_write_byte(UINT_8 reg_addr, UINT_8 value)
{
    bcm2835_gpio_clr(RPI_GPIO_P1_22); //CS1
    bcm2835_spi_transfer(0x40 | reg_addr);
    bcm2835_delayMicroseconds(5);
    bcm2835_spi_transfer(0x00);
    bcm2835_delayMicroseconds(5);
    bcm2835_spi_transfer(value);
    bcm2835_delayMicroseconds(1);
    bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
    return 0;
};

UINT_8 spi_read_byte(UINT_8 reg_addr)
{
    UINT_8 recv_buf;
    bcm2835_gpio_clr(RPI_GPIO_P1_22); //CS1
    bcm2835_spi_transfer(0x20 | reg_addr);
    bcm2835_delayMicroseconds(5);
    bcm2835_spi_transfer(0x00);
    bcm2835_delayMicroseconds(5);
    recv_buf =  bcm2835_spi_transfer(0x00);
    //printf("The Receive value is %X\n",recv_buf);
    bcm2835_delayMicroseconds(1);
    bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
    return recv_buf;
};

UINT_8 spi_send_cmd(UINT_8 cmd)
{
    UINT_8 result;
    bcm2835_gpio_clr(RPI_GPIO_P1_22); //CS1
    result = bcm2835_spi_transfer(cmd);
    bcm2835_delay(1);
    bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
    return result;
}

UINT_8 spi_read_data(UINT_8 numchs,UINT_8 gpio,UINT_8* chData)
{
    UINT_8 iter;
    bcm2835_gpio_clr(RPI_GPIO_P1_22); //CS1
    if(gpio)
    {
        for(iter=0;iter<(numchs+gpio)*3;iter++)
        {
            chData[iter] = bcm2835_spi_transfer(0);
            printf("The channel data is %X\n",chData[iter]);
        }
    }
    else
    {
        bcm2835_spi_transfer(0);
        bcm2835_spi_transfer(0);
        bcm2835_spi_transfer(0);
        for(iter=0;iter<(numchs)*3;iter++)
        {
            chData[iter] = bcm2835_spi_transfer(0);
            printf("The channel data of %d is %X\n",iter,chData[iter]);
            usleep(270);
        }        
    }
    sleep(1);
    bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
    return 0;
};
