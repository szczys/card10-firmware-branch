#include "portexpander.h"

#include "i2c.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

static bool detected = false;
static uint8_t output_state;

void portexpander_init(void)
{
	uint8_t addr = 0x21;
	int ret;

	// Enable pull-ups for buttons
	uint8_t command[] = { 0x43, 0x68 };
	ret = I2C_MasterWrite(MXC_I2C1_BUS0, addr << 1, command, 2, 0);

	if (ret != 2) {
		printf("portexpander NOT detected\n");
		detected = false;
		return;
	}
	detected = true;

	// Set _all_ outputs to open-drain to support the high side p-channel transistors.
	command[0] = 0x4F;
	command[1] = 0x01;
	I2C_MasterWrite(MXC_I2C1_BUS0, addr << 1, command, 2, 0);

	// Enable outputs for the transistors, the LED and the LCD reset
	command[0] = 0x03;
	command[1] = 0x68;
	I2C_MasterWrite(MXC_I2C1_BUS0, addr << 1, command, 2, 0);

	// Set outputs to high (i.e. open-drain)
	output_state = 0x97;
	command[0]   = 0x01;
	command[1]   = output_state;
	I2C_MasterWrite(MXC_I2C1_BUS0, addr << 1, command, 2, 0);
}

uint8_t portexpander_get(void)
{
	uint8_t addr      = 0x21;
	uint8_t command[] = { 0x00 };
	uint8_t buf       = 0xFF;

	if (detected) {
		I2C_MasterWrite(MXC_I2C1_BUS0, addr << 1, command, 1, 1);
		I2C_MasterRead(MXC_I2C1_BUS0, addr << 1, &buf, 1, 0);
	}

	return buf;
}

bool portexpander_detected(void)
{
	return detected;
}

void portexpander_set(uint8_t pin, uint8_t value)
{
	uint8_t addr = 0x21;
	uint8_t command[2];

	if (detected && pin < 8) {
		if (value) {
			output_state |= (1 << pin);
		} else {
			output_state &= ~(1 << pin);
		}

		command[0] = 0x01;
		command[1] = output_state;
		I2C_MasterWrite(MXC_I2C1_BUS0, addr << 1, command, 2, 0);
	}
}
