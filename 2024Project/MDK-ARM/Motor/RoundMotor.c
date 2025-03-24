#include "RoundMotor.h"


/**
  * @brief  控制直线运动电机转动
  * @param  pwm:控制信号
  *	@note 	
  * @retval 
  */
//1 Round  Motor
void set_motor1_rotate(int32_t pwm)
{
	if(pwm > 0)
	{
		
		TIM3->CCR1 = 0;
		TIM3->CCR2 = pwm;
		
	}
	else if(pwm < 0)
	{
		TIM3->CCR1 = -pwm;
		TIM3->CCR2 = 0;
	}
	else                                                 
	{
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 0;
	}
}

void StartTaskMotor1(void)
{
	if(Start_Flag==1)
	{
		 if(Round_Finish==0) 
		{
			Round_Finish=11;
		}
	}
	else if(Start_Flag==0) 
	{
		Round_Finish=0;
	}
	
	float transmit_angle=0.0;
	
	int transmit5_temp=0;

	flag1=0;
    for(;flag1!=1;)
    {
		set_target(&pid1,RoundEncoder);//为回转电机设定目标角度
		encoder1 = (int32_t) read_encoder(&htim1) + Motor1EncoderOverflowCnt*ENCODER_TIM_PERIOD;
		pwm1 = pwm_val_protect(PID_realize(&pid1, encoder1, pid1_err_limit));/*传入编码器的[总计数值]，实现电机【位置】控制*/
	
		/*【3】PWM控制电机*/
	    set_motor1_rotate(pwm1);
		static int8_t cnt =0;
		static int32_t last = 0;
		if(!flag1)
		{
			if((pid1.err - last)<= 10 && (pid1.err - last)>= -10 && abs(pid1.err)<= pid1_err_limit)//arrive target and keep it
			{
				cnt++;
			}
			else
			{
				cnt=0;
			}
			if(cnt>=FINISH_CNT)
			{
				flag1=1;
				cnt=0;
							}
			last = pid1.err;	//record the last error		
		}
		if(Start_Flag==1) 
		{
			transmit_angle=encoder1*360.0/ENCODERRESOLUTION;
			transmit5_temp=old_angle+(int)transmit_angle;
			if(transmit5_temp>0)
			{
				transmit[5]=transmit5_temp;
			}
			else
			{
				transmit[5]=180+transmit5_temp;
			}
		}
		HAL_Delay(10);
    }
	
	//get out of the for 
	if(Start_Flag==1)
	{
		if(Round_Finish==11) 
		{
			Round_Finish=1;//recover the flag
		}
	}
	
	//RoundEncoder = (float)(Round_Angle / 360.0 * ENCODERRESOLUTION);

	
}
/**
  * @brief  把串口传的指令转成编码器数字
  * @param  无
  *	@note 	无
  * @retval 无
  */
//1 Round  Motor
float AngleToTarget(int Round_Command,int Direct_Command)
{
	if(Direct_Command<0)
	{
		Round_Command=Round_Command-180;
	}
	float encoderValue = (float)(Round_Command / 360.0 * ENCODERRESOLUTION);
	
	return encoderValue;
}

