#include <stdint.h>
#include "main.h"
#include "uart.h"
#include "utils.h"

#define SRAM_START 0x20000000U
#define SRAM_SIZE (128U * 1024U)
#define SRAM_END   ((SRAM_START) + (SRAM_SIZE))
#define STACK_START SRAM_END

#define GPIOB ((struct gpio *) 0x58020400)

extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _lmaData;

extern uint32_t s_tick;

__attribute__ ((naked, noreturn)) void Reset_Handler(void);
__attribute__ ((weak)) void SysTick_Handler(void);
__attribute__ ((weak)) void Uart_Handler(void);
void Default_Handler(void);

__attribute__((section(".isr_vector"))) uint32_t vector[]=
{
    STACK_START,
    (uint32_t) Reset_Handler,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    (uint32_t) SysTick_Handler,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    (uint32_t) Uart_Handler,
};

__attribute__ ((naked, noreturn)) void Reset_Handler(void)
{

        /* Copie .data depuis la flash vers la sram */
        for (uint32_t *sptr = &_lmaData, *d_ptr = &_sdata; d_ptr < &_edata; d_ptr++, sptr++){
                *d_ptr = *sptr;
        }

        /* Initialise .bss à 0*/
        for (uint32_t *b_ptr = &_sbss; b_ptr < &_ebss; b_ptr ++){
                *b_ptr = 0;
        }
        main();
}

__attribute__ ((weak)) void SysTick_Handler(void)
{
    s_tick++;
}

__attribute__ ((weak)) void Uart_Handler(void)
{
}

void Default_Handler(void)
{
    while(1){}
}
