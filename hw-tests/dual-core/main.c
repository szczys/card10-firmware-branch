/*******************************************************************************
 * License: TBD
 ******************************************************************************/

/***** Includes *****/
#include "pmic.h"
#include "leds.h"
#include "card10.h"

#include "GUI_Paint.h"

#include "tmr_utils.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <Heart.h>

void Core1_Start(void) {
    //MXC_GCR->gp0 = (uint32_t)(&__isr_vector_core1);
    MXC_GCR->gp0 = 0x10040000;
    MXC_GCR->perckcn1 &= ~MXC_F_GCR_PERCKCN1_CPU1;
}

void Core1_Stop(void) {
    MXC_GCR->perckcn1 |= MXC_F_GCR_PERCKCN1_CPU1;
}

int main(void)
{
    card10_init();
    card10_diag();

    Paint_DrawImage(Heart, 0, 0, 160, 80);
    LCD_Update();

    for(int i=0; i<11; i++) {
        leds_set_dim(i, 1);
    }

    int h = 0;

    // Release core1
    Core1_Start();

    while (1) {
        #define NUM     15
        for(int i=0; i<NUM; i++) {
            if(i < 12) {
                leds_set_hsv(i, (h + 360/NUM * i) % 360, 1., 1./8);
            } else {
                leds_set_hsv(i, (h + 360/NUM * i) % 360, 1., 1.);
            }
        }

        leds_update();
        TMR_Delay(MXC_TMR0, MSEC(10), 0);
        h++;
    }
}
