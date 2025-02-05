#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define PINNO(pin) (pin & 255) // Limit pin value to 8 bits

/*
 * GPIO macro used to declare a struct pointer with the correct memory address
 */
#define GPIO(bank) ((struct gpio *) (0x58020000 + (0x400 * bank)))

/*
 *GPIO enums, used for set and write
 */
enum gpio_banks {A,B,C,D,E,F,G,H,I,J,K};
enum gpio_modes {INPUT, OUTPUT, ALTERNATE, ANALOG};
enum gpio_state {LOW, HIGH};

/*
 *GPIO struct containing all GPIO registers
 */
struct gpio {
    volatile uint32_t GPIO_MODER, GPIO_OTYPER, GPIO_OSPEEDR, GPIO_PUPDR, GPIO_IDR, GPIO_ODR, GPIO_BSRR, GPIO_LCKR, GPIO_AFRL, GPIO_AFRH;
};


/*
 * GPIO Functions
 */
void gpio_set(int pin, uint32_t bank, uint32_t mode);
int gpio_set_af(unsigned int pin, uint32_t bank, uint32_t af_value);
void gpio_write(int pin, uint32_t bank, uint32_t state);
uint16_t gpio_read(int pin, uint32_t bank);

#endif
