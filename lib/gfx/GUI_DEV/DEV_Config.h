/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* |	This version:   V1.0
* | Date        :   2018-11-22
* | Info        :

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include "Debug.h"
#include "spi.h"
#include "tmr.h"
#include "tmr_utils.h"
#include <stdint.h>
#include <stdio.h>


#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * GPIO config
**/
extern const gpio_cfg_t DEV_DC_PIN;

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) GPIO_OutPut(&_pin, _value == 0? 0 : _pin.mask)


/**
 * SPI
**/
void lcd_write(uint8_t* data, int size);
void display_set_reset_pin(uint8_t state);
#define DEV_SPI_WRITE(_dat) lcd_write(&_dat, 1)
#define DEV_RESET_LOW() display_set_reset_pin(0)
#define DEV_RESET_HIGH() display_set_reset_pin(1)
/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) TMR_Delay(MXC_TMR0, MSEC(__xms), 0)

/**
 * PWM_BL
**/

//#define DEV_Set_BL(_Value)     DEV_BL_PIN= _Value
void DEV_Set_BL(uint16_t _Value);
/*-----------------------------------------------------------------------------*/

#endif
