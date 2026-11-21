/*
 * lps2xhh.h
 *
 *  Created on: 16 nov. 2026
 *      Author: Ludo
 */

#ifndef __LPS2XHH_H__
#define __LPS2XHH_H__

#ifndef LPS2XHH_DRIVER_DISABLE_FLAGS_FILE
#include "lps2xhh_driver_flags.h"
#endif
#include "error.h"
#include "types.h"

/*** LPS2XHH structures ***/

/*!******************************************************************
 * \enum LPS2XHH_status_t
 * \brief LPS2XHH driver error codes.
 *******************************************************************/
typedef enum {
    // Driver errors.
    LPS2XHH_SUCCESS = 0,
    LPS2XHH_ERROR_NULL_PARAMETER,
    LPS2XHH_ERROR_CONVERSION_TIMEOUT,
    // Low level drivers errors.
    LPS2XHH_ERROR_HW_FUNCTION_NOT_IMPLEMENTED,
    LPS2XHH_ERROR_BASE_I2C = ERROR_BASE_STEP,
    LPS2XHH_ERROR_BASE_DELAY = (LPS2XHH_ERROR_BASE_I2C + LPS2XHH_DRIVER_I2C_ERROR_BASE_LAST),
    // Last base value.
    LPS2XHH_ERROR_BASE_LAST = (LPS2XHH_ERROR_BASE_DELAY + LPS2XHH_DRIVER_DELAY_ERROR_BASE_LAST),
} LPS2XHH_status_t;

#ifndef LPS2XHH_DRIVER_DISABLE

/*** LPS2XHH functions ***/

/*!******************************************************************
 * \fn LPS2XHH_status_t LPS2XHH_init(void)
 * \brief Init LPS2XHH driver.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
LPS2XHH_status_t LPS2XHH_init(void);

/*!******************************************************************
 * \fn LPS2XHH_status_t LPS2XHH_de_init(void)
 * \brief Release LPS2XHH driver.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
LPS2XHH_status_t LPS2XHH_de_init(void);

/*!******************************************************************
 * \fn LPS2XHH_status_t LPS2XHH_get_pressure_temperature(uint8_t i2c_address, int32_t* pressure_pa, int32_t* temperature_tenth_degrees)
 * \brief Perform pressure and temperature measurements.
 * \param[in]   i2c_address: I2C address of the sensor.
 * \param[out]  pressure_pa: Pointer to integer that will contain the atmospheric pressure in Pa.
 * \param[out]  temperature_tenth_degrees: Pointer to integer that will contain the temperature in 1/10 Celsius degrees.
 * \retval      Function execution status.
 *******************************************************************/
LPS2XHH_status_t LPS2XHH_get_pressure_temperature(uint8_t i2c_address, int32_t* pressure_pa, int32_t* temperature_tenth_degrees);

/*******************************************************************/
#define LPS2XHH_exit_error(base) { ERROR_check_exit(lps2xhh_status, LPS2XHH_SUCCESS, base) }

/*******************************************************************/
#define LPS2XHH_stack_error(base) { ERROR_check_stack(lps2xhh_status, LPS2XHH_SUCCESS, base) }

/*******************************************************************/
#define LPS2XHH_stack_exit_error(base, code) { ERROR_check_stack_exit(lps2xhh_status, LPS2XHH_SUCCESS, base, code) }

#endif /* LPS2XHH_DRIVER_DISABLE */

#endif /* __LPS2XHH_H__ */
