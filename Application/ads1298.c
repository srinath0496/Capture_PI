#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "bcm2835.h"
#include "typedef.h"
#include "Capture_main.h"

UINT_8 spi_write_byte(UINT_8 reg_addr, UINT_8 value)
{
    bcm2835_gpio_clr(RPI_GPIO_P1_22); //CS1
    bcm2835_delayMicroseconds(100);
    bcm2835_spi_transfer(0x40 | reg_addr);
    bcm2835_delayMicroseconds(5);
    bcm2835_spi_transfer(0x00);
    bcm2835_delayMicroseconds(5);
    bcm2835_spi_transfer(value);
    bcm2835_delayMicroseconds(10);
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
    bcm2835_delayMicroseconds(10);
    bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
    return recv_buf;
};

UINT_8 spi_send_cmd(UINT_8 cmd)
{
    UINT_8 result;
    bcm2835_gpio_clr(RPI_GPIO_P1_22); //CS1
    result = bcm2835_spi_transfer(cmd);
    bcm2835_delay(5);
    bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
    return result;
}

UINT_8 spi_read_data(UINT_8 numchs,UINT_8 gpio,UINT_8* chData)
{
    UINT_8 iter,startBit,loffStatP,loffStatN,data1,data2,data3;
    int channelData;
    bcm2835_gpio_clr(RPI_GPIO_P1_22); //CS1
    delayMicroseconds(300);
    if(gpio)
    {
        startBit = bcm2835_spi_transfer(0);
        loffStatP = bcm2835_spi_transfer(0);
        loffStatN = bcm2835_spi_transfer(0);
       // printf("The StartBit is %X\n",startBit);
//printf("The LED OFF Positive Status is %X\n",loffStatP);
//printf("The LED OFF Negative Status is %X\n",loffStatN);
        delayMicroseconds(100);
        for(iter=0;iter<(numchs);iter++)
        {
            data1 = bcm2835_spi_transfer(0);
            delayMicroseconds(100);
            data2 = bcm2835_spi_transfer(0);
            delayMicroseconds(100);
            data3 = bcm2835_spi_transfer(0);
            channelData = (data1<<16) | (data2<<8) | (data3);//&data2<<16&data3<<8;
            printf("%d\t",channelData);
        }
        printf("\n");
    }
    else
    {
        bcm2835_spi_transfer(0);
        bcm2835_spi_transfer(0);
        bcm2835_spi_transfer(0);
        for(iter=0;iter<(numchs)*3;iter++)
        {
            chData[iter] = bcm2835_spi_transfer(0);
            printf("%d\t",chData[iter]);
            usleep(270);
        }
        printf("\n");        
    }
    sleep(2);
    bcm2835_gpio_set(RPI_GPIO_P1_22); //CS1
    return 0;
};
