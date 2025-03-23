#ifndef _VARIATE_H_
#define _VARIATE_H_

#include "tim.h"
#include "stdbool.h"
#include "freertos.h"
#include "semphr.h"

#define LENGTH 100
#define ROLL_MAX 33

typedef struct 
{
	int32_t target_val;   //目标值
	int32_t err;          //偏差值
	int32_t err_last;     //上一个偏差值
	float Kp,Ki,Kd;     //比例、积分、微分系数
	int32_t integral;     //积分值
	int32_t output_val;   //输出值
}PID;



extern float initial_pid_val[6];
extern int16_t Motor1EncoderOverflowCnt ;      
extern int16_t Motor2EncoderOverflowCnt ;	
extern PID pid1;
extern PID pid2;
extern int32_t pid1_err_limit;
extern int32_t pid2_err_limit;
extern int32_t pwm1;
extern int32_t pwm2;
extern int32_t encoder1;
extern int32_t encoder2;


extern int Start_Flag;


extern uint8_t Command[LENGTH];
extern uint8_t Check_Sum;		
extern uint8_t Mode_Command;			//Command[4]
extern uint8_t Round_Command;			//Command[5]
extern uint8_t Linear_Command;			//Command[6]
extern uint8_t transmit[8];
extern unsigned int Find_Flag;
extern int8_t Linear_IntCommand;


extern int Round_Angle;	
extern double Linear_length;
extern int old_angle;
extern int old_length;


extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;


extern float RoundEncoder ;
extern float LinearEncoder ;

extern bool NewMessage1;
extern bool NewMessage2;

extern SemaphoreHandle_t RxFlag;
extern SemaphoreHandle_t Round_Finish;
extern SemaphoreHandle_t Linear_Finish;

#endif 
