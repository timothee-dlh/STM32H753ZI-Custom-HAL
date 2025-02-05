#include <stdint.h>
#include "systick.h"
#include "utils.h"

volatile uint32_t s_tick = 0;

void systick_enable(void)
{

        SYSTICK->LOAD = (FREQ / 1000U) - 1U; // Systick 
        SYSTICK->VAL = 0x00; // Systick default val
        SYSTICK->CTRL |= 0b111;  // Enable systick
}
