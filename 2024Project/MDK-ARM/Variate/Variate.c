#include "Variate.h"

PID pid1;
PID pid2;
float initial_pid_val[6] = {7, 0.005, 70, 7.2, 0.0003, 100};

int32_t pwm1 = 0;
uint8_t flag1=0;//回转电机标志位，指1表示运动到指定位置
int32_t encoder1 = 0;//回转电机编码器
int32_t pid1_err_limit = 1000;//1200=1degree 控制误差判断，在误差范围内就不再进行控制，根据实际需要调整
int16_t Motor1EncoderOverflowCnt = 0;//控制回转运动电机编码器溢出
float RoundEncoder =0.0;
int Round_Finish=0;

int32_t pwm2 = 0;
uint8_t flag2=0;//直线电机标志位，指1表示运动到指定位置
int32_t encoder2 = 0;//电机编码器
int32_t pid2_err_limit = 1000;//366=1degree 控制误差判断，在误差范围内就不再进行控制，根据实际需要调整
int16_t Motor2EncoderOverflowCnt = 0;//控制直线运动电机编码器溢出
int Linear_Finish=0;


uint8_t transmit[8]={0x53,0x5A,0x48,0x59,0xFF,0x00,0x20,0x1A};
							 //0x53 0x5A 0x48 0x59 Command round linear check_sum
uint8_t Command[LENGTH]={0};
uint8_t RxFlag = 0;
unsigned int Find_Flag=0; 
uint8_t Mode_Command;				//Command[4]
uint8_t Round_Command;				//Command[5]
uint8_t Linear_Command;				//Command[6]
uint8_t Check_Sum;					//Command[7]
int8_t Linear_IntCommand;
double Linear_length=ROLL_MAX;

int Round_Angle=0;	
int direct;//回转电机符号位
int Start_Flag=0;

int old_angle=0;
int old_length=0;



