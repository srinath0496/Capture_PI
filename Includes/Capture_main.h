#include "typedef.h"

UINT_8 bcm_driver_init();
UINT_8 spi_select(UINT_8 chip_sel);
UINT_8 spi_deselect(UINT_8 chip_sel);
UINT_8 spi_rdwr();
UINT_8 spi_init();
UINT_8 ads1298_init();
UINT_8 ads1298_gpio_init();
UINT_8 spi_write_byte(UINT_8 reg_addr, UINT_8 value);
UINT_8 spi_read_byte(UINT_8 reg_addr);
UINT_8 spi_send_cmd(UINT_8 cmd);
UINT_8 spi_read_data(UINT_8 numchs,UINT_8 gpio,UINT_8* chData);
UINT_8 ads1298_chan_setup(UINT_8 numChs,UINT_8 max_numChs,UINT_8 intTest);
void print_config(UINT_8 config_type,UINT_8 reg_Buffer);
UINT_8 set_config(UINT_8 config_type,UINT_8 reg_Buffer);
void registry_menu(UINT_8 operation);
#define TYPE_CONFIG1 1
#define TYPE_CONFIG2 2
#define TYPE_CONFIG3 3
#define REG_READ 1
#define REG_WRITE 2
//UINT_8 spi_read(UINT_8* data);

union STR_CONFIG_1
{
	UINT_8 data;
	struct 
	{
		UINT_8 HR:1;
		UINT_8 DAISY_EN_N:1;
		UINT_8 CLK_EN:1;
		UINT_8 Reserved:2;
		UINT_8 DR2:1;
		UINT_8 DR1:1;
		UINT_8 DR0:1;
	}STR_CONFIG_DATA;
};

union STR_CONFIG_2
{
	UINT_8 data;
	struct
	{
		UINT_8 RES_1:2;
		UINT_8 WCT_CHOP:1;
		UINT_8 INT_TEST:1;
		UINT_8 RES_2:1;
		UINT_8 TEST_AMP:1;
		UINT_8 TEST_FREQ1:1;
		UINT_8 TEST_FREQ0:1;
	}STR_CONFIG_DATA;
};

union STR_CONFIG_3
{
	UINT_8 data;
	struct 
	{
		UINT_8 PD_REFBUF_N:1;
		UINT_8 RES_1:1;
		UINT_8 VREF_4V:1;
		UINT_8 RLD_MEAS:1;
		UINT_8 RLDREF_INT:1;
		UINT_8 PD_RLD_N:1;
		UINT_8 RLD_LOFF_SENS:1;
		UINT_8 RLD_STAT:1;
	}STR_CONFIG_DATA;
};

union STR_CONFIG
{
	UINT_8 data;
	struct 
	{
		UINT_8 BIT7:1;
		UINT_8 BIT6:1;
		UINT_8 BIT5:1;
		UINT_8 BIT4:1;
		UINT_8 BIT3:1;
		UINT_8 BIT2:1;
        UINT_8 BIT1:1;
        UINT_8 BIT0:1;
	}CONFIG_DATA;
};

