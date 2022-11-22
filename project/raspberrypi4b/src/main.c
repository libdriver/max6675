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
 * @file      main.c
 * @brief     main source file
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

#include "driver_max6675_read_test.h"
#include "driver_max6675_basic.h"
#include <stdlib.h>

/**
 * @brief     max6675 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t max6675(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            max6675_info_t info;
            
            /* print max6675 info */
            max6675_info(&info);
            max6675_interface_debug_print("max6675: chip is %s.\n", info.chip_name);
            max6675_interface_debug_print("max6675: manufacturer is %s.\n", info.manufacturer_name);
            max6675_interface_debug_print("max6675: interface is %s.\n", info.interface);
            max6675_interface_debug_print("max6675: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
            max6675_interface_debug_print("max6675: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            max6675_interface_debug_print("max6675: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            max6675_interface_debug_print("max6675: max current is %0.2fmA.\n", info.max_current_ma);
            max6675_interface_debug_print("max6675: max temperature is %0.1fC.\n", info.temperature_max);
            max6675_interface_debug_print("max6675: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            max6675_interface_debug_print("max6675: SCK connected to GPIO11(BCM).\n");
            max6675_interface_debug_print("max6675: MISO connected to GPIO9(BCM).\n");
            max6675_interface_debug_print("max6675: CS connected to GPIO8(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show max6675 help */
            
            help:
            max6675_interface_debug_print("max6675 -i\n\tshow max6675 chip and driver information.\n");
            max6675_interface_debug_print("max6675 -h\n\tshow max6675 help.\n");
            max6675_interface_debug_print("max6675 -p\n\tshow max6675 pin connections of the current board.\n");
            max6675_interface_debug_print("max6675 -t read <times>\n\trun max6675 read test.times is the test times.\n");
            max6675_interface_debug_print("max6675 -c read <times>\n\trun max6675 read function.times is the read times.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run the test */
        if (strcmp("-t", argv[1]) == 0)
        {
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t times;
                
                times = atoi(argv[3]);
                res = max6675_read_test(times);
                if (res != 0)
                {
                    return 1;
                }
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run the function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t i;
                uint32_t times;
                
                times = atoi(argv[3]);
                res = max6675_basic_init();
                if (res != 0)
                {
                    return 1;
                }
                
                for (i = 0; i < times; i++)
                {
                    uint16_t raw;
                    float temp;
                    
                    /* read data */
                    res = max6675_basic_read(&raw, &temp);
                    if (res != 0)
                    {
                        (void)max6675_basic_deinit();
                        
                        return 1;
                    }
                    
                    /* output */
                    max6675_interface_debug_print("%d/%d %0.2fC.\n", i + 1, times, temp);
                    
                    /* delay 1000ms */
                    max6675_interface_delay_ms(1000);
                }
                
                /* deinit */
                (void)max6675_basic_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = max6675(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        max6675_interface_debug_print("max6675: run failed.\n");
    }
    else if (res == 5)
    {
        max6675_interface_debug_print("max6675: param is invalid.\n");
    }
    else
    {
        max6675_interface_debug_print("max6675: unknow status code.\n");
    }

    return 0;
}
