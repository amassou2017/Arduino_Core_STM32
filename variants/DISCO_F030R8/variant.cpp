/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
 //P1 connector Right side (bottom view)
  PC_13,  //D0
  PC_14,  //D1
  PC_15, //D2
  PF_0,  //D3 
  PF_1,  //D4
  PC_0,  //D5
  PC_1, //D6 
  PC_2,  //D7
  PC_3,  //D8
  PA_0,  //D9
  PA_1,  //D10
  PA_2,  //D11
  PA_3,  //D12
  PF_4,  //D13
  PF_5,  //D14
  PA_4,  //D15
  PA_5, //D16
  PA_6, //D17
  PA_7,  //D18
  PC_4,  //D19
  PC_5, //D20 
  PB_0, //D21 
  PB_1, //D22
  PB_2,  //D23
  PB_10, //D24
  PB_11, //D25
  PB_12, //D26
  //P2 connector Left side (bottom view)
  PB_9,  //D27
  PB_8,  //D28
  PB_7,  //D29
  PB_6,  //D30
  PB_5, //D31
  PB_4,  //D32
  PB_3,  //D33
  PD_2,  //D34
  PC_12,  //D35
  PC_11,  //D36
  PC_10, //D37
  PA_15, //D38
  PA_14, //D39
  PF_7, //D40
  PF_6,  //D41
  PA_13,  //D42
  PA_12, //D43
  PA_11, //D44
  PA_10, //D45
  PA_9,  //D46
  PA_8,  //D47
  PC_9,  //D48
  PC_8,  //D49
  PC_7,  //D50
  PC_6,  //D51
  PB_15,  //D52
  PB_14,  //D53
  PB_13,  //D54
  // Duplicated pins in order to be aligned with PinMap_ADC
  PC_0,  //D55/A0 = D5
  PC_1,  //D56/A1 = D6
  PC_2,  //D57/A2 = D7
  PC_3,  //D58/A3 = D8
  PA_0,  //D59/A4 = D9
  PA_1,  //D60/A5 = D10
  PA_2,  //D61/A6 = D11
  PA_3,  //D62/A7 = D12
  PA_4,  //D63/A8 = D15
  PA_5,  //D64/A9 = D16
  PA_6,  //D65/A10= D17
  PA_7,  //D66/A11= D18
  PC_4, //D67/A12 = D19
  PC_5, //D68/A13 = D20
  PB_0, //D69/A14 = D21
  PB_1  //D70/A15 = D22
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI/2)
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 8000000
  *            PREDIV                         = 1
  *            PLLMUL                         = 12
  *            Flash Latency(WS)              = 1
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* No HSE Oscillator on Nucleo, Activate PLL with HSI/2 as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 15;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
