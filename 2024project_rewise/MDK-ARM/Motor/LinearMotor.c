#include "LinearMotor.h"

void set_motor2_rotate(int32_t pwm)
{
	if(pwm > 0)
	{
		TIM3->CCR3 = pwm;
		TIM3->CCR4 = 0;
	}
	else if(pwm < 0)
	{
		TIM3->CCR3 = 0;
		TIM3->CCR4 = -pwm;
	}
	else                                                  //刹车
	{
		
		TIM3->CCR3 = 0;
		TIM3->CCR4 = 0;
	}
}
void StartTaskMotor2(double direct)
{
	if(Start_Flag==1)
	{		
		if(Linear_Finish==0) 
		{
			Linear_Finish=11;
		}
	}
	else if(Start_Flag==0)	Linear_Finish=0;
	
    int target = Calculate_Target(direct);
		flag2=0;
    for(;flag2!=1;)
    {
		set_target(&pid2,target);
		encoder2= (int32_t) (read_encoder(&htim5) + Motor2EncoderOverflowCnt*ENCODER_TIM_PERIOD);/*获取当前的累计值*/
		pwm2 = pwm_val_protect(PID_realize(&pid2, encoder2, pid2_err_limit));/*传入编码器的[总计数值]，实现电机【位置】控制*/
		set_motor2_rotate(pwm2);/*PWM控制电机*/
		static uint8_t cnt = 0;
		static int32_t last = 0;
		if(!flag2)
		{
			if((pid2.err - last)<= 10 && (pid2.err - last)>= -10 && abs(pid2.err )<= 1000)
			{
					cnt++;
			}
			else
			{
				cnt=0;
			}
			if(cnt>=FINISH_CNT)
			{
				flag2=1;
				cnt=0;				
			}
			last = pid2.err;			
		}
		
		HAL_Delay(5);//每5ms更新一次
    }
	if(Start_Flag==1)
	{
		 if(Linear_Finish==11) 
		{
			Linear_Finish=1;
		}
	}
}

int Calculate_Target(double direct)
{
	int target_encoder;
	target_encoder= (int)(ROLL_MAX -fabs(direct))*ENCODER_PER_CM;
	return target_encoder;
}
int Calculate_Length(void)
{
	int current_Length;
	current_Length = ROLL_MAX - encoder2*PAI/33000;
	return current_Length;
}
void LinearMotorInit(void)
{
	TIM3->CCR3=0;
	TIM3->CCR4=10000;
	HAL_Delay(200);
	TIM3->CCR3=0;
	TIM3->CCR4=5000;
	HAL_Delay(3000);
	TIM3->CCR4=0;
	
	Motor2EncoderOverflowCnt=0;
	Motor2EncoderOverflowCnt=0;
	TIM5 -> CNT=0;
	TIM1 -> CNT=0;
	Linear_length=ROLL_MAX;
	
	transmit[4]=0xFF;
	transmit[5]=0x00;
	transmit[6]=0x20;
	transmit[7]=transmit[4]+transmit[5]+transmit[6];
}
