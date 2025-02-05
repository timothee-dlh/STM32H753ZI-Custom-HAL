#include <stdbool.h>

#ifndef UART_H
#define UART_H

#define AUTO_BAUDRATE_ENABLE 1
#define AUTO_BAUDRATE_DISABLE 0

#define TX_ENABLE 1
#define TX_DISABLE 0
#define RX_ENABLE 1
#define RX_DISABLE 0

#define OVERSAMPLING_DISABLE 0
#define OVERSAMPLING_ENABLE 1 

/*
 * USART define used to access USART registers trough USART struct
 */
#define USART2_A ((struct usart *) 0x40004400)
#define USART3_A ((struct usart *) 0x40004800)
#define USART6_A ((struct usart *) 0x40011400)
#define UART7_A ((struct usart *) 0x40007800)
#define UART8_A ((struct usart *) 0x40007C00)

enum uart_id {USART1, USART2, USART3, UART4, UART5, USART6, UART7, UART8};

/*
 * USART struct containing all usart registers
 */
struct usart {
    volatile uint32_t USART_CR1, USART_CR2, USART_CR3, USART_BRR, USART_GTPR, USART_RQR, USART_ISR, USART_ICR, USART_RDR, USART_TDR, USART_PRESC;
};

typedef struct uart_init_param {
    struct usart *ua;      // Pointer to USART structure
    bool auto_baud;         // Enables automatic baud rate detection
    uint16_t baudrate;     // Baud rate setting
    bool TX_enable;         // Enables transmission
    bool RX_enable;         // Enables reception
    bool oversamp_en;       // Enables oversampling
} uart_init_param;

/*
 * UART Functions
 */
void uart_write_byte(uint8_t val, struct usart *ua);
void uart_write_buf(char *buf, int len, struct usart *ua);
void uart_set_auto_baud(struct usart *ua);
int uart_ready_RXTX(struct usart *ua);
bool uart_init(uart_init_param param);

#endif
