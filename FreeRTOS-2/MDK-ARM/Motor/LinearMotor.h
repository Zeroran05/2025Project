#ifndef __LINEARMOTOR_H__
#define __LINEARMOTOR_H__

#include "Motor.h"
#include "math.h"
#include "stdlib.h"

void set_motor2_rotate(int32_t pwm);
void StartTaskMotor2(void);
void LinearMotorInit(void);
int Translate_LinearMotor_Target(double direct);
bool Check_LinearMotor_Position(void);
void Transmit_Motor2_Position(void);

#endif
