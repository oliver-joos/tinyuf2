/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Ha Thach for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef BOARD_H_
#define BOARD_H_

//--------------------------------------------------------------------+
// LED
//--------------------------------------------------------------------+

#define LED_PORT              GPIOB
#define LED_PIN               GPIO_PIN_7    // blue LED
#define LED_STATE_ON          0

//--------------------------------------------------------------------+
// Neopixel
//--------------------------------------------------------------------+

//// Number of neopixels
#define NEOPIXEL_NUMBER       0

//#define NEOPIXEL_PORT         GPIOC
//#define NEOPIXEL_PIN          GPIO_PIN_0
//
//// Brightness percentage from 1 to 255
//#define NEOPIXEL_BRIGHTNESS   0x10


//--------------------------------------------------------------------+
// Flash
//--------------------------------------------------------------------+

// Flash size of the board
#define BOARD_FLASH_SIZE      (1024 * 1024)

//--------------------------------------------------------------------+
// USB UF2
//--------------------------------------------------------------------+

#define USB_VID           0x239A
#define USB_PID           0x0055
#define USB_MANUFACTURER  "Adafruit"
#define USB_PRODUCT       "UF2 Bootloader"

#define UF2_PRODUCT_NAME  USB_MANUFACTURER " " USB_PRODUCT
#ifndef UF2_BOARD_ID
#define UF2_BOARD_ID      "Nucleo-F412"
#endif
#define UF2_VOLUME_LABEL  "STMF412BOOT"        // max. 11 characters!
#define UF2_INDEX_URL     "https://github.com/oliver-joos/tinyuf2"

#define USB_NO_VBUS_PIN   1

//--------------------------------------------------------------------+
// UART
//--------------------------------------------------------------------+

#define UART_DEV              USART3
#define UART_CLOCK_ENABLE     __HAL_RCC_USART3_CLK_ENABLE
#define UART_CLOCK_DISABLE    __HAL_RCC_USART3_CLK_DISABLE
#define UART_GPIO_PORT        GPIOD
#define UART_GPIO_AF          GPIO_AF7_USART3
#define UART_TX_PIN           GPIO_PIN_8
#define UART_RX_PIN           GPIO_PIN_9

//--------------------------------------------------------------------+
// RCC Clock
//--------------------------------------------------------------------+
static inline void clock_init(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = HSE_VALUE / 1000000;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;       // DIV4 => SYSCLK 48MHz
  RCC_OscInitStruct.PLL.PLLQ = 4;                   // 4 => USB clock 48MHz
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);  // <64MHz:1 <84MHz:2 else 3
}

#endif
