/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_max6675.h
 * @brief     driver max6675 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-11-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/11/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_MAX6675_H
#define DRIVER_MAX6675_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup max6675_driver max6675 driver function
 * @brief    max6675 driver modules
 * @{
 */

/**
 * @addtogroup max6675_base_driver
 * @{
 */

/**
 * @brief max6675 handle structure definition
 */
typedef struct max6675_handle_s
{
    uint8_t (*spi_init)(void);                                  /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                /**< point to a spi_deinit function address */
    uint8_t (*spi_read_cmd)(uint8_t *buf, uint16_t len);        /**< point to a spi_read_cmd function address */
    void (*delay_ms)(uint32_t ms);                              /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);            /**< point to a debug_print function address */
    uint8_t inited;                                             /**< inited flag */
} max6675_handle_t;

/**
 * @brief max6675 information structure definition
 */
typedef struct max6675_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} max6675_info_t;

/**
 * @}
 */

/**
 * @defgroup max6675_link_driver max6675 link driver function
 * @brief    max6675 link driver modules
 * @ingroup  max6675_driver
 * @{
 */

/**
 * @brief     initialize max6675_handle_t structure
 * @param[in] HANDLE points to a max6675 handle structure
 * @param[in] STRUCTURE is max6675_handle_t
 * @note      none
 */
#define DRIVER_MAX6675_LINK_INIT(HANDLE, STRUCTURE)               memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE points to a max6675 handle structure
 * @param[in] FUC points to a spi_init function address
 * @note      none
 */
#define DRIVER_MAX6675_LINK_SPI_INIT(HANDLE, FUC)                (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE points to a max6675 handle structure
 * @param[in] FUC points to a spi_deinit function address
 * @note      none
 */
#define DRIVER_MAX6675_LINK_SPI_DEINIT(HANDLE, FUC)              (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_read_cmd function
 * @param[in] HANDLE points to a max6675 handle structure
 * @param[in] FUC points to a spi_read_cmd function address
 * @note      none
 */
#define DRIVER_MAX6675_LINK_SPI_READ_COMMAND(HANDLE, FUC)        (HANDLE)->spi_read_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a max6675 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_MAX6675_LINK_DELAY_MS(HANDLE, FUC)                (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a max6675 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_MAX6675_LINK_DEBUG_PRINT(HANDLE, FUC)             (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup max6675_base_driver max6675 base driver function
 * @brief    max6675 base driver modules
 * @ingroup  max6675_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a max6675 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t max6675_info(max6675_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a max6675 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t max6675_init(max6675_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a max6675 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t max6675_deinit(max6675_handle_t *handle);

/**
 * @brief      read the temperature
 * @param[in]  *handle points to a max6675 handle structure
 * @param[out] *raw points to a raw data buffer
 * @param[out] *temp points to a temp buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 thermocouple input is open
 * @note       none
 */
uint8_t max6675_read(max6675_handle_t *handle,uint16_t *raw, float *temp);

/**
 * @}
 */

/**
 * @defgroup max6675_extern_driver max6675 extern driver function
 * @brief    max6675 extern driver modules
 * @ingroup  max6675_driver
 * @{
 */

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a max6675 handle structure
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t max6675_get_reg(max6675_handle_t *handle, uint16_t *data);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
