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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>   //sprintf
#include <string.h>   //strlen
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
GPIO_PinState SwitchState[2];
uint32_t frequency = 1;
uint32_t TimeStamp = 0;
uint32_t LED1_HalfPeriod = 1000;
float ONOFF = 0;
float press = 0;
char TxDataBuffer[32] =
{ 0 };
char RxDataBuffer[32] =
{ 0 };

enum state
{
	mainmenu = 0,
	mainmenuwait,
	menuledcontrol,
	menuledcontrolwait,
	menubuttonstatus,
	menubuttonstatuswait
};

uint8_t state = mainmenu;
uint16_t test = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void UARTRecieveAndResponsePolling();
int16_t UARTRecieveIT();
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  {
	  //char temp[]="HELLO WORLD\r\n please type something to test UART\r\n";
	  char temp[]="MAIN MENU\r\n please type something to test UART\r\n";
	  //ประกาศ array , \r\n ขึ้นบรรทัดใหม่ของ ภาษา c
	  HAL_UART_Transmit(&huart2, (uint8_t*)temp, strlen(temp),10);
	  //strlen วางไว้ข้างหน้าตัวเเปรที่เราอยากจะเขียน ข้อความได้เลยอย่างเช่นอันนี้คือวางไว้ข้างหน้า temp ซึ่งนั้นก็คือตัวที่อยากจะทำการเขียนก็คือตัวเเปร temp
	  //
	  //uint8 temp ถ้าไม่ใส่ uint8 คือใส่เเต่ temp เลยมันจะขึ้น warning ว่ามันเป็นไฟล์เเปลกๆนะ



	  //สามารถเขียนเป็น case ได้
	  //if(HAL_UART_Transmit(&huart2, (uint8_t*)temp, strlen(temp),10) ≠ HAL_OK)
	  //{
	  	  	  //Error
	  //}

  }
  //ปีกกาทำให้ประหยัด memorie ขึ้นหรือเรียกอีกอย่างว่ากำหนดขอบเขตการทำงานของมันได้
  //ปีกกาเพื่อ จำกัดขอบเขตของตัวเเปรได้
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /*Method 1 Polling Mode*/

	  		//UARTRecieveAndResponsePolling();

	  		/*Method 2 Interrupt Mode*/
	  		HAL_UART_Receive_IT(&huart2,  (uint8_t*)RxDataBuffer, 32);
	  		//กำหนดขนาดตรงนี้อันสุดท้ายสุด
            //จะเห็นจากlive expression ว่าตัวอักษรอะมันเข้าระบบไปเเล้วเเต่การจะ received ออกมาได้คือต้อง
	  	//รอจนมันครบตัวที่ เรากำหนด เช่นเรากำหนดไว้ 32 มันก็จะรอจนกว่าจะครบตัวที่ 32 ถึงค่อย received
	  	//ใน huart2 เนี้ยมันจะมีตัวเเปร 	RxXferSize,RxXferCount
	  		//RxXferSize เท่ากับขนาดข้อมูลที่เราตั้งไว้ว่าให้มัน received ได้ครั้งนึงสมมติตั้ง 32 เเล้ว received คร้งนึ RxXferSizeจะขึ้นว่า 32
	  		//RxXferCount มันคือจะนับให้เราว่าเราพิมพ์ไปถึงตัวที่เท่าไหร่เเล้วเเต่มันจะเริ่มนับตั้งเเต่ 32->0 ทุกครั้งที่พิมพ์มันจะตกมาเรื่อยๆ โดยเริ่มจาก 32 เเละตกลงมาเรื่อยๆทุกครั้งที่เราพิมพ์เเละเมื่อมันถึง 0 ก้จะเริ่ม interupt ใหม่เป็น 32

	  		/*Method 2 W/ 1 Char Received*/
	  		int16_t inputchar = UARTRecieveIT();
	  		if(inputchar!=-1)
	  		{

	  			sprintf(TxDataBuffer, "ReceivedChar:[%c]\r\n", inputchar);
	  			HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  		}
	  		//receivedchar[a]
	  		//receivedchar[b]
	  		//receivedchar[c]
	  		//received[abcd]
	  		//receivedchar[d]



	  		/*This section just simmulate Work Load*/
//	  		HAL_Delay(100);
//	  		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  		SwitchState[0] = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	  		if(SwitchState[0] == GPIO_PIN_RESET && SwitchState[1] == GPIO_PIN_SET)
	  		{
	  			press = 1;
	  		}
	  		SwitchState[1] = SwitchState[0];

	  		LED1_HalfPeriod = ((1000/frequency)/2);

	  		if(ONOFF == 1)
			{
	  			if(HAL_GetTick() - TimeStamp >= LED1_HalfPeriod)
				{
	  				TimeStamp = HAL_GetTick();
	  				HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
				}
			}

			switch(state)
	  		{
	  			case mainmenu:
	  				sprintf(TxDataBuffer, "MainMenu\r\n0:LED CONTROL\r\n1:Button Status\r\n", inputchar);
	  				HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  				state = mainmenuwait;
	  				break;
	  			case mainmenuwait:
	  				switch(inputchar)
	  				{
	  					case '0':
	  					  	state = menuledcontrol;
	  					  	break;
	  					case '1':
	  						state = menubuttonstatus;
	  					  	break;
	  				}
	  				break;
	  			case menuledcontrol:
	  				sprintf(TxDataBuffer, "LED CONTROL\r\na:Speed Up +1Hz\r\ns:Speed Down -1Hz\r\nd:On/off\r\nx:back\r\n", inputchar);
	  				HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  				state = menuledcontrolwait;
	  				break;
	  			case menuledcontrolwait:
	  				switch(inputchar)
	  				{
	  					case 'a':
	  						if(frequency < 10)
	  						{
	  							frequency += 1;
	  							if(frequency == 0)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 0 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 1)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 1 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 2)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 2 Hz\r\n", inputchar);
	  							  	HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 3)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 3 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 4)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 4 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 5)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 5 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 6)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 6 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 7)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 7 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 8)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 8 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 9)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 9 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 10)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 10 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  						}
	  						else if(frequency == 10)
	  						{
	  							sprintf(TxDataBuffer, "Present Frequency = 10 Hz\r\n", inputchar);
	  							HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  						}
	  						break;
	  					case 's':
	  						if(frequency > 0)
	  						{
	  							frequency -= 1;
	  							if(frequency == 0)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 0 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 1)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 1 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 2)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 2 Hz\r\n", inputchar);
	  							  	HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 3)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 3 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 4)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 4 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 5)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 5 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 6)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 6 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 7)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 7 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 8)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 8 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 9)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 9 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  							else if(frequency == 10)
	  							{
	  								sprintf(TxDataBuffer, "Present Frequency = 10 Hz\r\n", inputchar);
	  								HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  							}
	  						}
	  						else if(frequency == 0)
	  						{
	  							sprintf(TxDataBuffer, "Present Frequency = 0 Hz\r\n", inputchar);
	  							HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  						}
	  						break;
	  					case 'd':
	  						if(ONOFF == 0)
	  						{
	  							ONOFF = 1;
	  						}
	  						else
	  						{
	  							ONOFF = 0;
	  							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  						}
	  						break;
	  					case 'x':
	  						state = mainmenu;
	  						break;
	  					default:
		  			  		sprintf(TxDataBuffer, "Wrong\r\n", inputchar);
		  			  		HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  				}
	  				break;
	  			case menubuttonstatus:
	  				sprintf(TxDataBuffer, "Button Status\r\nx:back\r\n", inputchar);
	  				HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  				state = menubuttonstatuswait;
	  				break;
	  			case menubuttonstatuswait:
					if(press == 0)
					{
			  			sprintf(TxDataBuffer, "Button:Unpress\r\n", inputchar);
			  			HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
					}
					if(press == 1)
					{
						sprintf(TxDataBuffer, "Button:Unpress\r\n", inputchar);
  			  			HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
					}
	  				switch(inputchar)
	  				{
	  					case 'x':
	  						state = mainmenu;
	  						break;
	  					default:
		  			  		sprintf(TxDataBuffer, "Wrong\r\n", inputchar);
		  			  		HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	  				}
	  				break;
	  		}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void UARTRecieveAndResponsePolling() //function ส่งอะไรมาเเล้วรับอะไรไป
{
	char Recieve[32]={0};
//Received ตามไฟกระพริบของ LD2ด้วย ไฟติด received ไฟดับ received เเละใน received สามารถกดเเป้น key พิมพ์ได้
	HAL_UART_Receive(&huart2, (uint8_t*)Recieve, 4, 1000);
//ส่งกลับไป
	//ถ้ากำหนดหลัง receive เป็น 4 เเปลว่าถ้าเรากดเเป้นพิมครบ 4 ตัวมันจะออกจาก function ทันทีเเละเเต่ละอันที่มัน received จะไม่มีทางเกิน 4 ถ้ายังกดไม่ครบ 4 ตัว มันจะ
	//receive ความเร็วตามปกติ เนื่องจากมันยังรอตัวอักษรที่ป้อนเข้าไป เเต่ ถ้าครบเเล้วมันจะออกจาก function ทันที มันจะขึ้น received เร็วมาก
	sprintf(TxDataBuffer, "Received:[%s]\r\n", Recieve);
	HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
//คือตัว printf มัน print ลงในตัวเเปรซักตัวเเปรนึง
	//print ไว้ใน databuffer ซึ่งมันเป็น global
}


int16_t UARTRecieveIT()
{
	static uint32_t dataPos =0;
	//ประกาศให้ตัวเเปรนี้รักษาค่าเดิมเอาไว้
	int16_t data=-1;
	if(huart2.RxXferSize - huart2.RxXferCount!=dataPos)
	{
		//เพื่อให้ได้ตำเเหน่งของข้อมูล
		data=RxDataBuffer[dataPos];
		dataPos= (dataPos+1)%huart2.RxXferSize;
	}
	return data;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	sprintf(TxDataBuffer, "Received:[%s]\r\n", RxDataBuffer);
	//HAL_UART_Transmit(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer), 1000);
	HAL_UART_Transmit_IT(&huart2, (uint8_t*)TxDataBuffer, strlen(TxDataBuffer));
	//functionนี้คือจะไม่ขึ้น receive จนกว่าจะใส่ข้อมูลครบ ถ้าเรากำหนดขนาด 32  มันจะ received ก็ต่อเมื่อมันครบ 32
}


/* USER CODE END 4 */

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
