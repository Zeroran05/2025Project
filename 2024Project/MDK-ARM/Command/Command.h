#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "usart.h"
#include "string.h"
#include "Variate.h"

//0 Command
//#define LENGTH 100
#define TRY_UNMOVE							0x00	 // 机械爪不动，回转电机、直线电机运动
#define TRY_GRAB_BALL        		0x01     // 抓取球				
#define TRY_GRAB_CUBE        		0x02     // 抓取魔方			
#define TRY_PUT_BALL						0x03     // 投放球	
#define TRY_PUT_CUBE         		0x04     // 投放魔方	
#define TRY_SWAP				 				0x05     // 爪臂横扫	
#define TRY_RESET				 				0x06     // 爪臂复位
#define TRY_UP				 					0x07     // 爪臂上	
#define TRY_DOWN							 	0x08     // 爪臂下	
#define TRY_GRAB_EDGE_BALL	 		0x09     // 抓取边缘球				
#define TRY_GRAB_EDGE_CUBE   		0x0A     // 抓取边缘魔方		
#define TRY_UP_LITLLE						0x0B	 	// 上升一点点
//#define TRY_DOWN_LITTLE			 
#define TRY_GRAB_CUBE_DOWN   		0x0C	 // 四两拨千斤_爪子下去	

#define TRY_FORCE_RESET			 		0xfc     // 强制复位状态	
#define TRY_FORCE_STOP			 		0xfe     // 强制停止状态	
#define TRY_FREE				 				0xff     // 空闲状态	


void Command_Analysis(void);
#endif
