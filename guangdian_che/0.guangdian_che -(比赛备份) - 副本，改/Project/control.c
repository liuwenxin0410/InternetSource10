#include "stm32f10x.h"
#include "control.h"
#include "xunji.h"

short g_fXunjiFlag;
short g_fXunjiFlag_te;

int g_nMotor_PWM_Control;

unsigned int g_unMotor_PWM_Left;
unsigned int g_unMotor_PWM_Right;

void delay_nms(u16 time)
{
	u16 i=0;
	while(time--)
	{
		i=12;
		while(i--);
	}
}

/*
 * 函数名：XunjiFlagControl
 * 描述  ：姿态管理
 * 输入  ：寻迹信号 XY等皆为传感器的数字信号
 * 输出  ：姿态
 * 调用  ：内部调用
 */
void XunjiFlagControl(void)
{
/*********************正常情况**************************************/
	
	if(X1==1 | Y1==1)// 线中
	{
		 delay_nms(5);//用延时过滤掉意外情况，
		
			if(X1==1 | Y1==1)
	  {
		  g_fXunjiFlag=0;
	  }
	}

/**********************左触***************************************/	
	
	if(X2==1)// 0010 0000
	{
		 delay_nms(5);
		
			if(X2==1)
	  {
		  g_fXunjiFlag=-1;
		}
	}
	if(X3==1)// 0100 0000
	{
		 delay_nms(5);
		
			if(X3==1)
	  {
		  g_fXunjiFlag=-2;
		}
	}		
	if(X4==1)// 1000 0000
	{
		 delay_nms(5);
		
		if(X4==1)
	 {
		  g_fXunjiFlag=-3;
	 }
	}	
/****************右触*********************************/
	if(Y2==1)// 0000 0100
	{
		 delay_nms(5);

		if(Y2==1)
	  {
		  g_fXunjiFlag=1;
		}
	}	

	if(Y3==1)// 0000 0010
	{
		 delay_nms(5);
		
			if(Y3==1)
	 {
		  g_fXunjiFlag=2;
	 }
	}		
	if(Y4==1)// 0000 0001
	{
		 delay_nms(5);
		
			if(Y4==1)
	 {
		  g_fXunjiFlag=3;
	 }
	}	 
}	

void AngleControl(void)	
{
	 if(g_fXunjiFlag==0)
	 {	 
	  g_nMotor_PWM_Control= 0 ;
	 }
	 	 else if(g_fXunjiFlag==1|g_fXunjiFlag==-1)
	 {		 
	    if(g_fXunjiFlag>0)
			                   g_nMotor_PWM_Control=  speed1;
			else
				                 g_nMotor_PWM_Control= -speed1;
	 }	 else if(g_fXunjiFlag==2|g_fXunjiFlag==-2)
	 {	 
	    if(g_fXunjiFlag>0)
			                   g_nMotor_PWM_Control=  speed2;
			else
				                 g_nMotor_PWM_Control= -speed2;
	 }
	 else if(g_fXunjiFlag==3|g_fXunjiFlag==-3)
	 {	 
	    if(g_fXunjiFlag>0)
			                   g_nMotor_PWM_Control=  speed3;
			else
				                 g_nMotor_PWM_Control= -speed3;
	 }

   if(Z1==1 | Z2==1)
   {
   }
   else
   {		 
	 g_unMotor_PWM_Left =	g_unMotor_PWM_Left - jiansuqu;
	 g_unMotor_PWM_Right= g_unMotor_PWM_Right- jiansuqu;
   } 
	
	 g_unMotor_PWM_Left = MOTOR_PWM - g_nMotor_PWM_Control;
	 g_unMotor_PWM_Right= MOTOR_PWM + g_nMotor_PWM_Control;
	 


/*******************PWM上下限****************/	
	if(g_unMotor_PWM_Left >MOTOR_PWM) g_unMotor_PWM_Left =MOTOR_PWM;
	if(g_unMotor_PWM_Right>MOTOR_PWM) g_unMotor_PWM_Right=MOTOR_PWM;	
	 
	if(g_unMotor_PWM_Left < 10      ) g_unMotor_PWM_Left = 10 ;
	if(g_unMotor_PWM_Right< 10      ) g_unMotor_PWM_Right= 10 ;	
	
		TIM_SetCompare1(TIM3,g_unMotor_PWM_Left);
		TIM_SetCompare2(TIM3,g_unMotor_PWM_Right);
}	










