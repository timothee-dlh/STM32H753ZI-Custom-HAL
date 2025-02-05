#include "gpio.h"
#include "err.h"

void init_err_led(void){
        gpio_set(0, B, OUTPUT);    
        gpio_set(14, B, OUTPUT); 
        gpio_set(1, E, OUTPUT);
}

void set_error(int err_code){
        init_err_led();
       switch (err_code) {
               case uart_init_err:
                               clear_status();
                               green_on();
                               break;
               case uart_transmit_err:
                               clear_status();
                               yellow_on();
                               break;

               case pll1_not_ready:
                               clear_status();
                               red_on();
                               break;

               case sys_clk_nok:
                               clear_status();
                               green_on();
                               yellow_on();
                               break;

               case uart_transmit:
                               clear_status();
                               green_on();
                               yellow_on();
                               red_on();
                               break;
               default:
                       break;
       } 
}

void clear_status(void){
        gpio_write(0, B, LOW);
        gpio_write(14, B, LOW);
        gpio_write(1, E, LOW);
}

void green_on(void){
        gpio_write(0, B, HIGH);
}

void yellow_on(void){
        gpio_write(1, E, HIGH);
}

void red_on(void){
        gpio_write(14, B, HIGH);
}
