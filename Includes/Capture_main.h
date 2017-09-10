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
//UINT_8 spi_read(UINT_8* data);
