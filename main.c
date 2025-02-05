#include <stdint.h>
#include <stdio.h>

#include "gpio.h"
#include "rcc.h"
#include "uart.h"
#include "utils.h"
#include "timer.h"
#include "systick.h"
#include "main.h"
#include "err.h"

// TODO: Set AHB + APB1 2 clock prescaler 
// TODO: Set PLL1 prescaler


/* 
 * When no data, transmit isn't high.
 */

int main(void)
{
        systick_enable();

	rcc_uart_init(USART2);
	rcc_uart_init(USART3);
	rcc_uart_init(USART6);
	rcc_uart_init(UART7);
	
        // HSI Clock is used and selected by default        
	enable_pll(PLL1);
	
        rcc_clock_cfgr clk_conf = {
                .system_clock_selection = pll1_ck
        }; 

        if(system_clk(clk_conf)){
                set_error(sys_clk_nok);
        }

        gpio_all_set();

        uart_init_param uart_init_struct = {
                .ua = USART3_A,
                .auto_baud = AUTO_BAUDRATE_DISABLE,
                .baudrate = 9600,
                .TX_enable = TX_ENABLE,
                .RX_enable = RX_ENABLE,
                .oversamp_en = OVERSAMPLING_DISABLE
        };        

        while(uart_init(uart_init_struct)){
                set_error(uart_init_err);
        }
        clear_status();

        while(uart_ready_RXTX(USART3_A)){
                set_error(uart_transmit_err);
        }
        clear_status();
        
        //uint32_t timer, period = 1000;
        //uint8_t on = 0;
        while(1){
                uart_write_buf("hello", sizeof("hello") , USART3_A);       
                //if(timer_expired(&timer, period)){
                //      timed thing
                //        on = ~on;
                //}
        }
}

void gpio_all_set(void)
{

        gpio_set(8, D, ALTERNATE); // UART3 TX
        gpio_set_af(8, E, 7);
        gpio_set(9, D, ALTERNATE); // UART3 RX
        gpio_set_af(7, E, 7);

}
