/**
  ******************************************************************************
  * @file    led.c
  * @brief   This file contains the code for a single LED's
  *          functionality such as ON, OFF, and Toggle.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "led.h"

/* Private defines -----------------------------------------------------------*/
/* GPIO port's registers are 0x400 apart */
#define GPIO_PORT_STRIDE    0x400UL

/* Public functions ----------------------------------------------------------*/
void led_init(const led_t *led)
{
    /* Port number (GPIOA = 0, GPIOB = 1, ...) which is also its RCC enable bit */
    const uint32_t port_index = ((uint32_t)led->port - GPIOA_BASE) / GPIO_PORT_STRIDE;

    /* MODER and PUPDR use 2 bits per pin */
    const uint32_t two_bit_shift = led->pin * 2U;

    /* Enable port clock */
    RCC->AHB2ENR |= (1UL << port_index);
    (void)RCC->AHB2ENR;

    /* Start off so the LED doesn't flash when pin becomes an output */
    led_off(led);

    /* Configure push-pull */
    led->port->OTYPER &= ~(1UL << led->pin);
    led->port->PUPDR  &= ~(3UL << two_bit_shift);

    /* Configure output mode (01). Clear bits first (since pins reset to analog (11)) */
    led->port->MODER &= ~(3UL << two_bit_shift);
    led->port->MODER |=  (1UL << two_bit_shift);
}

void led_on(const led_t *led)
{
    /* BSRR bits 0-15 set a pin high */
    led->port->BSRR = (1UL << led->pin);
}

void led_off(const led_t *led)
{
    /* BSRR bits 16-31 set a pin low */
    led->port->BSRR = (1UL << (led->pin + 16U));
}

void led_toggle(const led_t *led)
{
    /* Read current state from ODR, then change through BSRR */
    if ((led->port->ODR & (1UL << led->pin)) != 0U)
    {
        led_off(led);
    }
    else
    {
        led_on(led);
    }
}
