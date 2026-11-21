/*
 * lps2xhh.c
 *
 *  Created on: 16 nov. 2026
 *      Author: Ludo
 */

#include "lps2xhh.h"

#ifndef LPS2XHH_DRIVER_DISABLE_FLAGS_FILE
#include "lps2xhh_driver_flags.h"
#endif
#include "lps2xhh_hw.h"
#include "error.h"
#include "types.h"

#ifndef LPS2XHH_DRIVER_DISABLE

/*** LPS2XHH local macros ***/

#define LPS2XHH_WRITE_COMMAND_BUFFER_SIZE   2

#define LPS2XHH_CONVERSION_DELAY_MS         10
#define LPS2XHH_CONVERSION_TIMEOUT_MS       2000

#define LPS2XHH_PRESSURE_SENSITIVITY        4096
#define LPS2XHH_TEMPERATURE_SENSITIITY      10

/*** LPS2XHH local structures ***/

/*******************************************************************/
typedef enum {
    LPS2XHH_REGISTER_INTERRUPT_CFG = 0x0B,
    LPS2XHH_REGISTER_THS_P_L = 0x0C,
    LPS2XHH_REGISTER_THS_P_H = 0x0D,
    LPS2XHH_REGISTER_IF_CTRL = 0x0E,
    LPS2XHH_REGISTER_WHO_AM_I = 0x0F,
    LPS2XHH_REGISTER_CTRL_REG1 = 0x10,
    LPS2XHH_REGISTER_CTRL_REG2 = 0x11,
    LPS2XHH_REGISTER_CTRL_REG3 = 0x12,
    LPS2XHH_REGISTER_FIFO_CTRL = 0x13,
    LPS2XHH_REGISTER_FIFO_WTM = 0x14,
    LPS2XHH_REGISTER_REF_P_L = 0x15,
    LPS2XHH_REGISTER_REF_P_H = 0x16,
    LPS2XHH_REGISTER_RPDS_L = 0x18,
    LPS2XHH_REGISTER_RPDS_H = 0x19,
    LPS2XHH_REGISTER_INT_SOURCE = 0x24,
    LPS2XHH_REGISTER_FIFO_STATUS1 = 0x25,
    LPS2XHH_REGISTER_FIFO_STATUS2 = 0x26,
    LPS2XHH_REGISTER_STATUS = 0x27,
    LPS2XHH_REGISTER_PRESS_OUT_XL = 0x28,
    LPS2XHH_REGISTER_PRESS_OUT_L = 0x29,
    LPS2XHH_REGISTER_PRESS_OUT_H = 0x2A,
    LPS2XHH_REGISTER_TEMP_OUT_L = 0x2B,
    LPS2XHH_REGISTER_TEMP_OUT_H = 0x2C,
    LPS2XHH_REGISTER_LPFP_RES = 0x3C,
    LPS2XHH_REGISTER_FIFO_DATA_OUT_PRESS_XL = 0x78,
    LPS2XHH_REGISTER_FIFO_DATA_OUT_PRESS_L = 0x79,
    LPS2XHH_REGISTER_FIFO_DATA_OUT_PRESS_H = 0x7A,
    LPS2XHH_REGISTER_FIFO_DATA_OUT_TEMP_L = 0x7B,
    LPS2XHH_REGISTER_FIFO_DATA_OUT_TEMP_H = 0x7C,
    LPS2XHH_REGISTER_LAST
} LPS2XHH_register_t;

/*** LPS2XHH local functions ***/

/*******************************************************************/
static LPS2XHH_status_t _LPS2XHH_write_register(uint8_t i2c_address, LPS2XHH_register_t register_address, uint8_t value) {
    // Local variables.
    LPS2XHH_status_t status = LPS2XHH_SUCCESS;
    uint8_t register_write_command[LPS2XHH_WRITE_COMMAND_BUFFER_SIZE] = { register_address, value };
    // I2C transfer.
    status = LPS2XHH_HW_i2c_write(i2c_address, register_write_command, LPS2XHH_WRITE_COMMAND_BUFFER_SIZE, 1);
    if (status != LPS2XHH_SUCCESS) goto errors;
errors:
    return status;
}

/*******************************************************************/
static LPS2XHH_status_t _LPS2XHH_read_register(uint8_t i2c_address, LPS2XHH_register_t register_address, uint8_t* value) {
    // Local variables.
    LPS2XHH_status_t status = LPS2XHH_SUCCESS;
    LPS2XHH_register_t local_addr = register_address;
    // I2C transfer.
    status = LPS2XHH_HW_i2c_write(i2c_address, &local_addr, 1, 1);
    if (status != LPS2XHH_SUCCESS) goto errors;
    status = LPS2XHH_HW_i2c_read(i2c_address, value, 1);
    if (status != LPS2XHH_SUCCESS) goto errors;
errors:
    return status;
}

/*** LPS2XHH functions ***/

/*******************************************************************/
LPS2XHH_status_t LPS2XHH_init(void) {
    // Local variables.
    LPS2XHH_status_t status = LPS2XHH_SUCCESS;
    // Init hardware interface.
    status = LPS2XHH_HW_init();
    if (status != LPS2XHH_SUCCESS) goto errors;
errors:
    return status;
}

/*******************************************************************/
LPS2XHH_status_t LPS2XHH_de_init(void) {
    // Local variables.
    LPS2XHH_status_t status = LPS2XHH_SUCCESS;
    // Release hardware interface.
    status = LPS2XHH_HW_de_init();
    if (status != LPS2XHH_SUCCESS) goto errors;
errors:
    return status;
}

/*******************************************************************/
LPS2XHH_status_t LPS2XHH_get_pressure_temperature(uint8_t i2c_address, int32_t* pressure_pa, int32_t* temperature_tenth_degrees) {
    // Local variables.
    LPS2XHH_status_t status = LPS2XHH_SUCCESS;
    uint8_t reg_value = 0;
    uint32_t loop_count_ms = 0;
    uint32_t raw_data = 0;
    // Check parameters.
    if ((pressure_pa == NULL) || (temperature_tenth_degrees == NULL)) {
        status = LPS2XHH_ERROR_NULL_PARAMETER;
        goto errors;
    }
    // Disable I3C interface.
    status = _LPS2XHH_write_register(i2c_address, LPS2XHH_REGISTER_IF_CTRL, 0x02);
    if (status != LPS2XHH_SUCCESS) goto errors;
    // Trigger one shot measurement in low noise mode.
    status = _LPS2XHH_write_register(i2c_address, LPS2XHH_REGISTER_CTRL_REG2, 0x03);
    if (status != LPS2XHH_SUCCESS) goto errors;
    // Wait for conversion to complete.
    do {
        // Read status register.
        status = _LPS2XHH_read_register(i2c_address, LPS2XHH_REGISTER_STATUS, &reg_value);
        if (status != LPS2XHH_SUCCESS) goto errors;
        // Delay.
        status = LPS2XHH_HW_delay_milliseconds(LPS2XHH_CONVERSION_DELAY_MS);
        if (status != LPS2XHH_SUCCESS) goto errors;
        // Exit if timeout.
        loop_count_ms += LPS2XHH_CONVERSION_DELAY_MS;
        if (loop_count_ms > LPS2XHH_CONVERSION_TIMEOUT_MS) {
            status = LPS2XHH_ERROR_CONVERSION_TIMEOUT;
            goto errors;
        }
    }
    while ((reg_value & 0x03) != 0x03);
    // Read raw pressure data.
    status = _LPS2XHH_read_register(i2c_address, LPS2XHH_REGISTER_PRESS_OUT_XL, &reg_value);
    if (status != LPS2XHH_SUCCESS) goto errors;
    raw_data = ((uint32_t) reg_value);
    status = _LPS2XHH_read_register(i2c_address, LPS2XHH_REGISTER_PRESS_OUT_L, &reg_value);
    if (status != LPS2XHH_SUCCESS) goto errors;
    raw_data |= ((uint32_t) (reg_value) << 8);
    status = _LPS2XHH_read_register(i2c_address, LPS2XHH_REGISTER_PRESS_OUT_H, &reg_value);
    if (status != LPS2XHH_SUCCESS) goto errors;
    raw_data |= ((uint32_t) (reg_value) << 16);
    // Compute pressure.
    (*pressure_pa) = (int32_t) ((raw_data * 100) / (LPS2XHH_PRESSURE_SENSITIVITY));
    // Read raw temperature data.
    status = _LPS2XHH_read_register(i2c_address, LPS2XHH_REGISTER_TEMP_OUT_L, &reg_value);
    if (status != LPS2XHH_SUCCESS) goto errors;
    raw_data = ((uint32_t) reg_value);
    status = _LPS2XHH_read_register(i2c_address, LPS2XHH_REGISTER_TEMP_OUT_H, &reg_value);
    if (status != LPS2XHH_SUCCESS) goto errors;
    raw_data |= ((uint32_t) (reg_value) << 8);
    // Compute temperature.
    (*temperature_tenth_degrees) = (int32_t) (((int16_t) raw_data) / ((int16_t) LPS2XHH_TEMPERATURE_SENSITIITY));
errors:
    return status;
}

#endif /* LPS2XHH_DRIVER_DISABLE */
