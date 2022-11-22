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
 * @file      driver_max6675_read_test.c
 * @brief     driver max6675 read test source file
 * @version   21.0.0
 * @author    Shifeng Li
 * @date      2022-11-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/11/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */
 
#include "driver_max6675_read_test.h"

static max6675_handle_t gs_handle;        /**< max6675 handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t max6675_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    max6675_info_t info;
    
    /* link functions */
    DRIVER_MAX6675_LINK_INIT(&gs_handle, max6675_handle_t);
    DRIVER_MAX6675_LINK_SPI_INIT(&gs_handle, max6675_interface_spi_init);
    DRIVER_MAX6675_LINK_SPI_DEINIT(&gs_handle, max6675_interface_spi_deinit);
    DRIVER_MAX6675_LINK_SPI_READ_COMMAND(&gs_handle, max6675_interface_spi_read_cmd);
    DRIVER_MAX6675_LINK_DELAY_MS(&gs_handle, max6675_interface_delay_ms);
    DRIVER_MAX6675_LINK_DEBUG_PRINT(&gs_handle, max6675_interface_debug_print);
    
    /* max6675 info */
    res = max6675_info(&info);
    if (res != 0)
    {
        max6675_interface_debug_print("max6675: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        max6675_interface_debug_print("max6675: chip is %s.\n", info.chip_name);
        max6675_interface_debug_print("max6675: manufacturer is %s.\n", info.manufacturer_name);
        max6675_interface_debug_print("max6675: interface is %s.\n", info.interface);
        max6675_interface_debug_print("max6675: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        max6675_interface_debug_print("max6675: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        max6675_interface_debug_print("max6675: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        max6675_interface_debug_print("max6675: max current is %0.2fmA.\n", info.max_current_ma);
        max6675_interface_debug_print("max6675: max temperature is %0.1fC.\n", info.temperature_max);
        max6675_interface_debug_print("max6675: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* max6675 init */
    res = max6675_init(&gs_handle);
    if (res != 0)
    {
        max6675_interface_debug_print("max6675: init failed.\n");
       
        return 1;
    }
    
    /* start read test */
    max6675_interface_debug_print("max6675: start read test.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t raw;
        float temp;
        
        /* read data */
        res = max6675_read(&gs_handle, &raw, &temp);
        if (res != 0)
        {
            max6675_interface_debug_print("max6675: read failed.\n");
            (void)max6675_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        max6675_interface_debug_print("max6675: temperature is %0.2fC.\n", temp);
        
        /* delay 1000ms */
        max6675_interface_delay_ms(1000);
    }
    
    /* finish read test */
    max6675_interface_debug_print("max6675: finish read test.\n");  
    (void)max6675_deinit(&gs_handle);
    
    return 0;
}
