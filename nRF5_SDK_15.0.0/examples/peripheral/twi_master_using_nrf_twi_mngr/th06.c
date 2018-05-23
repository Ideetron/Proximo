/**
 *
 */
#include "th06.h"



//uint8_t NRF_TWI_MNGR_BUFFER_LOC_IND mma7660_xout_reg_addr = MMA7660_REG_XOUT;
uint8_t NRF_TWI_MNGR_BUFFER_LOC_IND th06_write_user_reg1 = TH06_WRITE_USER_REG1;


// Read the user register for the TH06 settings.
static uint8_t NRF_TWI_MNGR_BUFFER_LOC_IND default_config[] = { TH06_READ_USER_REG1, 1 };

//nrf_twi_mngr_transfer_t const th06_init_transfers[1] =
//{
//    NRF_TWI_MNGR_WRITE(THO6_I2C_ADDRESS, default_config, sizeof(default_config), 0)
//};









