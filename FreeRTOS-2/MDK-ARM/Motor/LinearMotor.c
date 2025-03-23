#include "LinearMotor.h"


void StartTaskMotor2(void)
{
	NewMessage2=0;
	do
	{
		LinearEncoder = Translate_LinearMotor_Target(Linear_length);
		set_target(&pid2,LinearEncoder);
		encoder2= (int32_t) (read_encoder(&htim5) + Motor2EncoderOverflowCnt*ENCODER_TIM_PERIOD);/*获取当前的累计值*/
		pwm2 = pwm_val_protect(PID_realize(&pid2, encoder2, pid2_err_limit));/*传入编码器的[总计数值]，实现电机【位置】控制*/
		set_motor2_rotate(pwm2);/*PWM控制电机*/
		Transmit_Motor2_Position();
		HAL_Delay(5);//每5ms更新一次
    }while(!Check_LinearMotor_Position());
	
		if(Start_Flag==1 && NewMessage2==false)
	{
		xSemaphoreGive(Linear_Finish);
	}
}

int Translate_LinearMotor_Target(double Linear_length)
{
	int target_encoder;
	target_encoder= (int)(ROLL_MAX -fabs(Linear_length))*ENCODER_PER_CM;
	return target_encoder;
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

bool Check_LinearMotor_Position(void)
{
	static int cnt=0;
	static int last=0;
	bool judge=false;
	if((pid2.err - last)<= 10 && (pid2.err - last)>= -10 && abs(pid2.err)<= pid2_err_limit)
			{
				cnt++;
			}
			else
			{
				cnt=0;
			}
			last = pid2.err;
			if(cnt>=FINISH_CNT)
			{
				judge=true;
				cnt=0;
				last=0;
			}
			return judge;
}

void Transmit_Motor2_Position(void)
{
	float transmit_lenth=0.0;
	transmit_lenth=(int)(ROLL_MAX-encoder2)/ENCODER_PER_CM;
	transmit[6]=transmit_lenth;
}