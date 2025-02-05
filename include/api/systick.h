#ifndef SYSTICK_H
#define SYSTICK_H

#include "stdint.h"

/*
 * Systick define used to access Systick registers trough Systick struct
 */
#define  SYSTICK ((struct systick *) 0xE000E010)


/*
 * Systick struct containing all 4 Systick registers
 */
struct systick {
    volatile uint32_t CTRL, LOAD, VAL, CALIB;
};

void systick_enable(void);

#endif
