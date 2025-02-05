#include "gpio.h"
#include "rcc.h"

void gpio_set(int pin, uint32_t bank, uint32_t mode)
{
        /*
         * Set GPIO MODE using GPIO MODER Registers.
         */
        struct gpio *gpio = GPIO(bank);
        RCC->RCC_AHB4ENR |= 1U << bank;
        gpio->GPIO_MODER &= ~(3U << (PINNO(pin)*2));
        gpio->GPIO_MODER |= (mode << (PINNO(pin)*2));
}

int gpio_set_af(unsigned int pin, uint32_t bank, uint32_t af_value)
{

        struct gpio *gpio = GPIO(bank);

        if(pin > 15) {
                return 1;
        }

        if( pin >= 8 ) {
                gpio->GPIO_AFRH &= ~(15UL << (pin * 4));
                gpio->GPIO_AFRH |= (af_value << (pin * 4));
                return 0;
        }
        else {
                gpio->GPIO_AFRL &= ~(15UL << (pin * 4));
                gpio->GPIO_AFRL |= (af_value << (pin * 4));
                return 0;
        }
}

/*
 *Set GPIO Output using BSRR Registers
 */

void gpio_write(int pin, uint32_t bank, uint32_t state)
{
        struct gpio *gpio = GPIO(bank);
        gpio->GPIO_BSRR = (1U << PINNO(pin)) << (state ? 0 : 16);
}

// Function to test
uint16_t gpio_read(int pin, uint32_t bank)
{
        struct gpio *gpio = GPIO(bank);
        uint32_t mask = (1U << PINNO(pin)) & 0xffff;
        return (gpio->GPIO_IDR & mask) & 0xffff;
}
