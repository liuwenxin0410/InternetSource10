/**********************************************************************
概		要: 	STM32f103C8T6 8路黑白寻迹小车
***********************************************************************/
#include "stm32f10x.h"
#include "xunji.h"
#include "SysTick.h"
#include "control.h"

int main(void)
{
  TIM3_PWM_Init();   //TIM3定时器初始化 其中两个接驱动正引脚
	xunji_GPIO_Init();  //寻迹模块初始化
	SysTick_Init();     //系统滴答定时器初始化
	
	Che_front();        //电机驱动引脚全部置零   其中两个接驱动负引脚 （驱动使能端跳线帽接5伏 即默认设置）

  while (1)
  {
		XunjiFlagControl();  //姿态函数    控制函数在中断里
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
