/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "navigation_module.h"
#include "motor.h"
#include "servo.h"
#include "bsp_can.h"
#include "stepper.h"
#include "arm.h"
#include "chassis.h"
#include "remote.h"
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

/* USER CODE BEGIN PV */
extern struct Servo_t servo_grab;
extern struct Servo_t servo_platform;
extern struct Servo_t servo_raise_l;
extern struct Servo_t  servo_raise_r;
extern struct Stepper_t stepper;
// uint8_t pwm_ok=0;
extern Arm_t robot_arm;
extern struct Chassis_t chassis;
extern struct DT7Remote_t Remote;

extern struct CAN_Motor can1_motor_1;
extern struct CAN_Motor can1_motor_2;
extern struct CAN_Motor can1_motor_3;
extern struct CAN_Motor can1_motor_4;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
// void out_pwm(uint32_t num)
// {
//   if(pwm_ok==1)
//   {
//     pwm_ok=0;
// 	__HAL_TIM_SetCounter(&htim1,0);
//     __HAL_TIM_SET_AUTORELOAD(&htim1,num-1);
//     HAL_TIM_Base_Start_IT(&htim1);
//     HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_2);
//   }
// }
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)

{
  /* USER CODE BEGIN 1 */
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_CAN1_Init();
  MX_USART6_UART_Init();
  MX_UART8_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_CAN2_Init();
  /* USER CODE BEGIN 2 */
	Remote_init();
  navi_init();  //初始化定位模块通信
  CanFilterInit(&hcan1);
  arm_attach(&robot_arm,&servo_grab,&servo_raise_l,&servo_raise_r,&servo_platform,&stepper);
  //arm_param_init(&robot_arm,grabber_release,90,0,H);
	MotorParamInit(&can1_motor_1,100,0,0,2400,5000,0,0,0,0,0);
	MotorParamInit(&can1_motor_2,100,0,0,2400,5000,0,0,0,0,0);
	MotorParamInit(&can1_motor_3,100,0,0,2400,5000,0,0,0,0,0);
	MotorParamInit(&can1_motor_4,100,0,0,2400,5000,0,0,0,0,0);
  
  stepper_init(&stepper); //步进电机初始化
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);	//舵机
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);	//舵机
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);	//舵机
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);	//舵机
	
	
//	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);	//步进
	// HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);	//步进

  // HAL_TIM_Base_Start_IT(&htim1);
	//HAL_TIM_PWM_Start_IT(&htim3,TIM_CHANNEL_2);
  //__HAL_TIM_SET_AUTORELOAD(&htim1,0);
	
	//HAL_GPIO_WritePin(STEP2_L_DIR_GPIO_Port,STEP2_L_DIR_Pin,GPIO_PIN_RESET);	//
	// HAL_GPIO_WritePin(J2_STEP_L_DIR_GPIO_Port,J2_STEP_L_DIR_Pin,GPIO_PIN_SET);	//暂时用作5v输出
	// HAL_GPIO_WritePin(K1_STEP_R_EN_GPIO_Port,K1_STEP_R_EN_Pin,GPIO_PIN_SET);
	
//	__HAL_TIM_SetAutoreload(&htim3,2000);
//	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,6000);
	
	// new_aar=500;
  /* USER CODE END 2 */

  /* Init scheduler */
  //osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  //MX_FREERTOS_Init();
  /* Start scheduler */
  //osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  arm_turn_wrist(&robot_arm,(enum Wrist_Pos_e)outside);
//	  HAL_Delay(1000);
//	  arm_catch(&robot_arm);
//	  HAL_Delay(700);
//	  arm_turn_wrist(&robot_arm,(enum Wrist_Pos_e)hold);
//	  arm_turnToID(&robot_arm,I);
//	  HAL_Delay(200);
//	  arm_turn_wrist(&robot_arm,(enum Wrist_Pos_e)platform);
//	  HAL_Delay(1000);
//	  arm_release(&robot_arm);
//	  HAL_Delay(2000);
//	  arm_turn_wrist(&robot_arm,(enum Wrist_Pos_e)camera);
//	  HAL_Delay(800);
//	  arm_turnToID(&robot_arm,H);
//	  
//	  //arm_turnToID(&robot_arm,T);
//	  HAL_Delay(1500);
//		stepper_setSpeed(&stepper,-2300);
//		stepper_setSteps(&stepper,3000);
//		HAL_Delay(5000);
//		stepper_setSpeed(&stepper,1300);
//		stepper_setSteps(&stepper,3000);
//		HAL_Delay(5000);

		
	  if(Remote.inputmode==RC_Remote)
	  {
			//chassis_move(10,0);
//			stepper_setSpeed(&stepper,2300);
//			stepper_setSteps(&stepper,10000);
//			HAL_Delay(2000);
			arm_lift(&robot_arm,10000,2300);
			
			//CanTransmit_1234(&hcan1,-1000, 1000, 1000, -1000);

		}
		else if(Remote.inputmode==RC_Stop)
		{
			stepper_stop(&stepper);
			//CanTransmit_1234(&hcan1,0, 0, 0, 0);
			HAL_Delay(20);

		}
		else if(Remote.inputmode==RC_MouseKey)
		{
			stepper_setSpeed(&stepper,-2300);
			stepper_setSteps(&stepper,10000);
			HAL_Delay(20);
		}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim==(&SLAVE_HTIM))
  {
    stepper_TIM_PeriodElapsedCallback(&SLAVE_HTIM,&stepper);
	  
  }
  
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
