#include "RoundMotor.h"


/**
  * @brief  控制直线运动电机转动
  * @param  pwm:控制信号
  *	@note 	
  * @retval 
  */

void StartTaskMotor1(void)
{
	NewMessage1=false;
//	float transmit_angle=0.0;
//	int transmit5_temp=0;
		set_target(&pid1,RoundEncoder);//为回转电机设定目标角度
		encoder1 = (int32_t) read_encoder(&htim1) + Motor1EncoderOverflowCnt*ENCODER_TIM_PERIOD;
		pwm1 = pwm_val_protect(PID_realize(&pid1, encoder1, pid1_err_limit));/*传入编码器的[总计数值]，实现电机【位置】控制*/
	
		/*【3】PWM控制电机*/
	    set_motor1_rotate(pwm1);
//		static int8_t cnt =0;
//		static int32_t last = 0;
//		if(!flag1)
//		{
//			if((pid1.err - last)<= 10 && (pid1.err - last)>= -10 && abs(pid1.err)<= pid1_err_limit)
//			{
//				cnt++;
//			}
//			else
//			{
//				cnt=0;
//			}
//			if(cnt>=FINISH_CNT)
//			{
//				flag1=1;
//				cnt=0;
//							}
//			last = pid1.err;			
//		}
		while(!Check_RoundMotor_Position())
			Transmit_Motor1_Position();
			Transmit_Motor1_Position();
//		if(Start_Flag==1) 
//		{
//			transmit_angle=encoder1*360.0/ENCODERRESOLUTION;
//			transmit5_temp=old_angle+(int)transmit_angle;//roundmotor's encoder will reset to zero everytime,so the old angle must be added
//			if(transmit5_temp>0)
//			{
//				transmit[5]=transmit5_temp;
//			}
//			else
//			{
//				transmit[5]=180+transmit5_temp;
//			}
//		}
		HAL_Delay(10);
    
		if(Start_Flag==1 && NewMessage1==false)
	{
			Round_Finish=1;
	}
}
	
	//RoundEncoder = (float)(Round_Angle / 360.0 * ENCODERRESOLUTION);
/**
  * @brief  把串口传的指令转成编码器数字
  * @param  无
  *	@note 	无
  * @retval 无
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

bool Check_RoundMotor_Position(void)
{
	static int cnt=0;
	static int last=0;
	bool judge=false;
	if((pid1.err - last)<= 10 && (pid1.err - last)>= -10 && abs(pid1.err)<= pid1_err_limit)
			{
				cnt++;
			}
			else
			{
				cnt=0;
			}
			last = pid1.err;
			if(cnt>=FINISH_CNT)
			{
				judge=true;
				cnt=0;
				last=0;
			}
				return judge;
}

void Transmit_Motor1_Position(void)
{
	if(Start_Flag==1) 
		{
			float transmit_angle=0.0;
			int transmit5_temp=0;
			transmit_angle=encoder1*360.0/ENCODERRESOLUTION;
			transmit5_temp=old_angle+(int)transmit_angle;//roundmotor's encoder will reset to zero everytime,so the old angle must be added
			if(transmit5_temp>0)
			{
				transmit[5]=transmit5_temp;
			}
			else
			{
				transmit[5]=180+transmit5_temp;
			}
		}
}
