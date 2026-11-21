/*
 * lps2xhh_hw.h
 *
 *  Created on: 16 nov. 2026
 *      Author: Ludo
 */

#ifndef __LPS2XHH_HW_H__
#define __LPS2XHH_HW_H__

#ifndef LPS2XHH_DRIVER_DISABLE_FLAGS_FILE
#include "lps2xhh_driver_flags.h"
#endif
#include "lps2xhh.h"
#include "types.h"

#ifndef LPS2XHH_DRIVER_DISABLE

/*** LPS2XHH HW functions ***/

/*!******************************************************************
 * \fn LPS2XHH_status_t LPS2XHH_HW_init(void)
 * \brief Init LPS2XHH hardware interface.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
LPS2XHH_status_t LPS2XHH_HW_init(void);

/*!******************************************************************
 * \fn LPS2XHH_status_t LPS2XHH_HW_de_init(void)
 * \brief Release LPS2XHH hardware interface.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
LPS2XHH_status_t LPS2XHH_HW_de_init(void);

/*!******************************************************************
 * \fn LPS2XHH_status_t LPS2XHH_HW_i2c_write(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes, uint8_t stop_flag)
 * \brief Write data to sensor over I2C bus.
 * \param[in]   i2c_address: 7-bits sensor address.
 * \param[in]   data: Byte array to send.
 * \param[in]   data_size_bytes: Number of bytes to send.
 * \param[in]   stop_flag: Generate stop condition at the end of the transfer if non zero.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
LPS2XHH_status_t LPS2XHH_HW_i2c_write(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes, uint8_t stop_flag);

/*!******************************************************************
 * \fn LPS2XHH_status_t LPS2XHH_HW_i2c_read(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes)
 * \brief Read data from sensor over I2C bus.
 * \param[in]   i2c_address: 7-bits sensor address.
 * \param[in]   data_size_bytes: Number of bytes to read.
 * \param[out]  data: Byte array that will contain the read data.
 * \retval      Function execution status.
 *******************************************************************/
LPS2XHH_status_t LPS2XHH_HW_i2c_read(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes);

/*!******************************************************************
 * \fn LPS2XHH_status_t LPS2XHH_HW_delay_milliseconds(uint32_t delay_ms)
 * \brief Delay function.
 * \param[in]   delay_ms: Delay to wait in ms.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
LPS2XHH_status_t LPS2XHH_HW_delay_milliseconds(uint32_t delay_ms);

#endif /* LPS2XHH_DRIVER_DISABLE */

#endif /* __LPS2XHH_HW_H__ */
