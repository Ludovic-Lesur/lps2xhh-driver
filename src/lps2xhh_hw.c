/*
 * lps2xhh_hw.c
 *
 *  Created on: 16 nov. 2026
 *      Author: Ludo
 */

#include "lps2xhh_hw.h"

#ifndef LPS2XHH_DRIVER_DISABLE_FLAGS_FILE
#include "lps2xhh_driver_flags.h"
#endif
#include "lps2xhh.h"
#include "types.h"

#ifndef LPS2XHH_DRIVER_DISABLE

/*** LPS2XHH HW functions ***/

/*******************************************************************/
LPS2XHH_status_t __attribute__((weak)) LPS2XHH_HW_init(void) {
    // Local variables.
    LPS2XHH_status_t status = LPS2XHH_ERROR_HW_FUNCTION_NOT_IMPLEMENTED;
    /* To be implemented */
    return status;
}

/*******************************************************************/
LPS2XHH_status_t __attribute__((weak)) LPS2XHH_HW_de_init(void) {
    // Local variables.
    LPS2XHH_status_t status = LPS2XHH_ERROR_HW_FUNCTION_NOT_IMPLEMENTED;
    /* To be implemented */
    return status;
}

/*******************************************************************/
LPS2XHH_status_t __attribute__((weak)) LPS2XHH_HW_i2c_write(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes, uint8_t stop_flag) {
    // Local variables.
    LPS2XHH_status_t status = LPS2XHH_ERROR_HW_FUNCTION_NOT_IMPLEMENTED;
    /* To be implemented */
    UNUSED(i2c_address);
    UNUSED(data);
    UNUSED(data_size_bytes);
    UNUSED(stop_flag);
    return status;
}

/*******************************************************************/
LPS2XHH_status_t __attribute__((weak)) LPS2XHH_HW_i2c_read(uint8_t i2c_address, uint8_t* data, uint8_t data_size_bytes) {
    // Local variables.
    LPS2XHH_status_t status = LPS2XHH_ERROR_HW_FUNCTION_NOT_IMPLEMENTED;
    /* To be implemented */
    UNUSED(i2c_address);
    UNUSED(data);
    UNUSED(data_size_bytes);
    return status;
}

/*******************************************************************/
LPS2XHH_status_t __attribute__((weak)) LPS2XHH_HW_delay_milliseconds(uint32_t delay_ms) {
    // Local variables.
    LPS2XHH_status_t status = LPS2XHH_ERROR_HW_FUNCTION_NOT_IMPLEMENTED;
    /* To be implemented */
    UNUSED(delay_ms);
    return status;
}

#endif /* LPS2XHH_DRIVER_DISABLE */
