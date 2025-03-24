#ifndef __LINEARMOTOR_H__
#define __LINEARMOTOR_H__

#include "Motor.h"
#include "math.h"
#include "stdlib.h"

void set_motor2_rotate(int32_t pwm);
void StartTaskMotor2(double direct);
void LinearMotorInit(void);
int Calculate_Target(double direct);
int Calculate_Length(void);


#endif
