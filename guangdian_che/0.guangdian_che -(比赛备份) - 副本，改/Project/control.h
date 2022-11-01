#ifndef __CONTROL_H
#define __CONTROL_H

#define MOTOR_PWM 390//450
#define jiansuqu 000

#define speed1 190+0//260
#define speed2 240 +0//310
#define speed3 280 +0//360

typedef struct _P_t{
	float P1;
	float P2;
	float P3;
}P_t;

extern short g_fXunjiFlag;
extern short g_fXunjiFlag_te;

extern P_t g_nCar_PID;	

extern int g_nMotor_PWM_Control;

extern unsigned int g_unMotor_PWM_Left;
extern unsigned int g_unMotor_PWM_Right;

void XunjiFlagControl(void);
void AngleControl(void);








#endif

