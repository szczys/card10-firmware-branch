/*******************************************************************************
 * License: TBD
 ******************************************************************************/

/***** Includes *****/
#include "pmic.h"
#include "leds.h"
#include "card10.h"

#include "gfx.h"
#include "display.h"

#include "tmr_utils.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <Heart.h>

int main(void)
{
	card10_init();
	card10_diag();

	gfx_copy_region_raw(
		&display_screen, 0, 0, 160, 80, 2, (const void *)(Heart)
	);
	gfx_update(&display_screen);

	// Release core1
	core1_start((void *)0x10080000);
	int h = 0;

	while (1) {
#define NUM 15

		leds_update();
		TMR_Delay(MXC_TMR0, MSEC(10), 0);
		h++;

		// Send a txev using `sev` every once in a while to wake up core1
		// and let it do something
		if (h % 100 == 0) {
			printf("core0: Triggering core1 using SEV ...\n");
			__asm volatile("sev");
		}
	}
}
