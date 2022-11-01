#ifndef __CHE_H
#define __CHE_H

#define X4 GPIO_ReadInputDataBit( GPIOB , GPIO_Pin_12 )
#define X3 GPIO_ReadInputDataBit( GPIOB , GPIO_Pin_13 )
#define X2 GPIO_ReadInputDataBit( GPIOB , GPIO_Pin_14 )
#define X1 GPIO_ReadInputDataBit( GPIOB , GPIO_Pin_15 )

#define Y1 GPIO_ReadInputDataBit( GPIOB , GPIO_Pin_4  )
#define Y2 GPIO_ReadInputDataBit( GPIOB , GPIO_Pin_5  )
#define Y3 GPIO_ReadInputDataBit( GPIOB , GPIO_Pin_6  )
#define Y4 GPIO_ReadInputDataBit( GPIOB , GPIO_Pin_7  )

#define Z1 GPIO_ReadInputDataBit( GPIOB , GPIO_Pin_8  )
#define Z2 GPIO_ReadInputDataBit( GPIOB , GPIO_Pin_9  )

void Car_GPIO_Init(void);
void TIM3_GPIO_Init(void);
void TIM3_Mode_Init(void);

void TIM3_PWM_Init(void);

void xunji_GPIO_Init(void);

void Che_front(void);

#endif
