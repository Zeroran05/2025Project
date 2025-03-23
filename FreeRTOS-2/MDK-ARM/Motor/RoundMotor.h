#ifndef __ROUNDMOTOR_H__
#define __ROUNDMOTOR_H__

#include "Motor.h"
#include "math.h"
#include "stdlib.h"
#include "stdbool.h"


#define ENCODERRESOLUTION  425400//??


//1 Round  Motor
void set_motor1_rotate(int32_t pwm);
void StartTaskMotor1(void);
bool Check_RoundMotor_Position(void);
void Transmit_Motor1_Position(void);
int Translate_RoundMotor_Target(int Round_Angle);

#endif
