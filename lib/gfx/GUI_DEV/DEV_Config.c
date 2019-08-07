/*****************************************************************************
* | File        :   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* | This version:   V1.0
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
#include "DEV_Config.h"
#include "spi.h"

#define SPI SPI2

//const gpio_cfg_t DEV_CS_PIN = {PORT_0, PIN_8, GPIO_FUNC_OUT, GPIO_PAD_NONE};
//const gpio_cfg_t DEV_BL_PIN = {PORT_0, PIN_8, GPIO_FUNC_OUT, GPIO_PAD_NONE};
static spi_req_t req = {.rx_data = NULL, .bits=8, .width = SPI17Y_WIDTH_1, .ssel = 0, .deass = 1, .ssel_pol = SPI17Y_POL_LOW, .tx_num = 0, .rx_num = 0};
#define SPI_SPEED (15 * 1000 * 1000) // Bit Rate. Display has 15 MHz limit

/********************************************************************************/
void lcd_write(uint8_t *data, int size)
{
    sys_cfg_spi_t spi17y_master_cfg;

    spi17y_master_cfg.map = MAP_A;
    spi17y_master_cfg.ss0 = Enable;
    spi17y_master_cfg.ss1 = Disable;
    spi17y_master_cfg.ss2 = Disable;
    if (SPI_Init(SPI2, 0, SPI_SPEED, spi17y_master_cfg) != 0) {
        printf("Error configuring SPI\n");
        while (1)
            ;
    }
    req.tx_data = data;
    req.len = size;
    SPI_MasterTrans(SPI, &req);
}

