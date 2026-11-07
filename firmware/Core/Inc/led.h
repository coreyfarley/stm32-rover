/**
  ******************************************************************************
  * @file    led.h
  * @brief   Register-level GPIO LED driver for STM32L4.
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LED_H
#define LED_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32l4xx.h"

/** GPIO port/pin pair for a single LED */
typedef struct
{
    GPIO_TypeDef    *port;
    uint8_t         pin;
} led_t;

/* Exported functions prototypes ---------------------------------------------*/
void led_init(const led_t *led);    // Enables the port clock & sets pin to push-pull output.
void led_on(const led_t *led);
void led_off(const led_t *led);
void led_toggle(const led_t *led);

#endif /* LED_H */
