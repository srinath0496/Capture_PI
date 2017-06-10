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
UINT_8 spi_read_data();
//UINT_8 spi_read(UINT_8* data);

enum CONFIG1_bits
{
        SINGLE_SHOT = 0x80,
        DR2 = 0x04,
        DR1 = 0x02,
        DR0 = 0x01,
        CONFIG_const = 0x00,
        SAMP_125_SPS = CONFIG_const,
        SAMP_250_SPS = (CONFIG_const | DR0),
        SAMP_500_SPS =  (CONFIG_const | DR1),
        SAMP_1_SPS =  (CONFIG_const | DR0 | DR1),
        SAMP_2_SPS =  (CONFIG_const | DR2),
        SAMP_4_SPS =  (CONFIG_const | DR0 | DR2),
        SAMP_8_SPS =  (CONFIG_const | DR1 | DR2)
};

enum CONFIG2_bits
{
        PDB_LOFF_COMP = 0x40,
        PDB_REFBUF = 0x20,
        VREF_4V = 0x10,
        CLK_EN = 0x08,
        INT_TEST = 0x02,
        TEST_FREQ = 0x01,
        CONFIG2_const = 0x80,
        INT_TEST_1HZ = (CONFIG2_const | INT_TEST | TEST_FREQ),
        INT_TEST_DC = (CONFIG2_const | INT_TEST)
};

enum reg
{
       ID = 0x00,
       CONFIG1 = 0x01,
       CONFIG2 = 0x02,
       CONFIG3 = 0x03,
       LOFF = 0x03,
       CHnSET = 0x03,
      CH1SET = CHnSET +1,
        CH2SET = CHnSET +2,
        GPIO = 0x0b
};

enum spi_command
{
        RDATAC = 0x10,
        SDATAC = 0x11,
        RDATA = 0x12

};
