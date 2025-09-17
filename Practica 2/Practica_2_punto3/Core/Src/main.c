/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
  * @brief  Inicializa una estructura de retardo.
  * @param  delay: Puntero a la estructura de retardo.
  * @param  duration: Duración del retardo en milisegundos (ms).
  * @retval None
  */
void delayInit( delay_t * delay, tick_t duration )
{
	delay->duration = duration;
	delay->running = false;
}

/**
  * @brief  Lee el estado del retardo. Si no está corriendo, lo inicia.
  *         Si está corriendo, verifica si se ha cumplido el tiempo.
  * @param  delay: Puntero a la estructura de retardo.
  * @retval bool_t: true si el tiempo se cumplió, false en caso contrario.
  */
bool_t delayRead( delay_t * delay )
{
	bool_t time_cumplido = false; // Variable para almacenar el resultado

	if( !delay->running )
	{
		// Si el retardo no está corriendo, tomamos la marca de tiempo inicial
		// y lo ponemos a correr.
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else
	{
		// Si el retardo ya está corriendo, verificamos si ha pasado el tiempo.
		// La resta de enteros sin signo gestiona automáticamente el desbordamiento (rollover)
		// del contador de HAL_GetTick().
		if( (HAL_GetTick() - delay->startTime) >= delay->duration )
		{
			// Si el tiempo se cumplió, lo indicamos y reiniciamos el flag.
			time_cumplido = true;
			delay->running = false;
		}
	}

	return time_cumplido;
}

/**
  * @brief  Permite actualizar la duración de un retardo existente.
  * @param  delay: Puntero a la estructura de retardo.
  * @param  duration: Nueva duración del retardo en milisegundos (ms).
  * @retval None
  */
void delayWrite( delay_t * delay, tick_t duration )
{
	delay->duration = duration;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	// Estructura para definir cada paso del patrón de parpadeo
		typedef struct {
		    tick_t period_ms;   // Período total del parpadeo (ON + OFF)
		    uint8_t num_blinks; // Cantidad de parpadeos para este período
		} BlinkPattern_t;

		// Arreglo constante que define la secuencia completa
		const BlinkPattern_t pattern[] = {
		    {1000, 5}, // 5 veces con período de 1 segundo (500ms ON, 500ms OFF)
		    {200,  5}, // 5 veces con período de 200 ms (100ms ON, 100ms OFF)
		    {100,  5}  // 5 veces con período de 100 ms (50ms ON, 50ms OFF)
		};

		// Variables para gestionar el estado de la secuencia
		uint8_t pattern_index = 0;
		uint8_t toggle_count = 0;

		// Nuestra variable de retardo, como antes
		delay_t led_delay;
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
  // Calculamos el número total de pasos en nuestro patrón
    const uint8_t pattern_size = sizeof(pattern) / sizeof(pattern[0]);

    // Inicializamos el retardo con la duración del PRIMER paso del patrón.
    // La duración del retardo es la MITAD del período para un ciclo de trabajo del 50%.
    delayInit(&led_delay, pattern[pattern_index].period_ms / 2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // Verificamos si se cumplió el tiempo de retardo actual
	      if ( delayRead(&led_delay) )
	      {
	          // 1. Invertimos el estado del LED
	          HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	          // 2. Incrementamos el contador de inversiones
	          toggle_count++;

	          // 3. Verificamos si completamos los parpadeos de la fase actual
	          // (num_blinks * 2 porque cada parpadeo tiene un ON y un OFF)
	          if ( toggle_count >= (pattern[pattern_index].num_blinks * 2) )
	          {
	              // Fase completada, reiniciamos el contador de toggles
	              toggle_count = 0;

	              // Avanzamos al siguiente paso del patrón
	              pattern_index++;

	              // Si llegamos al final del patrón, volvemos al inicio
	              if ( pattern_index >= pattern_size )
	              {
	                  pattern_index = 0;
	              }

	              // 4. ACTUALIZAMOS la duración del retardo para la NUEVA fase
	              delayWrite(&led_delay, pattern[pattern_index].period_ms / 2);
	          }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

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
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

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

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
#ifdef USE_FULL_ASSERT
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
