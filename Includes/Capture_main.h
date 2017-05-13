#include "types.h"

UINT_8 bcm_driver_init();
UINT_8 spi_select(UINT_8 chip_sel);
UINT_8 spi_deselect(UINT_8 chip_sel);
UINT_8 spi_rdwr();
//UINT_8 spi_read(UINT_8* data);
