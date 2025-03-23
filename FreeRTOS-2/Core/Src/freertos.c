/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Command.h"
#include "Motor.h"
#include "RoundMotor.h"
#include "LinearMotor.h"
#include "Engine.h"
#include "Variate.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;
osThreadId myTask05Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void RoundMotorTask(void const * argument);
void LinearMotorTask(void const * argument);
void Engine(void const * argument);
void Transmit(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
	RxFlag = xSemaphoreCreateBinary();
	Round_Finish = xSemaphoreCreateBinary();
	Linear_Finish = xSemaphoreCreateBinary();
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, RoundMotorTask, osPriorityIdle, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, LinearMotorTask, osPriorityIdle, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, Engine, osPriorityIdle, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* definition and creation of myTask05 */
  osThreadDef(myTask05, Transmit, osPriorityIdle, 0, 128);
  myTask05Handle = osThreadCreate(osThread(myTask05), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
	
	for(;;)
	{
		if(xSemaphoreTake(RxFlag,portMAX_DELAY) == pdTRUE)
		{
			Command_Analysis();
		}
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_RoundMotorTask */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RoundMotorTask */
void RoundMotorTask(void const * argument)
{
  /* USER CODE BEGIN RoundMotorTask */
  /* Infinite loop */
  for(;;)
  {
		if(Mode_Command!=TRY_FORCE_RESET)  
		{
			StartTaskMotor1();
		}
    osDelay(1);
  }
  /* USER CODE END RoundMotorTask */
}

/* USER CODE BEGIN Header_LinearMotorTask */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LinearMotorTask */
void LinearMotorTask(void const * argument)
{
  /* USER CODE BEGIN LinearMotorTask */
  /* Infinite loop */
  for(;;)
  {
		if(Mode_Command!=TRY_FORCE_RESET)  
		{
			StartTaskMotor2();
    }
		osDelay(1);
  }
  /* USER CODE END LinearMotorTask */
}

/* USER CODE BEGIN Header_Engine */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Engine */
void Engine(void const * argument)
{
  /* USER CODE BEGIN Engine */
  /* Infinite loop */
  for(;;)
  {
//		if(Mode_Command==TRY_SWAP)  
//		{
//			if(Start_Flag==1 && Round_Finish==0 && Linear_Finish==0)
//			{
//			TIM4->CCR1=INITIAL1-700; 
//			TIM4->CCR2=INITIAL1-700;
//			}
//			if(Start_Flag==1 && Round_Finish==1 && Linear_Finish==1)
//			{
//				TIM4->CCR1=INITIAL1; 
//				TIM4->CCR2=INITIAL1;
//				Start_Flag=0;
//				Round_Finish=0;
//				Linear_Finish=0;
//				transmit[4]=0xFF;
//			}		
//		}
		
		if(Start_Flag == 1 && xSemaphoreTake(Round_Finish,portMAX_DELAY) == pdTRUE && xSemaphoreTake(Linear_Finish,portMAX_DELAY) == pdTRUE)
		{
			if(Mode_Command==TRY_UNMOVE); 			
			else if(Mode_Command==TRY_GRAB_CUBE) 			motor_grab_cube();//
			else if(Mode_Command==TRY_PUT_CUBE)  			motor_put_cube();
			else if(Mode_Command==TRY_GRAB_BALL) 			motor_grab_ball();
			else if(Mode_Command==TRY_PUT_BALL)  			motor_put_ball();
			else if(Mode_Command==TRY_RESET) 		 			motor_reset();
			else if(Mode_Command==TRY_UP) 		   			motor_up_open();
			else if(Mode_Command==TRY_DOWN) 		 			motor_down_close();
			else if(Mode_Command==TRY_GRAB_EDGE_BALL) motor_grab_edge_ball();
			else if(Mode_Command==TRY_GRAB_EDGE_CUBE) motor_grab_edge_cube();
			else if(Mode_Command==TRY_UP_LITLLE)      motor_up_little();
			else if(Mode_Command==TRY_GRAB_CUBE_DOWN) motor_grab_cube_down();
			else if(Mode_Command==TRY_SWAP)						motor_swap();
			transmit[4]=0xFF;			
			Start_Flag=0;
		}
		
    osDelay(1);
  }
  /* USER CODE END Engine */
}

/* USER CODE BEGIN Header_Transmit */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Transmit */
void Transmit(void const * argument)
{
  /* USER CODE BEGIN Transmit */
  /* Infinite loop */
  for(;;)
  {
		transmit[7]=transmit[4]+transmit[5]+transmit[6];
		HAL_UART_Transmit_DMA(&huart2,(uint8_t *)transmit, 8);	
    osDelay(1);
  }
  /* USER CODE END Transmit */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
