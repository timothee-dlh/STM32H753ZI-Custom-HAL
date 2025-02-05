#include <stdint.h>
#include <stdbool.h>
#include "uart.h"
#include "utils.h"
#include "err.h"


bool uart_init(uart_init_param param)
{
        
        param.ua->USART_CR1 |= 0; // Disable UART

        if(param.auto_baud) {
                uart_set_auto_baud(param.ua);
        }
        else {
                // Formula for baudrate : BRR = USART_CLOCK / BAUD_RATE
                // Can only be set when UART Disabled, &0xffff to make sure it is 16 bits.
                param.ua->USART_BRR = FREQ / param.baudrate & 0xffff; 
        }
        param.ua->USART_CR1 &= 0xefffefff; // Clear bit M1 and M0 to set word length : 1 start bit, 8 Data bits, n Stop bit
        param.ua->USART_CR2 &= 0xffffcfff; // Set 1 Stop bit

        param.ua->USART_GTPR = 0; // No Prescaler

        if(param.oversamp_en) {
                param.ua->USART_CR1 |= SHIFT(15); // Enable oversampling by 8
        } else {
                param.ua->USART_CR1 &= 0xffff7fff; // Disable oversampling by 8
        }
        param.ua->USART_CR1 |= 1; // Enable UART

        if(param.TX_enable && param.RX_enable) {
                param.ua->USART_CR1 |= SHIFT(2) | SHIFT(3); // Enable TX and RX
        }else if(param.TX_enable) {
                 param.ua->USART_CR1 |= SHIFT(3); // Enable only TX
        }else if(param.RX_enable) {
                 param.ua->USART_CR1 |= SHIFT(2); // Enable only RX
        }else {
                return 1;
        }
        

        return 0;
}

/*
 * Test if RX and TX enable value was taken into account
 */
int uart_ready_RXTX(struct usart *ua)
{
        uint32_t isr_rx_tx_value = ua->USART_ISR & (SHIFT(21) | SHIFT(22)); 
        while(isr_rx_tx_value == (SHIFT(21) | SHIFT(22))) {
                set_error(uart_transmit_err);
        }
        return 0;
}

/*
 * Write byte to uart output
 */
void uart_write_byte(uint8_t val, struct usart *ua)
{
        ua->USART_TDR = val;

        int TC = (ua->USART_ISR & 0b100000) >> 5;
        while (TC) {
                set_error(uart_transmit);
        }
}
/*
 * Write the buffer to uart output using uart_write_byte function
 */
void uart_write_buf(char *buf, int len, struct usart *ua)
{
        int i = 0;
        for(i = 0; i < len; i++) {
                uart_write_byte(buf[i], ua);
        }
}

/*
 * Set UART auto baud rate
 * Verify if correct
 */
void uart_set_auto_baud(struct usart *ua)
{
        ua->USART_CR2 |= SHIFT(20) | (0x0UL << 21) | (0x0UL << 22); // auto baude rate detection
}
