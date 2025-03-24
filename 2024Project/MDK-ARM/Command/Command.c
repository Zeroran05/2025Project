#include "Command.h"
#include "Motor.h"
#include "RoundMotor.h"
#include "LinearMotor.h"
#include "Engine.h"

void Command_Analysis(void)
{
	if(RxFlag ==1)
	{
		RxFlag=0;
		Find_Flag=0;
		for(int i=0;i<93 && Find_Flag==0;i++)
		{
			if(Command[i]==0x53)
			{
				if(Command[i]==0x53 && Command[i+1]==0x5A && Command[i+2]==0x48 && Command[i+3]==0x59)
				{
					if(Command[i+4]==TRY_GRAB_CUBE || Command[i+4]==TRY_PUT_CUBE || Command[i+4]==TRY_GRAB_BALL || Command[i+4]==TRY_PUT_BALL 
						|| Command[i+4]==TRY_UNMOVE || Command[i+4]==TRY_SWAP || Command[i+4]==TRY_RESET || Command[i+4]==TRY_UP 
							|| Command[i+4]==TRY_DOWN || Command[i+4]==TRY_GRAB_EDGE_BALL || Command[i+4]==TRY_GRAB_EDGE_CUBE || Command[i+4]==TRY_UP_LITLLE 
								|| Command[i+4]==TRY_FORCE_RESET || Command[i+4]==TRY_FORCE_STOP || Command[i+4]==TRY_GRAB_CUBE_DOWN)
					{
						Check_Sum=Command[i+4]+Command[i+5]+Command[i+6]+1;
						if(Check_Sum==Command[i+7])
						{
							//强制停止
							if(Command[i+4]==TRY_FORCE_STOP)
							{
								Mode_Command=Command[i+4];
								transmit[4]=Mode_Command;
								
								Round_Angle=0;
								RoundEncoder = (float)(Round_Angle / 360.0 * ENCODERRESOLUTION);
								Motor1EncoderOverflowCnt=0;TIM1 -> CNT=0;				
								
								Linear_length=Calculate_Length();
								
								Find_Flag=1;
								Start_Flag=1;
								Round_Finish=1;
								Linear_Finish=1;
							    Linear_length=ROLL_MAX;
								transmit[6]=Linear_length;
							}
							//强制复位
							else if(Command[i+4]==TRY_FORCE_RESET)
							{
								Mode_Command=Command[i+4];
								transmit[4]=Mode_Command;
								
								Find_Flag=1;
								Start_Flag=1;
								Round_Finish=1;
								Linear_Finish=1;
							}
			
							else if(transmit[4]==0xFF)
							{
								Mode_Command=Command[i+4];
								Round_Command=Command[i+5];
								Linear_Command=Command[i+6];

								memcpy(&Linear_IntCommand,&Linear_Command,sizeof(int8_t));
								Linear_length=(double)(Linear_IntCommand/127.0*35.0);
								Round_Angle=Round_Command;
								if(Linear_length<0 && Round_Angle!=0) 
								{
									Round_Angle=Round_Angle-180;
									Linear_length=-Linear_length;
								}
								RoundEncoder = (float)(Round_Angle / 360.0 * ENCODERRESOLUTION);
								Motor1EncoderOverflowCnt=0;TIM1 -> CNT=0;						
								
								Find_Flag=1;
								Start_Flag=1;
								Round_Finish=0;
								Linear_Finish=0;
								
								transmit[4]=Mode_Command;
								old_angle=transmit[5];
								old_length=transmit[6];
								transmit[6]=Linear_length;
							}

						}
					}
				}
			}
		}
		Find_Flag=0;
		memset(Command,0x00,100);
		__HAL_DMA_DISABLE(&hdma_usart2_rx);
	}
			//StartTaskMotor1(Round_Angle,Linear_length);
			//StartTaskMotor2(fabs(Linear_length));
}
