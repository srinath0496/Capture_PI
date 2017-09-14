#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "bcm2835.h"
#include "typedef.h"
#include "Capture_main.h"
#include "ADS1298.h"

char ads_reg_lable[26][9][50] =  {
                {"","","","","","","","","DUMMY"},
                {"HR","DAISY_EN_N","CLK_EN","RESERVED","RESERVED","DR2","DR1","DR0","CONFIG1"},
                {"RESERVED","RESERVED","WCT_CHOP","INT_TEST","RESERVED","TEST_AMP","TEST_FREQ1","TEST_FREQ0","CONFIG2"},
                {"PD_REFBUF_N","RESERVED","VREF_4V","RLD_MEAS","RLDREF_INT","PD_RLD_N","RLD_LOFF_SENS","RLD_STAT","CONFIG3"},
                {"COMP_TH2","COMP_TH1","COMP_TH0","VLEAD_OFF_ EN","ILEAD_OFF1","ILEAD_OFF0","FLEAD_OFF1","FLEAD_OFF0","LOFF"},
                {"PD1","GAIN12","GAIN11","GAIN10","RESERVED","MUX12","MUX11","MUX10","CH1SET"},
                {"PD1","GAIN12","GAIN11","GAIN10","RESERVED","MUX12","MUX11","MUX10","CH2SET"},
                {"PD1","GAIN12","GAIN11","GAIN10","RESERVED","MUX12","MUX11","MUX10","CH3SET"},
                {"PD1","GAIN12","GAIN11","GAIN10","RESERVED","MUX12","MUX11","MUX10","CH4SET"},
                {"PD1","GAIN12","GAIN11","GAIN10","RESERVED","MUX12","MUX11","MUX10","CH5SET"},
                {"PD1","GAIN12","GAIN11","GAIN10","RESERVED","MUX12","MUX11","MUX10","CH6SET"},
                {"PD1","GAIN12","GAIN11","GAIN10","RESERVED","MUX12","MUX11","MUX10","CH7SET"},
                {"PD1","GAIN12","GAIN11","GAIN10","RESERVED","MUX12","MUX11","MUX10","CH8SET"},
                {"RLD8P","RLD7P","RLD6P","RLD5P","RLD4P","RLD3P","RLD2P","RLD1P","RLD_SENSP"},
                {"RLD8N","RLD7N","RLD6N","RLD5N","RLD4N","RLD3N","RLD2N","RLD1N","RLD_SENSN"},
                {"LOFF8P","LOFF7P","LOFF6P","LOFF5P","LOFF4P","LOFF3P","LOFF2P","LOFF1P","LOFF_SENSP"},
                {"LOFF8N","LOFF7N","LOFF6N","LOFF5N","LOFF4N","LOFF3N","LOFF2N","LOFF1N","LOFF_SENSN"},
                {"LOFF_FLIP8","LOFF_FLIP7","LOFF_FLIP6","LOFF_FLIP5","LOFF_FLIP4","LOFF_FLIP3","LOFF_FLIP2","LOFF_FLIP1","LOFF_FLIP"},
                {"IN8P_OFF","IN7P_OFF","IN6P_OFF","IN5P_OFF","IN4P_OFF","IN3P_OFF","IN2P_OFF","IN1P_OFF","LOFF_STATP"},
                {"IN8N_OFF","IN7N_OFF","IN6N_OFF","IN5N_OFF","IN4N_OFF","IN3N_OFF","IN2N_OFF","IN1N_OFF","LOFF_STATN"},
                {"GPIOD4","GPIOD3","GPIOD2","GPIOD1","GPIOC4","GPIOC3","GPIOC2""GPIOC1","GPIO"},
                {"RESERVED","RESERVED","RESERVED","PACEE1","PACEE0","PACEO1","PACEO0","PD_PACE_N","PACE"},
                {"RESP_DEMOD_EN1","RESP_MOD_EN1","RESERVED","RESP_PH2","RESP_PH1","RESP_PH0","RESP_CTRL1","RESP_CTRL0","RESP"},
                {"RESP_FREQ2","RESP_FREQ1","RESP_FREQ0","RESERVED","SINGLE_SHOT","WCT_TO_RLD","PD_LOFF_COMP_N","REESERVED","CONFIG4"},
                {"aVF_CH6","aVF_CH5","aVF_CH7","aVF_CH4","PD_WCTA_N","WCTA2","WCTA1","WCTA0","WCT1"},
                {"PD_WCTC_N","PD_WCTB_N","WCTB2""WCTB1","WCTB0","WCTC2","WCTC1","WCTC0","WCT2"}
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
            system("clear"); //clears the screen
            switch(option)
            {
                case 1:
                            printf("The Dev ID is %X\n",spi_read_byte(ID));
                            break;
                case 2:
                            //print_config(TYPE_CONFIG1,spi_read_byte(CONFIG1));
                            //sleep(1);
                           // print_config(TYPE_CONFIG2,spi_read_byte(CONFIG2));
                            //sleep(1);
                           // print_config(TYPE_CONFIG3,spi_read_byte(CONFIG3));
                            registry_menu(REG_READ);
                            break;
                case 3:
                            //spi_write_byte(CONFIG1, set_config(TYPE_CONFIG1,spi_read_byte(CONFIG1)));
                            registry_menu(REG_WRITE);
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
            //system("clear"); //clears the screen
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
                                printf("%s-------->\t%d\n",ads_reg_lable[config_type][i],(reg_Buffer&maxBit)>>bitOffset);
                                maxBit = maxBit /2;
                                bitOffset--;
                            }
                           
                          
return 0;
                        }
UINT_8 set_config(UINT_8 config_type,UINT_8 reg_Buffer)
{
    UINT_8 maxBit = 0x80;
    UINT_8 bitOffset=7;
    UINT_8 i,new_Buffer,set;
                            printf("ADS1298 %s REGISTER\n",ads_reg_lable[config_type][8]);
                            new_Buffer = reg_Buffer;
                            getchar();
                            
                            for(i=0;i<8;i++)
                            {
                                printf("%s:%d\t Press 1 to Set: 0 to Clear: Enter to Cancel\t",ads_reg_lable[config_type][i],(reg_Buffer&maxBit)>>bitOffset);
                                while((set = getchar())!='\n')
                                {
                                    switch(set)
                                    {
                                        case '1':
                                                new_Buffer = new_Buffer | maxBit;
                                                break;
                                        case '0':
                                                new_Buffer = new_Buffer & ~(maxBit);
                                                break;
                                        case '\n':
                                                 break;
                                        default:
                                        printf("Breaking");
                                                break;   
                                    }
                                }
                                maxBit = maxBit /2;
                                bitOffset--;
                            }
                         return new_Buffer;
                          
}

void registry_menu(UINT_8 operation)
{
    UINT_8 i;
    UINT_16 option;
                for(i=1;i<26;i++)
                printf("%d.%s REGISTER\n",i,ads_reg_lable[i][8]);
                printf("Select the Register number to be displayed\n");
                scanf("%d",&option);
                //operation = REG_READ;
                switch(operation)
                {
                    case REG_WRITE:
                             spi_write_byte(option, set_config(option,spi_read_byte(option)));
                             break;
                    case REG_READ:
                                print_config(option,spi_read_byte(option));
                                break;
                }
            
            }

