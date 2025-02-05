#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"

int timer_expired(uint32_t *t, uint32_t prd); 
void delay(int time);

#endif
