#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "tim.h"
#include "Variate.h"

#define ENCODER_TIM_PERIOD  65535   /*计数器最大值*/
#define CNT_INIT 0                  /*计数器初值*/
//#define ROLL_MAX 27
#define PAI 3.141593
#define ENCODER_PER_CM 31200/PAI
#define Max_Angle 180.0
#define FINISH_CNT 10

int32_t read_encoder(TIM_HandleTypeDef *htim);
void 	set_target(PID *pid, int32_t temp_val);
int32_t pwm_val_protect(int32_t pwm_input);
void 	PID_param_init(float* p);
int32_t PID_realize(PID* pid, int32_t actual_val, int32_t pid_err_limit);

#endif


