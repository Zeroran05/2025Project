#include "Motor.h"


/**
  * @brief  读取编码器当前值
  * @param  htim:指针
  *	@note 	
  * @retval 编码器当前值
  */
int32_t read_encoder(TIM_HandleTypeDef *htim)
{
	return htim -> Instance -> CNT;
}
/**
  * @brief  设置目标值
  * @param  val		目标值
  *	@note 	无
  * @retval 无
  */
void set_target(PID *pid, int32_t temp_val)
{ 
	pid -> target_val = temp_val;
}
/**
  * @brief  PWM限幅
  * @param  pwm_input:控制信号
  *	@note 	
  * @retval PWM输出
  */
int32_t pwm_val_protect(int32_t pwm_input)
{
	int32_t pwm_output = 0;
	
	if(pwm_input>10000) 
	{
		pwm_output = 10000;
	}
	else if(pwm_input<-10000) 
	{
		pwm_output = -10000;
	}
	
//	if(pwm_input>7500) 
//	{
//		pwm_output = 7500;
//	}
//	else if(pwm_input<-7500) 
//	{
//		pwm_output = -7500;
//	}
//	
	else
	{
		pwm_output = pwm_input;
	}
	return pwm_output;
}

void PID_param_init(float* p)
{

	/* 初始化参数 */
	pid1.target_val=0;				
	pid1.output_val=0;
	pid1.err=0;
	pid1.err_last=0;
	pid1.integral=0;
	pid1.Kp = p[0];
	pid1.Ki = p[1];
	pid1.Kd = p[2];

	pid2.target_val=0;				
	pid2.output_val=0;
	pid2.err=0;
	pid2.err_last=0;
	pid2.integral=0;
	pid2.Kp = p[3];
	pid2.Ki = p[4];
	pid2.Kd = p[5];
}

/**
  * @brief  PID算法实现
  * @param  actual_val:实际值
  *	@note 	
  * @retval 通过PID计算后的输出
  */
int32_t PID_realize(PID* pid, int32_t actual_val, int32_t pid_err_limit)
{
	/*计算目标值与实际值的误差*/
	pid->err = pid->target_val - actual_val;
	
	if(pid->err <= pid_err_limit && pid->err >= -pid_err_limit)   //偏差在一定范围内就不再进行控制
	{
		pid -> integral = 0;
		return 0;
	}		
	
	
	/*积分项*/
	pid->integral += pid->err;
	
	if(pid->integral > 6000000)
		pid->integral = 6000000;
	else if(pid->integral < -6000000)
		pid->integral = -6000000;

	/*PID算法实现*/
	pid->output_val = pid->Kp * pid->err + 
				      pid->Ki * pid->integral + 
				      pid->Kd * (pid->err - pid->err_last);

	/*误差传递*/
	pid->err_last = pid->err;

	/*返回当前实际值*/
	return pid->output_val;
}

