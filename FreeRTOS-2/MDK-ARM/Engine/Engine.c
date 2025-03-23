#include "Engine.h"
#include "LinearMotor.h"


void motor_init(void)
{
	//直线电机TIM3->CCR3 4
//	LinearMotorInit();
//	TIM3->CCR3=0;
//	TIM3->CCR4=4000;
//	HAL_Delay(2500);
//	TIM3->CCR4=0;
//	Motor2EncoderOverflowCnt=0;
//	TIM5 -> CNT=0;
//	TIM1 -> CNT=0;
	motor_move();
	LinearMotorInit();
//	Motor2EncoderOverflowCnt=0;
//	TIM5 -> CNT=0;
//	TIM1 -> CNT=0;
}
void motor_move(void)
{
	//TIM4->CCR3 4
	TIM4->CCR3=GRIPPER_INITIAL_CLAW1;
	TIM4->CCR4=GRIPPER_INITIAL_CLAW2;
	//TIM4->CCR1 2
	TIM4->CCR1=INITIAL1;//舵机收缩，夹子夹紧
	TIM4->CCR2=INITIAL2;//舵机收缩，夹子夹紧
	HAL_Delay(500);
	//TIM4->CCR3 4
	TIM4->CCR3=GRAB_CUBE_CLAW1;
	TIM4->CCR4=GRAB_CUBE_CLAW2;
	//TIM4->CCR1 2
	TIM4->CCR1=RESET1;//舵机收缩，夹子夹紧
	TIM4->CCR2=RESET2;//舵机收缩，夹子夹紧
	HAL_Delay(1000);
	//TIM4->CCR3 4
	TIM4->CCR3=GRIPPER_INITIAL_CLAW1;
	TIM4->CCR4=GRIPPER_INITIAL_CLAW2;
	//TIM4->CCR1 2
	TIM4->CCR1=INITIAL1;//舵机收缩，夹子夹紧
	TIM4->CCR2=INITIAL2;//舵机收缩，夹子夹紧
}
void motor_grab_cube(void)
{
	//舵机爪
	TIM4->CCR3=GRAB_CUBE_CLAW1_INITIAL;
	TIM4->CCR4=GRAB_CUBE_CLAW2_INITIAL;
	HAL_Delay(300);
	//舵机
	 TIM4->CCR1=CUBE1;
	 TIM4->CCR2=CUBE2;
	 HAL_Delay(300);
	//舵机爪
	TIM4->CCR3=GRAB_CUBE_CLAW1;
	TIM4->CCR4=GRAB_CUBE_CLAW2;
		HAL_Delay(400);
	//舵机
	 TIM4->CCR1=INITIAL1;//舵机回收复位
	 TIM4->CCR2=INITIAL2;
	HAL_Delay(1000);
}
void motor_grab_ball(void)
{
	//舵机爪
	TIM4->CCR3=GRAB_BALL_CLAW1_INITIAL;
	TIM4->CCR4=GRAB_BALL_CLAW2_INITIAL;
	HAL_Delay(300);
	//舵机
	TIM4->CCR1=BALL1; 
	TIM4->CCR2=BALL2;
  HAL_Delay(300);
	//舵机爪
	TIM4->CCR3=GRAB_BALL_CLAW1;
	TIM4->CCR4=GRAB_BALL_CLAW2;
	 HAL_Delay(400);
	//舵机
	 TIM4->CCR1=INITIAL1;//舵机回收复位
	 TIM4->CCR2=INITIAL2;
		HAL_Delay(1000);
}
void motor_put_cube(void)
{
//	//舵机
//	TIM4->CCR1=PUT_CUBE1; 
//	TIM4->CCR2=PUT_CUBE2;
//  HAL_Delay(400);
	//舵机爪
	TIM4->CCR3=PUT_CUBE_CLAW1;
	TIM4->CCR4=PUT_CUBE_CLAW2;
//  HAL_Delay(400);
//	//舵机
//	 TIM4->CCR1=INITIAL1;//舵机回收复位
//	 TIM4->CCR2=INITIAL2;
//	HAL_Delay(400);
}
void motor_put_ball(void)
{
//	//舵机
//	TIM4->CCR1=PUT_BALL1; 
//	TIM4->CCR2=PUT_BALL2;
//	 HAL_Delay(400);
	//舵机爪
	TIM4->CCR3=PUT_BALL_CLAW1;
	TIM4->CCR4=PUT_BALL_CLAW2;
//  HAL_Delay(400);
//	//舵机
//	 TIM4->CCR1=INITIAL1;//舵机回收复位
//	 TIM4->CCR2=INITIAL2;
//		HAL_Delay(400);
}
void motor_reset(void)
{
	//TIM4->CCR3 4
	TIM4->CCR3=GRIPPER_INITIAL_CLAW1;
	TIM4->CCR4=GRIPPER_INITIAL_CLAW2;
	//TIM4->CCR1 2
	TIM4->CCR1=INITIAL1;//舵机收缩，夹子夹紧
	TIM4->CCR2=INITIAL2;//舵机收缩，夹子夹紧
}
void motor_up_open(void)
{
	//舵机 上升
	TIM4->CCR1=INITIAL1; 
	TIM4->CCR2=INITIAL2;
	//舵机爪  张开
	TIM4->CCR3=GRIPPER_INITIAL_CLAW1;
	TIM4->CCR4=GRIPPER_INITIAL_CLAW2;
}
void motor_down_close(void)
{
	//舵机爪  收缩
	TIM4->CCR3=GRAB_BALL_CLAW1;
	TIM4->CCR4=GRAB_BALL_CLAW2;
	HAL_Delay(500);
	//舵机 下降
	TIM4->CCR1=MOTOR_DOWN1; 
	TIM4->CCR2=MOTOR_DOWN2;
}
void motor_grab_edge_ball(void)
{
	//舵机爪  收缩
	TIM4->CCR3=EDGE_BALL_CLAW_STATE1_1;
	TIM4->CCR4=EDGE_BALL_CLAW_STATE1_2;
	HAL_Delay(400);
	//舵机 下降
	TIM4->CCR1=EDGE_BALL_STATE1_1;
	TIM4->CCR2=EDGE_BALL_STATE1_2;
	HAL_Delay(200);
	//舵机爪 张开+舵机 下降
	TIM4->CCR3=EDGE_BALL_CLAW_STATE2_1;
	TIM4->CCR4=EDGE_BALL_CLAW_STATE2_2;
	TIM4->CCR1=EDGE_BALL_STATE2_1;
	TIM4->CCR2=EDGE_BALL_STATE2_2;
	HAL_Delay(200);
	//舵机 下降
	TIM4->CCR1=BALL1; 
	TIM4->CCR2=BALL2;
	HAL_Delay(200);
	//舵机爪 收缩抓取
	TIM4->CCR3=GRAB_BALL_CLAW1;
	TIM4->CCR4=GRAB_BALL_CLAW2;
	HAL_Delay(500);
	//舵机 上升
	 TIM4->CCR1=INITIAL1;//舵机回收复位
	 TIM4->CCR2=INITIAL2;
//	 HAL_Delay(400);
}
void motor_grab_edge_cube(void)
{
	//舵机爪  收缩
	TIM4->CCR3=EDGE_CUBE_CLAW_STATE1_1;
	TIM4->CCR4=EDGE_CUBE_CLAW_STATE1_1;
	HAL_Delay(400);
	//舵机 下降
	TIM4->CCR1=EDGE_BALL_STATE1_1;
	TIM4->CCR2=EDGE_BALL_STATE1_2;
	HAL_Delay(200);
	//舵机爪 张开+舵机 下降
	TIM4->CCR3=EDGE_CUBE_CLAW_STATE2_1;
	TIM4->CCR4=EDGE_CUBE_CLAW_STATE2_1;
	TIM4->CCR1=EDGE_BALL_STATE2_1;
	TIM4->CCR2=EDGE_BALL_STATE2_2;
	HAL_Delay(200);
	//舵机 下降
	TIM4->CCR1=BALL1; 
	TIM4->CCR2=BALL2;
	HAL_Delay(200);
	//舵机爪 收缩抓取
	TIM4->CCR3=GRAB_CUBE_CLAW1;
	TIM4->CCR4=GRAB_CUBE_CLAW2;
	HAL_Delay(500);
	//舵机 上升
	 TIM4->CCR1=INITIAL1;//舵机回收复位
	 TIM4->CCR2=INITIAL2;
//	 HAL_Delay(400);
}

unsigned int PWM_Limit(unsigned int pwm)
{
	if(pwm>2500) return 2500;
	if(pwm<500)  return 500;
	return pwm;
}
void motor_up_little(void)
{
	int pwm_temp1,pwm_temp2=0;
	pwm_temp1=TIM4->CCR1;
	pwm_temp2=TIM4->CCR2;
	TIM4->CCR1=PWM_Limit(pwm_temp1-50);
	TIM4->CCR2=PWM_Limit(pwm_temp2-50);	
}
void motor_down_little(void)
{
	int pwm_temp1,pwm_temp2=0;
	pwm_temp1=TIM4->CCR1;
	pwm_temp2=TIM4->CCR2;
	TIM4->CCR1=PWM_Limit(pwm_temp1+50);
	TIM4->CCR2=PWM_Limit(pwm_temp2+50);	
}
void motor_grab_cube_down(void)
{
	//舵机爪
	TIM4->CCR3=GRAB_BALL_CLAW1;
	TIM4->CCR4=GRAB_BALL_CLAW2;
	HAL_Delay(500);
	//舵机
	 TIM4->CCR1=CUBE1_DOWN;
	 TIM4->CCR2=CUBE2_DOWN;
//	 HAL_Delay(500);
}

void motor_swap(void)
{
	
}