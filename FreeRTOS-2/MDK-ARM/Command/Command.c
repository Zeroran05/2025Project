#include "Command.h"
#include "Motor.h"
#include "RoundMotor.h"
#include "LinearMotor.h"
#include "Engine.h"

void Command_Analysis(void)
{
	int8_t i=0;
	i=FindCommand(i);
	if(i==-1)  return;
	Check_Sum=Command[i+4]+Command[i+5]+Command[i+6]+1;
	if(Check_Sum==Command[i+7])
	{
		//强制停止
		if(Command[i+4]==TRY_FORCE_STOP)
		{
			Mode_Command=Command[i+4];
			transmit[4]=Mode_Command;
			
			Round_Angle=0;
			RoundEncoder = 0;//set zero to the round_aim value
			Motor1EncoderOverflowCnt=0;TIM1 -> CNT=0;//set zero to the present value
			
			Linear_length=ROLL_MAX;//make linear motor move to end
			transmit[6]=Linear_length;
		}
		//强制复位
		else if(Command[i+4]==TRY_FORCE_RESET)
		{
			Mode_Command=Command[i+4];
			transmit[4]=Mode_Command;
			LinearMotorInit();
			transmit[4]=TRY_FREE;
		}

		else if(transmit[4]==TRY_FREE)// 空闲状态
		{
			Mode_Command=Command[i+4];
			Round_Command=Command[i+5];
			Linear_Command=Command[i+6];

			Data_cal();
			Motor1EncoderOverflowCnt=0;TIM1 -> CNT=0;						
			
			xSemaphoreGive(Start_Flag);
			
			transmit[4]=Mode_Command;
			old_angle=transmit[5];
		}
		NewMessage1=true;
		NewMessage2=true;
	}
				
	memset(Command,0x00,100);
	__HAL_DMA_DISABLE(&hdma_usart2_rx);
		//StartTaskMotor1(Round_Angle,Linear_length);
		//StartTaskMotor2(fabs(Linear_length));
}

int8_t FindCommand(int8_t i)
{
	while(Command[i]!=0x53 || Command[i+1]!=0x5A || Command[i+2]!=0x48 || Command[i+3]!=0x59)
	{
		i++;
		if(i>=93)  
		{
			return -1;
		}
	}
	if((Command[i+4]>TRY_UNMOVE && Command[i+4]<=TRY_GRAB_CUBE_DOWN) || Command[i+4]==TRY_FORCE_RESET || Command[i+4]==TRY_FORCE_STOP || Command[i+4]==TRY_UNMOVE)
	{	
		return i;
	}
	else 
	{
		return -1;
	}		
}

void Data_cal(void)
{
	memcpy(&Linear_IntCommand,&Linear_Command,sizeof(int8_t));
	Linear_length=(double)(Linear_IntCommand/127.0*35.0);
	Round_Angle=Round_Command;
	if(Linear_length<0 && Round_Angle!=0) 
	{
		Round_Angle=Round_Angle-180;
		Linear_length=-Linear_length;
	}
}
