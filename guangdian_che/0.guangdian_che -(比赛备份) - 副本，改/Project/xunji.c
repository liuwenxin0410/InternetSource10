/**********************************************************************
概		要: 	电机pwm驱动
***********************************************************************/
#include "stm32f10x.h"

void Car_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);		  

	
	GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4);
	GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
}

/*
 * 函数名：TIM3_GPIO_Init
 * 描述  ：配置TIM3复用输出PWM时用到的I/O
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void TIM3_GPIO_Init(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
 * 函数名：TIM3_Mode_Config
 * 描述  ：配置TIM3输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void TIM3_Mode_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM信号电平跳变值 */
	u16 CCR1_Val = 0;        
	u16 CCR2_Val = 0;
	u16 CCR3_Val = 0;
	u16 CCR4_Val = 0;
	//u16 PrescalerValue;
/* -----------------------------------------------------------------------
    TIM2 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM3CLK = 72 MHz, Prescaler = 0x0, TIM3 counter clock = 72 MHz
    TIM3 ARR Register = 71999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
    TIM3 Frequency = 1 KHz.
		CC1 update rate = TIM2 counter clock / CCR1_Val
    TIM3 Channelx duty cycle = (TIM2_CCRx/ TIM2_ARR)* 100 = x%
    
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //当定时器从0计数到999，即为1000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 3;	    //设置预分频：不预分频，即为72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM2 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平


  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	  //使能通道1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  //使能通道3
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;   
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //使能通道3
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

   TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	  //
   TIM_OC4Init(TIM3, &TIM_OCInitStructure);	  //使能通道4
   TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);


  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // 使能TIM3重载寄存器ARR

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //使能定时器3	
}

void TIM3_PWM_Init(void)
{
	Car_GPIO_Init();
	TIM3_GPIO_Init();
	TIM3_Mode_Init();	
}



void Che_front(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4 );				    
	GPIO_ResetBits(GPIOA, GPIO_Pin_3 );
	
  GPIO_ResetBits(GPIOB, GPIO_Pin_1 );				    
	GPIO_ResetBits(GPIOB, GPIO_Pin_0 );
}


/*
 * 函数名：xunji_GPIO_Init
 * 描述  ：初始化寻迹模块
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void xunji_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15|   
	                              GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_12 | GPIO_Pin_12|
                                GPIO_Pin_8  | GPIO_Pin_9  ;	//8 9 无用
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;     //上拉输入 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}	











