#include "stdint.h"
#include "utils.h"

extern uint32_t s_tick;

int timer_expired(uint32_t *t, uint32_t prd) 
{
        if (s_tick + prd < *t){
                *t = 0;                    // Time wrapped? Reset timer
        }
        if (*t == 0) {
                *t = s_tick + prd;                   // First poll? Set expiration
        }
        if (*t > s_tick) {
                return 0;  // Not expired yet, return
        }     
        *t = (s_tick - *t) > prd ? s_tick + prd : *t + prd;  // Next expiration time
        return 1;                                   // Expired, return true
}

void delay(uint32_t time)
{
        uint32_t current_time = s_tick;
        while (current_time + time * 1000 > s_tick) {
                spin(1);
        }
}
