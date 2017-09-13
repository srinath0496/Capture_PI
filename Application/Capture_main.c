#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "bcm2835.h"
#include "typedef.h"
#include "Capture_main.h"
#include "ADS1298.h"

char ads_reg_lable[4][9][50] =  {
                {"","","","","","","","","DUMMY"},
                {"HR","DAISY_EN_N","CLK_EN","RESERVED","RESERVED","DR2","DR1","DR0","CONFIG1"},
                {"RESERVED","RESERVED","WCT_CHOP","INT_TEST","RESERVED","TEST_AMP","TEST_FREQ1","TEST_FREQ0","CONFIG2"},
                {"PD_REFBUF_N","RESERVED","VREF_4V","RLD_MEAS","RLDREF_INT","PD_RLD_N","RLD_LOFF_SENS","RLD_STAT","CONFIG3"}
};
char menu_itens[10][50] = {
                            "",
                            "Read Device ID",
                            "Display all ADS Registers",
                            "Set ADS Registers",
                            "Channel SelfTest",
                            "Start Continous Read",
                            "Stop Continous Read",
                            "Single Data Read",
                            "Read ADS Channels",
                            "Exit"
};


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
            for(i=1;i<10;i++)
            printf("%d.%s\n",i,menu_itens[i]);
            scanf("%d",&option);
            switch(option)
            {
                case 1:
                            printf("The Dev ID is %X\n",spi_read_byte(ID));
                            break;
                case 2:
                            print_config(TYPE_CONFIG1,spi_read_byte(CONFIG1));
                            //sleep(1);
                            print_config(TYPE_CONFIG2,spi_read_byte(CONFIG2));
                            //sleep(1);
                            print_config(TYPE_CONFIG3,spi_read_byte(CONFIG3));
                            break;
                case 4:
                            ads1298_chan_setup(8,8,1);
                            bcm2835_delay(5);
                            break;
                case 5:
                            //cm2835_gpio_set(RPI_GPIO_P1_18);  //SPI_START
                            spi_send_cmd(RDATAC);
                            bcm2835_delay(5);
                            break;
                case 6:
                            //cm2835_gpio_set(RPI_GPIO_P1_18);  //SPI_START
                            spi_send_cmd(SDATAC);
                            bcm2835_delay(5);
                            break;
                case 7:
                            //cm2835_gpio_set(RPI_GPIO_P1_18);  //SPI_START
                            spi_send_cmd(RDATA);
                            bcm2835_delay(5);
                            break;
                case 8:
                //spi_send_cmd(RDATAC);
                bcm2835_delay(5);
                            for(i=0;i<6;i++)
                            spi_read_data(8,1,&data);
                           
                            bcm2835_delay(5);
                            break;
                 case 9:
                                bcm2835_close();
                                exit(1);

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
    union STR_CONFIG_1 config1_reg;
    spi_write_byte(GPIO,0x00);
    spi_write_byte(CONFIG1,HIGH_RES_1k_SPS);
    print_config(TYPE_CONFIG1,spi_read_byte(CONFIG1));
    if(intTest)
    {
        spi_write_byte(CONFIG2,CONFIG2_const | INT_TEST_1HZ | TEST_AMP);
        print_config(TYPE_CONFIG2,spi_read_byte(CONFIG2));
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

void print_config(UINT_8 config_type,UINT_8 reg_Buffer)
{
    UINT_8 maxBit = 0x80;
    UINT_8 bitOffset=7;
    UINT_8 i;
                            printf("ADS1298 %s REGISTER\n",ads_reg_lable[config_type][8]);
                            for(i=0;i<8;i++)
                            {
                                printf("1%s:%d\n",ads_reg_lable[config_type][i],(reg_Buffer&maxBit)>>bitOffset);
                                maxBit = maxBit /2;
                                bitOffset--;
                            }
                           
                            /*
                            printf("%s:%d\n",ads_reg_lable[config_type][0],(reg_Buffer&0x80)>>7);
                            printf("%s:%d\n",ads_reg_lable[config_type][1],(reg_Buffer&0x40)>>6);
                            printf("%s:%d\n",ads_reg_lable[config_type][2],(reg_Buffer&0x20)>>5);
                            printf("%s:%d\n",ads_reg_lable[config_type][3],(reg_Buffer&0x10)>>4);
                            printf("%s:%d\n",ads_reg_lable[config_type][4],(reg_Buffer&0x08)>>3);
                            printf("%s:%d\n",ads_reg_lable[config_type][5],(reg_Buffer&0x04)>>2);
                            printf("%s:%d\n",ads_reg_lable[config_type][6],(reg_Buffer&0x02)>>1);
                            printf("%s:%d\n",ads_reg_lable[config_type][7],(reg_Buffer&0x01));*/

}

/*void set_config(UINT_8 config_type,UINT_8 reg_Buffer)
{
    UINT_8 valueSet;
    union 

                            printf("ADS1298 %s REGISTER\n",ads_reg_lable[config_type][8]);
                            printf("%s:%d\t To Change Press (1/0). To Cancel Press Return\t",ads_reg_lable[config_type][0],(reg_Buffer&0x80)>>7);
                            if((getchar()!='\n')
                            {
                                struct
                            }
                            printf("%s:%d\n",ads_reg_lable[config_type][1],(reg_Buffer&0x40)>>6);
                            printf("%s:%d\n",ads_reg_lable[config_type][2],(reg_Buffer&0x20)>>5);
                            printf("%s:%d\n",ads_reg_lable[config_type][3],(reg_Buffer&0x10)>>4);
                            printf("%s:%d\n",ads_reg_lable[config_type][4],(reg_Buffer&0x08)>>3);
                            printf("%s:%d\n",ads_reg_lable[config_type][5],(reg_Buffer&0x04)>>2);
                            printf("%s:%d\n",ads_reg_lable[config_type][6],(reg_Buffer&0x02)>>1);
                            printf("%s:%d\n",ads_reg_lable[config_type][7],(reg_Buffer&0x01));

}*/