/**********************************************************************
��		Ҫ: 	STM32f103C8T6 8·�ڰ�Ѱ��С��
***********************************************************************/
#include "stm32f10x.h"
#include "xunji.h"
#include "SysTick.h"
#include "control.h"

int main(void)
{
  TIM3_PWM_Init();   //TIM3��ʱ����ʼ�� ��������������������
	xunji_GPIO_Init();  //Ѱ��ģ���ʼ��
	SysTick_Init();     //ϵͳ�δ�ʱ����ʼ��
	
	Che_front();        //�����������ȫ������   �������������������� ������ʹ�ܶ�����ñ��5�� ��Ĭ�����ã�

  while (1)
  {
		XunjiFlagControl();  //��̬����    ���ƺ������ж���
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
