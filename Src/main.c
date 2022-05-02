/**
 * @file main.c
 *
 * @brief
 *
 * @author monoliths (monoliths-uni@outlook.com)
 * @version 1.0
 * @date 2022-05-02
 *
 * *********************************************************************************
 *
 * @note version: 1.0
 *
 *
 * @description:
 *
 * *********************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include <stdio.h>

/** @addtogroup STM32F10x_StdPeriph_Template
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{

    GPIO_InitTypeDef gpio;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    // RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD, ENABLE);
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &gpio);

    // -----> TIM

    TIM_TimeBaseInitTypeDef tim3;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    // (7199 + 1) * (9999 + 1)/72 = 1000000us = 1000ms
    tim3.TIM_Prescaler = 7199;
    tim3.TIM_CounterMode = TIM_CounterMode_Up;
    tim3.TIM_Period = 9999;
    tim3.TIM_RepetitionCounter = 0;
    tim3.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM3, &tim3);

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM3, ENABLE);

    // -----> NVIC

    NVIC_InitTypeDef nvicTIM3;
    nvicTIM3.NVIC_IRQChannel = TIM3_IRQn;
    nvicTIM3.NVIC_IRQChannelCmd = ENABLE;
    nvicTIM3.NVIC_IRQChannelPreemptionPriority = 3;
    nvicTIM3.NVIC_IRQChannelSubPriority = 0;

    NVIC_Init(&nvicTIM3);


    /* Infinite loop */
    while (1)
    {
    }
}

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    // USART_SendData(, (uint8_t) ch);

    /* Loop until the end of transmission */
    // while (USART_GetFlagStatus(, USART_FLAG_TC) == RESET)
    // {}

    return ch;
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line
       number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line)
     */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
 * @}
 */
