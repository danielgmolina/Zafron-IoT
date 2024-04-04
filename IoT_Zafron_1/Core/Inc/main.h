/* USER CODE BEGIN Header */

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#ifdef RFU
#include "rfu.h"
#endif
#ifdef SENSOR

#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "net.h"
#include "flash.h"
#include "timedate.h"
#ifdef FIREWALL_MBEDLIB
#include "firewall_wrapper.h"
#include "firewall.h"
#endif /* FIREWALL_MBEDLIB */
#include "iot_flash_config.h"
#include "msg.h"
#include "cloud.h"
#include "sensors_data.h"
#include "version.h"

//#include "sensores.h"
#include "audio.h"
#include "cs43l22.h"
#include "m24sr.h"
#include "stm32l475e_iot01.h"

#include "temperatura.h"
#include "humedad.h"
#include "presion.h"
#include "acelerometro.h"
#include "giroscopio.h"
#include "magnetometro.h"
#include "microfono.h"
#include "tof.h"

#include "vl53l0x_def.h"
#include "vl53l0x_api.h"
#include "vl53l0x_tof.h"


#ifdef USE_MBED_TLS
extern int mbedtls_hardware_poll( void *data, unsigned char *output, size_t len, size_t *olen );
#endif /* USE_MBED_TLS */

#if defined(USE_WIFI)
#define NET_IF  NET_IF_WLAN
#elif defined(USE_LWIP)
#define NET_IF  NET_IF_ETH
#elif defined(USE_C2C)
#define NET_IF  NET_IF_C2C
#endif

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

void    Periph_Config(void);
extern  SPI_HandleTypeDef hspi;
extern RNG_HandleTypeDef hrng;
extern RTC_HandleTypeDef hrtc;
extern net_hnd_t         hnet;

extern I2C_HandleTypeDef hi2c2;


extern const user_config_t *lUserConfigPtr;
extern uint16_t numeroDetecciones;
extern uint16_t numeroPulsaciones;


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RED_LED_Pin GPIO_PIN_3
#define RED_LED_GPIO_Port GPIOE
#define ARD_A2_LEDON_Pin GPIO_PIN_3
#define ARD_A2_LEDON_GPIO_Port GPIOC
#define ARD_A1_LEDWIFI_Pin GPIO_PIN_4
#define ARD_A1_LEDWIFI_GPIO_Port GPIOC
#define ARD_A0_3_3CTRL_Pin GPIO_PIN_5
#define ARD_A0_3_3CTRL_GPIO_Port GPIOC
#define ISM43362_RST_Pin GPIO_PIN_8
#define ISM43362_RST_GPIO_Port GPIOE
#define INTERNAL_I2C2_SCL_Pin GPIO_PIN_10
#define INTERNAL_I2C2_SCL_GPIO_Port GPIOB
#define INTERNAL_I2C2_SDA_Pin GPIO_PIN_11
#define INTERNAL_I2C2_SDA_GPIO_Port GPIOB
#define ISM43362_BOOT0_Pin GPIO_PIN_12
#define ISM43362_BOOT0_GPIO_Port GPIOB
#define ISM43362_WAKEUP_Pin GPIO_PIN_13
#define ISM43362_WAKEUP_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_14
#define LED2_GPIO_Port GPIOB
#define LED3_WIFI__LED4_BLE_Pin GPIO_PIN_9
#define LED3_WIFI__LED4_BLE_GPIO_Port GPIOC
#define SYS_JTMS_SWDIO_Pin GPIO_PIN_13
#define SYS_JTMS_SWDIO_GPIO_Port GPIOA
#define SYS_JTCK_SWCLK_Pin GPIO_PIN_14
#define SYS_JTCK_SWCLK_GPIO_Port GPIOA
#define INTERNAL_SPI3_SCK_Pin GPIO_PIN_10
#define INTERNAL_SPI3_SCK_GPIO_Port GPIOC
#define INTERNAL_SPI3_MISO_Pin GPIO_PIN_11
#define INTERNAL_SPI3_MISO_GPIO_Port GPIOC
#define INTERNAL_SPI3_MOSI_Pin GPIO_PIN_12
#define INTERNAL_SPI3_MOSI_GPIO_Port GPIOC
#define STSAFE_A100_RESET_Pin GPIO_PIN_7
#define STSAFE_A100_RESET_GPIO_Port GPIOD
#define SYS_JTD0_SWO_Pin GPIO_PIN_3
#define SYS_JTD0_SWO_GPIO_Port GPIOB
#define ST_LINK_UART1_TX_Pin GPIO_PIN_6
#define ST_LINK_UART1_TX_GPIO_Port GPIOB
#define ST_LINK_UART1_RX_Pin GPIO_PIN_7
#define ST_LINK_UART1_RX_GPIO_Port GPIOB
#define ISM43362_SPI3_CSN_Pin GPIO_PIN_0
#define ISM43362_SPI3_CSN_GPIO_Port GPIOE
#define ISM43362_DRDY_EXTI1_Pin GPIO_PIN_1
#define ISM43362_DRDY_EXTI1_GPIO_Port GPIOE
#define ISM43362_DRDY_EXTI1_EXTI_IRQn EXTI1_IRQn

/* USER CODE BEGIN Private defines */

#define TRANSISTOR_2_Pin GPIO_PIN_3
#define TRANSISTOR_2_GPIO_Port GPIOA
#define RD_A1_LEDWIFI_Pin GPIO_PIN_4
#define RD_A1_LEDWIFI_GPIO_Port GPIOC
#define ISM43362_RST_Pin GPIO_PIN_8
#define ISM43362_RST_GPIO_Port GPIOE
#define ISM43362_BOOT0_Pin GPIO_PIN_12
#define ISM43362_BOOT0_GPIO_Port GPIOB
#define ISM43362_WAKEUP_Pin GPIO_PIN_13
#define ISM43362_WAKEUP_GPIO_Port GPIOB
#define TRANSISTOR_1_Pin GPIO_PIN_14
#define TRANSISTOR_1_GPIO_Port GPIOD
#define LED3_WIFI_Pin GPIO_PIN_9
#define LED3_WIFI_GPIO_Port GPIOC
#define ISM43362_SSN_Pin GPIO_PIN_0
#define ISM43362_SSN_GPIO_Port GPIOE
#define ISM43362_DATAREADY_Pin GPIO_PIN_1
#define ISM43362_DATAREADY_GPIO_Port GPIOE
#define ISM43362_DATAREADY_EXTI_IRQn EXTI1_IRQn


#define CREDENCIALES_SERV_IOT     "0"

#define MI_SSID_WIFI  "iPhoneDani"
#define MI_PSWRD_WIFI "dani1234"
#define MI_SCRTYLVL  WIFI_ECN_WPA2_PSK
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
