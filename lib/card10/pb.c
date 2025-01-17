/*******************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-08-13 23:38:48 +0000 (Mon, 13 Aug 2018) $
 * $Revision: 36945 $
 *
 ******************************************************************************/

#include "mxc_config.h"
#include "mxc_assert.h"
#include "pb.h"
#include "portexpander.h"
#include "MAX77650-Arduino-Library.h"
#include <stddef.h>
/******************************************************************************/
int PB_Init(void)
{
	int retval = E_NO_ERROR;
	unsigned int i;

	// If we have a port expander, its pins are already configured
	if (!portexpander_detected()) {
		// Enable pushbutton inputs
		for (i = 0; i < num_pbs; i++) {
			if (GPIO_Config(&pb_pin[i]) != E_NO_ERROR) {
				retval = E_UNKNOWN;
			}
		}
	}

	return retval;
}

/******************************************************************************/
int PB_RegisterCallback(unsigned int pb, pb_callback callback)
{
	MXC_ASSERT(pb < num_pbs);

	// TODO: portexpander support
	if (callback) {
		// Register callback
		GPIO_RegisterCallback(&pb_pin[pb], callback, (void *)pb);

		// Configure and enable interrupt
		GPIO_IntConfig(&pb_pin[pb], GPIO_INT_EDGE, GPIO_INT_FALLING);
		GPIO_IntEnable(&pb_pin[pb]);
		NVIC_EnableIRQ((IRQn_Type)MXC_GPIO_GET_IRQ(pb_pin[pb].port));
	} else {
		// Disable interrupt and clear callback
		GPIO_IntDisable(&pb_pin[pb]);
		GPIO_RegisterCallback(&pb_pin[pb], NULL, NULL);
	}

	return E_NO_ERROR;
}

//******************************************************************************
void PB_IntEnable(unsigned int pb)
{
	// TODO: portexpander support
	MXC_ASSERT(pb < num_pbs);
	GPIO_IntEnable(&pb_pin[pb]);
}

//******************************************************************************
void PB_IntDisable(unsigned int pb)
{
	// TODO: portexpander support
	MXC_ASSERT(pb < num_pbs);
	GPIO_IntDisable(&pb_pin[pb]);
}

//******************************************************************************
void PB_IntClear(unsigned int pb)
{
	// TODO: portexpander support
	MXC_ASSERT(pb < num_pbs);
	GPIO_IntClr(&pb_pin[pb]);
}

//******************************************************************************
int PB_Get(unsigned int pb)
{
	static const uint8_t expander_pins[] = { 5, 0x0, 3, 6 };
	MXC_ASSERT(pb <= 4);
	switch (pb) {
	case 1:
	case 3:
	case 4:
		if (portexpander_detected()) {
			uint8_t port = portexpander_get();
			return (port & (1 << expander_pins[pb - 1])) == 0;
		} else {
			return GPIO_InGet(&pb_pin[pb - 1]) == 0;
		}
		break;
	case 2:
		return MAX77650_getDebounceStatusnEN0();
		break;
	}
	return 0;
}
