/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CayenneMQTTClient.h"
#include"GenericMQTT.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SaturaLH(N, L, H) (((N)<(L))?(L):(((N)>(H))?(H):(N)))
#define M24SR_ADDR 0xAC // Dirección I2C del dispositivo M24SR
#define BUFFER_SIZE 10

#define SENIAL1 0x10
#define SENIAL2 0x20
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

DFSDM_Filter_HandleTypeDef hdfsdm1_filter0;
DFSDM_Channel_HandleTypeDef hdfsdm1_channel2;
DMA_HandleTypeDef hdma_dfsdm1_flt0;

I2C_HandleTypeDef hi2c2;

RNG_HandleTypeDef hrng;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart1;

/* Definitions for Zafron */
osThreadId_t ZafronHandle;
const osThreadAttr_t Zafron_attributes = {
  .name = "Zafron",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Representacion */
osThreadId_t RepresentacionHandle;
const osThreadAttr_t Representacion_attributes = {
  .name = "Representacion",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Microfono */
osThreadId_t MicrofonoHandle;
const osThreadAttr_t Microfono_attributes = {
  .name = "Microfono",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
net_hnd_t hnet; /* Es inicializado porcloud_main(). */

net_sockhnd_t socket;
CayenneMQTTClient mqttClient;
Network network;
Timer timer;

char *username = "a8f3a0ec-6d65-4a45-bfb6-4ea3a2f5b438";
char *password = "00000000764D8D03";
char *clientID = "D61ED7EE";

bool FLAG1 = false;
bool encendido = true;
bool estadoLED = false;

AUDIO_DrvTypeDef *audio_drv;
int32_t RecBuff[2048];
int16_t PlayBuff[4096];
uint32_t DmaRecHalfBuffCplt = 0;
uint32_t DmaRecBuffCplt = 0;
uint32_t PlaybackStarted = 0;

uint16_t numeroDetecciones;
uint16_t numeroPulsaciones;
//uint16_t volumenMicro;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C2_Init(void);
static void MX_RNG_Init(void);
static void MX_RTC_Init(void);
static void MX_SPI3_Init(void);
static void MX_CRC_Init(void);
static void MX_DFSDM1_Init(void);
void StartZafron(void *argument);
void StartRepresentacion(void *argument);
void StartMicrofono(void *argument);

/* USER CODE BEGIN PFP */
void SPI_WIFI_ISR(void);
bool inicializa_ConexionIoT(void);
bool inicia_ClienteMQTT(void);

void messageArrived(CayenneMessageData *message);
void outputMessage(CayenneMessageData *message);
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

	/* Configure the peripherals common clocks */
	PeriphCommonClock_Config();

	/* USER CODE BEGIN SysInit */
	BSP_LED_Init(LED_GREEN);	//Led de usuario en la placa
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);	//PushButton de la placa
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_USART1_UART_Init();
	MX_I2C2_Init();
	MX_RNG_Init();
	MX_RTC_Init();
	MX_SPI3_Init();
	MX_CRC_Init();
	MX_DFSDM1_Init();

	/* USER CODE BEGIN 2 */
	numeroDetecciones = 0;
	numeroPulsaciones = 0;
	NFC_IO_Init(1);
	inicializarTemperatura();
	inicializarHumedad();
	inicializarBarometro();
	inicializarAcelerometro();
	inicializarGiro();
	inicializarMagneto();
	inicializarToF();
	//inicializarSensores();
	if (HAL_OK
			!= HAL_DFSDM_FilterRegularStart_DMA(&hdfsdm1_filter0, RecBuff,
					2048)) { //Inicializar micro
		Error_Handler();
	}

	inicializa_ConexionIoT();
	inicia_ClienteMQTT();

	printf("\x1b[2J" "\x1b[f"); //limpiar buffer y ventana de TeraTerm

	/* USER CODE END 2 */

	/* Init scheduler */
	osKernelInitialize();

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* creation of Zafron */
	ZafronHandle = osThreadNew(StartZafron, NULL, &Zafron_attributes);

	/* creation of Representacion */
	RepresentacionHandle = osThreadNew(StartRepresentacion, NULL,
			&Representacion_attributes);

	/* creation of Microfono */
	MicrofonoHandle = osThreadNew(StartMicrofono, NULL, &Microfono_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
	//publicador = osThreadNew(publicaDatos, NULL, &defaultTask_attributes_1);
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

	/* Start scheduler */
	osKernelStart();
	/* We should never get here as control is now taken by the scheduler */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1) {
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SAI1|RCC_PERIPHCLK_RNG;
  PeriphClkInit.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI1;
  PeriphClkInit.RngClockSelection = RCC_RNGCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 24;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_SAI1CLK|RCC_PLLSAI1_48M2CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DFSDM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DFSDM1_Init(void)
{

  /* USER CODE BEGIN DFSDM1_Init 0 */

  /* USER CODE END DFSDM1_Init 0 */

  /* USER CODE BEGIN DFSDM1_Init 1 */

  /* USER CODE END DFSDM1_Init 1 */
  hdfsdm1_filter0.Instance = DFSDM1_Filter0;
  hdfsdm1_filter0.Init.RegularParam.Trigger = DFSDM_FILTER_SW_TRIGGER;
  hdfsdm1_filter0.Init.RegularParam.FastMode = ENABLE;
  hdfsdm1_filter0.Init.RegularParam.DmaMode = ENABLE;
  hdfsdm1_filter0.Init.InjectedParam.Trigger = DFSDM_FILTER_SW_TRIGGER;
  hdfsdm1_filter0.Init.InjectedParam.ScanMode = ENABLE;
  hdfsdm1_filter0.Init.InjectedParam.DmaMode = DISABLE;
  hdfsdm1_filter0.Init.InjectedParam.ExtTrigger = DFSDM_FILTER_EXT_TRIG_TIM1_TRGO;
  hdfsdm1_filter0.Init.InjectedParam.ExtTriggerEdge = DFSDM_FILTER_EXT_TRIG_RISING_EDGE;
  hdfsdm1_filter0.Init.FilterParam.SincOrder = DFSDM_FILTER_SINC3_ORDER;
  hdfsdm1_filter0.Init.FilterParam.Oversampling = 64;
  hdfsdm1_filter0.Init.FilterParam.IntOversampling = 1;
  if (HAL_DFSDM_FilterInit(&hdfsdm1_filter0) != HAL_OK)
  {
    Error_Handler();
  }
  hdfsdm1_channel2.Instance = DFSDM1_Channel2;
  hdfsdm1_channel2.Init.OutputClock.Activation = ENABLE;
  hdfsdm1_channel2.Init.OutputClock.Selection = DFSDM_CHANNEL_OUTPUT_CLOCK_AUDIO;
  hdfsdm1_channel2.Init.OutputClock.Divider = 4;
  hdfsdm1_channel2.Init.Input.Multiplexer = DFSDM_CHANNEL_EXTERNAL_INPUTS;
  hdfsdm1_channel2.Init.Input.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
  hdfsdm1_channel2.Init.Input.Pins = DFSDM_CHANNEL_SAME_CHANNEL_PINS;
  hdfsdm1_channel2.Init.SerialInterface.Type = DFSDM_CHANNEL_SPI_RISING;
  hdfsdm1_channel2.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
  hdfsdm1_channel2.Init.Awd.FilterOrder = DFSDM_CHANNEL_FASTSINC_ORDER;
  hdfsdm1_channel2.Init.Awd.Oversampling = 10;
  hdfsdm1_channel2.Init.Offset = 0;
  hdfsdm1_channel2.Init.RightBitShift = 0x02;
  if (HAL_DFSDM_ChannelInit(&hdfsdm1_channel2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DFSDM_FilterConfigRegChannel(&hdfsdm1_filter0, DFSDM_CHANNEL_2, DFSDM_CONTINUOUS_CONV_ON) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DFSDM_FilterConfigInjChannel(&hdfsdm1_filter0, DFSDM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DFSDM1_Init 2 */

  /* USER CODE END DFSDM1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x10909CEC;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0;
  sTime.Minutes = 0;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 1;
  sDate.Year = 0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
	HAL_RTCEx_WakeUpTimerIRQHandler(&hrtc);
  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
	BSP_COM_Init(COM1, &huart1); //Transmisión de los datos por el puerto USART1 al COM del ordenador por USB
  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2|RED_LED_Pin|ISM43362_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, ARD_A2_LEDON_Pin|ARD_A1_LEDWIFI_Pin|LED3_WIFI__LED4_BLE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ARD_A0_3_3CTRL_GPIO_Port, ARD_A0_3_3CTRL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ISM43362_BOOT0_Pin|ISM43362_WAKEUP_Pin|LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(STSAFE_A100_RESET_GPIO_Port, STSAFE_A100_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ISM43362_SPI3_CSN_GPIO_Port, ISM43362_SPI3_CSN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PE2 RED_LED_Pin ISM43362_RST_Pin ISM43362_SPI3_CSN_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_2|RED_LED_Pin|ISM43362_RST_Pin|ISM43362_SPI3_CSN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PE4 ISM43362_DRDY_EXTI1_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_4|ISM43362_DRDY_EXTI1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : ARD_A2_LEDON_Pin ARD_A1_LEDWIFI_Pin LED3_WIFI__LED4_BLE_Pin */
  GPIO_InitStruct.Pin = ARD_A2_LEDON_Pin|ARD_A1_LEDWIFI_Pin|LED3_WIFI__LED4_BLE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : ARD_A0_3_3CTRL_Pin */
  GPIO_InitStruct.Pin = ARD_A0_3_3CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ARD_A0_3_3CTRL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ISM43362_BOOT0_Pin ISM43362_WAKEUP_Pin LED2_Pin */
  GPIO_InitStruct.Pin = ISM43362_BOOT0_Pin|ISM43362_WAKEUP_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : STSAFE_A100_RESET_Pin */
  GPIO_InitStruct.Pin = STSAFE_A100_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(STSAFE_A100_RESET_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/**********************Funciones para habilitar el envío de mensajes por el USART1 al COM del ordenador*********
 * **********************************************************************************************************
 */
#if (defined(__GNUC__) && !defined(__CC_ARM))
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART2 and Loop until the end of transmission */
	while (HAL_OK != HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 30000)) {
		;
	}
	return ch;
}

/**
 * @brief  Retargets the C library scanf function to the USART.
 * @param  None
 * @retval None
 */
GETCHAR_PROTOTYPE {
	/* Place your implementation of fgetc here */
	/* e.g. read a character on USART and loop until the end of read */
	uint8_t ch = 0;
	while (HAL_OK != HAL_UART_Receive(&huart1, (uint8_t*) &ch, 1, 30000)) {
		;
	}
	return ch;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin) {
	/*case (GPIO_PIN_13): {
	 Button_ISR();
	 break;
	 }*/

	case (GPIO_PIN_1): {
		SPI_WIFI_ISR();
		break;
	}

	default: {
		break;
	}
	}
}

bool inicializa_ConexionIoT(void) {
	int ret = 0;
	const char *connectionString = NULL;
	ret = platform_init();
	if (ret != 0) {
		msg_error(
				"\nFallo al inicializar la plataforma de conexión a Internet.\n");
		HAL_GPIO_WritePin(GPIOC, RD_A1_LEDWIFI_Pin, GPIO_PIN_RESET); //LED de conexión Wi-Fi}

	} else {
		ret = (getIoTDeviceConfig(&connectionString) != 0);
		ret |= (parse_and_fill_device_config(&device_config, connectionString)
				!= 0);
		connection_security = (conn_sec_t) atoi(device_config->ConnSecurity);
		HAL_GPIO_WritePin(GPIOC, RD_A1_LEDWIFI_Pin, GPIO_PIN_SET); //LED de conexión Wi-Fi}
	}

	if (ret != 0) {
		msg_error(
				"\nNo se pudo recuperar la cadena de conexion de la configuracion del usuario desde el almacenamiento.\n");
	} else {
		net_macaddr_t mac = { 0 };
		if (net_get_mac_address(hnet, &mac) == NET_OK) {
			snprintf(pub_data.mac, MODEL_MAC_SIZE, "%02X%02X%02X%02X%02X%02X",
					mac.mac[0], mac.mac[1], mac.mac[2], mac.mac[3], mac.mac[4],
					mac.mac[5]);
		} else {
			msg_warning("\nNo se pudo recuperar la direccion MAC pare establecer la ID del dispositivo \n");
			snprintf(pub_data.mac, MODEL_MAC_SIZE - 1, "UnknownMAC");
		}
	}
	return (ret == 0);
}

bool inicia_ClienteMQTT() {
	int error = 0;
	int ret = net_sock_create(hnet, &socket,
			(connection_security == CONN_SEC_NONE) ?
					NET_PROTO_TCP : NET_PROTO_TLS);
	net_sock_setopt(socket, "sock_noblocking", NULL, 0);
	net_sock_open(socket, CAYENNE_DOMAIN,
	CAYENNE_PORT, 0);
	if (ret != NET_OK) //Error al abrir el Socket en el servidor IoT que le hemos facilitado
	{
		msg_error(
				"\nNo se pudo abrir un socket en la direccion %s  con puerto %d.\n",
				CAYENNE_DOMAIN, CAYENNE_PORT);
		g_connection_needed_score++;
		return error;
	}

	else {

		network.my_socket = socket;
		network.mqttread = (network_read);
		network.mqttwrite = (network_write);
		CayenneMQTTClientInit(&mqttClient, &network, username, password,
				clientID, messageArrived);
		if ((error = CayenneMQTTConnect(&mqttClient)) != MQTT_SUCCESS) {
			printf("MQTT connect failed, error: %d\n", error);
			return error;
		}
		printf("Connected\n");

		// Subscribe to required topics.
		if ((error = CayenneMQTTSubscribe(&mqttClient, NULL, COMMAND_TOPIC,
		CAYENNE_ALL_CHANNELS, NULL)) != CAYENNE_SUCCESS) {
			printf("Subscription to Command topic failed, error: %d\n", error);
		}
		if ((error = CayenneMQTTSubscribe(&mqttClient, NULL, CONFIG_TOPIC,
		CAYENNE_ALL_CHANNELS, NULL)) != CAYENNE_SUCCESS) {
			printf("Subscription to Config topic failed, error:%d\n", error);
		}
		if ((error = CayenneMQTTSubscribe(&mqttClient, NULL, DATA_TOPIC,
		CAYENNE_ALL_CHANNELS, NULL)) != CAYENNE_SUCCESS) {
			printf("Subscription to Config topic failed, error:%d\n", error);
		}
		// Send device info. Here we just send some example values for the system info. These should be changed to use actual system data, or removed if not needed.
		CayenneMQTTPublishData(&mqttClient, NULL, SYS_VERSION_TOPIC,
		CAYENNE_NO_CHANNEL, NULL, NULL, CAYENNE_VERSION);
		CayenneMQTTPublishData(&mqttClient, NULL, SYS_MODEL_TOPIC,
		CAYENNE_NO_CHANNEL, NULL, NULL, "Windows");

	}
	FLAG1 = true; //Si se ha iniciado correctamente
	return CAYENNE_SUCCESS;
}

void outputMessage(CayenneMessageData *message) {
	size_t i;
	switch (message->topic) {
	case COMMAND_TOPIC:
		printf("topic=Command");
		break;
	case CONFIG_TOPIC:
		printf("topic=Config");
		break;
	default:
		printf("topic=%d", message->topic);
		break;
	}
	printf(" channel=%d", message->channel);
	if (message->clientID) {
		printf(" clientID=%s", message->clientID);
	}
	if (message->type) {
		printf(" type=%s", message->type);
	}
	for (i = 0; i < message->valueCount; ++i) {
		if (message->values[i].value) {
			printf(" value=%s", message->values[i].value);
		}
		if (message->values[i].unit) {
			printf(" unit=%s", message->values[i].unit);
		}
	}
	if (message->id) {
		printf(" id=%s", message->id);
	}
	printf("\n");
}

/**
 * Handle messages received from the Zafron server.
 * @param[in] message The message received from the Zafron server.
 */
// Handle messages received from the Zafron server.
void messageArrived(CayenneMessageData *message) {
	if (message->channel == 15 && (atoi(message->values[0].value) == 0)) {
		printf("Message received on channel %d: 0\n", message->channel);
		encendido = false;

	}
	if (message->channel == 15 && (atoi(message->values[0].value) == 1)) {
		printf("Message received on channel %d: 1\n", message->channel);
		encendido = true;

	}

	if (message->channel == 16 && (atoi(message->values[0].value) == 0)) {
		printf("Message received on channel %d: 0\n", message->channel);
		BSP_LED_Off(LED2);
		estadoLED = false;
	}
	if (message->channel == 16 && (atoi(message->values[0].value) == 1)) {
		printf("Message received on channel %d: 1\n", message->channel);
		BSP_LED_On(LED2);
		estadoLED = true;


	}
	// Add code to process the message here.
	if (message->topic == COMMAND_TOPIC) {
		// If this is a command message we publish a response to show we recieved it. Here we are just sending a default 'OK' response.
		// An error response should be sent if there are issues processing the message.
		CayenneMQTTPublishResponse(&mqttClient, message->clientID, message->id,
		NULL);
		// Send the updated state for the channel so it is reflected in the Zafron dashboard. If a command is successfully processed
		// the updated state will usually just be the value received in the command message.
		CayenneMQTTPublishData(&mqttClient, message->clientID, DATA_TOPIC,
				message->channel, NULL, NULL, message->values[0].value);
	}
}

void HAL_DFSDM_FilterRegConvHalfCpltCallback(
		DFSDM_Filter_HandleTypeDef *hdfsdm_filter) {
	DmaRecHalfBuffCplt = 1;
}

void HAL_DFSDM_FilterRegConvCpltCallback(
		DFSDM_Filter_HandleTypeDef *hdfsdm_filter) {
	DmaRecBuffCplt = 1;
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartCayenne */
/**
 * @brief  Function implementing the Zafron thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartCayenne */
void StartZafron(void *argument)
{
  /* USER CODE BEGIN 5 */
	/* Infinite loop */

	if (FLAG1) {

		while (1) {

			CayenneMQTTYield(&mqttClient, 1000);

			if (net_sock_setopt(socket, "sock_noblocking", NULL, 0) != NET_OK
					|| !CayenneMQTTConnected(&mqttClient)) {
				net_sock_close(socket);
				CayenneMQTTDisconnect(&mqttClient);
				printf("Reconectando\n");
				while (inicia_ClienteMQTT() != CAYENNE_SUCCESS) {
					return;
				}

			}

			getTemperatura(&temperatura);
			getHumedad(&humedad);
			getAxisAccelerometer(&accx, &accy, &accz);
			getAxisGyro(&gyrox, &gyroy, &gyroz);
			getMagnetoAxis(&magx, &magy, &magz);
			getPresion(&pressure);
			inicializarToF();
			getDistancia(&distancia);



			osThreadFlagsSet(RepresentacionHandle, SENIAL1);
			osThreadFlagsSet(MicrofonoHandle, SENIAL2);

			//if (encendido) {

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 0,
				TYPE_TEMPERATURE, UNIT_CELSIUS, temperatura);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 1,
				TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT, humedad);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 2,
				TYPE_BAROMETRIC_PRESSURE, UNIT_HECTOPASCAL, pressure);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 3,
				TYPE_ACELERACION_X, UNIT_mGRAVEDADES, accx_g);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 4,
				TYPE_ACELERACION_Y, UNIT_mGRAVEDADES, accy_g);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 5,
				TYPE_ACELERACION_Z, UNIT_mGRAVEDADES, accz_g);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 6,
				TYPE_GIROS_X, UNIT_mGRAVEDADES, gyrox_g);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 7,
				TYPE_GIROS_Y, UNIT_mGRAVEDADES, gyroy_g);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 8,
				TYPE_GIROS_Z, UNIT_mGRAVEDADES, gyroz_g);

				CayenneMQTTPublishDataInt(&mqttClient, NULL, DATA_TOPIC, 9,
				TYPE_MAGNETICO_X, UNIT_GAUSS, magx);

				CayenneMQTTPublishDataInt(&mqttClient, NULL, DATA_TOPIC, 10,
				TYPE_MAGNETICO_Y, UNIT_GAUSS, magy);

				CayenneMQTTPublishDataInt(&mqttClient, NULL, DATA_TOPIC, 11,
				TYPE_MAGNETICO_Z, UNIT_GAUSS, magz);

				CayenneMQTTPublishDataInt(&mqttClient, NULL, DATA_TOPIC, 12,
				TYPE_PROXIMITY, UNIT_CENTIMETER, distancia / 10);

				CayenneMQTTPublishDataInt(&mqttClient, NULL, DATA_TOPIC, 13,
				TYPE_NUMERO, UNIT_VECES, numeroDetecciones);

				CayenneMQTTPublishDataInt(&mqttClient, NULL, DATA_TOPIC, 14,
				TYPE_VOLUMEN, UNIT_VOLUMEN, volumenMicro);

				CayenneMQTTPublishDataInt(&mqttClient, NULL, DATA_TOPIC, 17,
				TYPE_NUMERO, UNIT_VECES, numeroPulsaciones);

				//printf("Publicados Datos en Zafron:\n");

				HAL_Delay(4000);

			//} else {

				/*CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 0,
				TYPE_TEMPERATURE, UNIT_CELSIUS, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 1,
				TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 2,
				TYPE_BAROMETRIC_PRESSURE, UNIT_HECTOPASCAL, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 3,
				TYPE_ACELERACION, UNIT_mGRAVEDADES, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 4,
				TYPE_ACELERACION, UNIT_mGRAVEDADES, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 5,
				TYPE_ACELERACION, UNIT_mGRAVEDADES, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 6,
				TYPE_GIROS, UNIT_mGRAVEDADES, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 7,
				TYPE_GIROS, UNIT_mGRAVEDADES, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 8,
				TYPE_GIROS, UNIT_mGRAVEDADES, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 9,
				TYPE_MAGNETICO, UNIT_GAUSS, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 10,
				TYPE_MAGNETICO, UNIT_GAUSS, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 11,
				TYPE_MAGNETICO, UNIT_GAUSS, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 12,
				TYPE_PROXIMITY, UNIT_CENTIMETER, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 13,
				TYPE_NUMERO, UNIT_VECES, 0);

				CayenneMQTTPublishDataFloat(&mqttClient, NULL, DATA_TOPIC, 14,
				TYPE_VOLUMEN, UNIT_VOLUMEN, 0);

				CayenneMQTTPublishDataInt(&mqttClient, NULL, DATA_TOPIC, 17,
				TYPE_NUMERO, UNIT_VECES, 0);

				HAL_Delay(5000);

			}*/

		}
	}
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartRepresentacion */
/**
 * @brief Function implementing the Representacion thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartRepresentacion */
void StartRepresentacion(void *argument)
{
  /* USER CODE BEGIN StartRepresentacion */
	uint32_t flags;

	/* Infinite loop */
	while (1) {

		flags = osThreadFlagsWait(SENIAL1, osFlagsWaitAny, osWaitForever);

		if (flags == SENIAL1) {

			printf("\n\n\r");

			printf("Temperatura: %.2f grados \n\r", temperatura);
			printf("Humedad: %.2f HR \n\r", humedad);
			printf("Presion: %.2f HPa \n\r", pressure);
			printf("Aceleracion en X: %.2f mG\n\r", accx_g);
			printf("Aceleracion en Y: %.2f mG\n\r", accy_g);
			printf("Aceleracion en Z: %.2f mG\n\r", accz_g);
			printf("Giro en X: %.2f mG\n\r", gyrox_g);
			printf("Giro en Y: %.2f mG\n\r", gyroy_g);
			printf("Giro en Z: %.2f mG\n\r", gyroz_g);
			printf("Magneto en X: %d Gauss\n\r", magx);
			printf("Magneto en Y: %d Gauss\n\r", magy);
			printf("Magneto en Z: %d Gauss\n\r", magz);
			printf("Distancia: %d cm\n\r", distancia / 10);
			printf("Detecciones NFC: %d veces\n\r", numeroDetecciones);
			printf("Volumen microfono: %d\n\r", volumenMicro);
			printf("Pulsaciones Joystick: %d veces\n\r", numeroPulsaciones);
			if (estadoLED == false){
				printf("Estado LED: Apagado\n\r");
			}else{
				printf("Estado LED: Encendido\n\r");
			}


			osThreadFlagsClear(SENIAL1);

		}
	}
  /* USER CODE END StartRepresentacion */
}

/* USER CODE BEGIN Header_StartMicrofono */
/**
 * @brief Function implementing the Microfono thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartMicrofono */
void StartMicrofono(void *argument)
{
  /* USER CODE BEGIN StartMicrofono */
	uint32_t flags;
	int i;
	int max_val = 0;

	/* Infinite loop */
	while (1) {

		flags = osThreadFlagsWait(SENIAL2, osFlagsWaitAny, osWaitForever);

		if (flags == SENIAL2) {

			if (DmaRecHalfBuffCplt == 1) {
				 //Store values on Play buff
				for (i = 0; i < 1024; i++) {
					PlayBuff[2 * i] = SaturaLH((RecBuff[i] >> 8), -32768, 32767);
					PlayBuff[(2 * i) + 1] = PlayBuff[2 * i];
				}

				PlaybackStarted = 1;
				DmaRecHalfBuffCplt = 0;
			}
			if (DmaRecBuffCplt == 1) {
				 //Store values on Play buff
				for (i = 1024; i < 2048; i++) {
					PlayBuff[2 * i] = SaturaLH((RecBuff[i] >> 8), -32768, 32767);
					PlayBuff[(2 * i) + 1] = PlayBuff[2 * i];
				}
				DmaRecBuffCplt = 0;

				for (int j = 0; j < 4096; j++) {

					if (PlayBuff[j] > max_val) {
						max_val = PlayBuff[j];
					}
				}
			}

			volumenMicrofono(max_val);
			max_val = 0;


			osThreadFlagsClear(SENIAL2);
		}
	}
  /* USER CODE END StartMicrofono */
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
	while (1) {
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
