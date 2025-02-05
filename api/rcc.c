#include "rcc.h"
#include "utils.h"
#include "uart.h"

int rcc_uart_init(int uart)
{
	switch ( uart ){
		case USART1:
			RCC->RCC_APB2ENR |= SHIFT(4);
			break;
		case USART2:
			RCC->RCC_APB1LENR |= SHIFT(17);
			break;	
		case USART3:
			RCC->RCC_APB1LENR |= SHIFT(18);
			break;
		case UART4:
			RCC->RCC_APB1LENR |= SHIFT(19);
			break;	
		case UART5:
			RCC->RCC_APB1LENR |= SHIFT(20);
			break;
		case USART6:
			RCC->RCC_APB2ENR |= SHIFT(6);
			break;	
		case UART7:
			RCC->RCC_APB1LENR |= SHIFT(30);
			break;
		case UART8:
			RCC->RCC_APB1LENR |= SHIFT(31);
			break;	
		default:
			return 1;
			break;
	
	}
	return 0;
}

void enable_pll(int pll)
{
	switch( pll ) {
		case 1:
			RCC->RCC_CR |= SHIFT(24); // PLL1 Enable
			while(!(RCC->RCC_CR & SHIFT(25))){ // Wait until PLL1 Ready
				spin(100);
			}
			break;
		case 2:
			break;
		case 3: 
			break;
		default:
			break;
	}
}

int system_clk(rcc_clock_cfgr config){
        RCC->RCC_CFGR |= config.system_clock_selection;

        if((RCC->RCC_CFGR >> 3) != config.system_clock_selection){
                return 1;
        }else {
                return 0;
        }
}
