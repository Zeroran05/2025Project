#ifndef __ROUNDMOTOR_H__
#define __ROUNDMOTOR_H__

#include "Motor.h"
#include "math.h"
#include "stdlib.h"


#define ENCODERRESOLUTION  425400


//1 Round  Motor
void set_motor1_rotate(int32_t pwm);
void StartTaskMotor1(void);
float AngleToTarget(int Round_Command,int Direct_Command);

#endif
