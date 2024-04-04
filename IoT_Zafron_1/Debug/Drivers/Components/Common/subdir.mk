################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/Common/STM32CubeRTCInterface.c \
../Drivers/Components/Common/cloud.c \
../Drivers/Components/Common/entropy_hardware_poll.c \
../Drivers/Components/Common/flash_l4.c \
../Drivers/Components/Common/heap.c \
../Drivers/Components/Common/http_util.c \
../Drivers/Components/Common/iot_flash_config.c \
../Drivers/Components/Common/mbedtls_net.c \
../Drivers/Components/Common/net.c \
../Drivers/Components/Common/net_tcp_wifi.c \
../Drivers/Components/Common/net_tls_mbedtls.c \
../Drivers/Components/Common/paho_timer.c \
../Drivers/Components/Common/rfu.c \
../Drivers/Components/Common/sensors_data.c \
../Drivers/Components/Common/stm32l475e_iot01.c \
../Drivers/Components/Common/stm32l475e_iot01_accelero.c \
../Drivers/Components/Common/stm32l475e_iot01_gyro.c \
../Drivers/Components/Common/stm32l475e_iot01_hsensor.c \
../Drivers/Components/Common/stm32l475e_iot01_magneto.c \
../Drivers/Components/Common/stm32l475e_iot01_psensor.c \
../Drivers/Components/Common/stm32l475e_iot01_tsensor.c \
../Drivers/Components/Common/timedate.c \
../Drivers/Components/Common/timingSystem.c \
../Drivers/Components/Common/wifi_net.c 

OBJS += \
./Drivers/Components/Common/STM32CubeRTCInterface.o \
./Drivers/Components/Common/cloud.o \
./Drivers/Components/Common/entropy_hardware_poll.o \
./Drivers/Components/Common/flash_l4.o \
./Drivers/Components/Common/heap.o \
./Drivers/Components/Common/http_util.o \
./Drivers/Components/Common/iot_flash_config.o \
./Drivers/Components/Common/mbedtls_net.o \
./Drivers/Components/Common/net.o \
./Drivers/Components/Common/net_tcp_wifi.o \
./Drivers/Components/Common/net_tls_mbedtls.o \
./Drivers/Components/Common/paho_timer.o \
./Drivers/Components/Common/rfu.o \
./Drivers/Components/Common/sensors_data.o \
./Drivers/Components/Common/stm32l475e_iot01.o \
./Drivers/Components/Common/stm32l475e_iot01_accelero.o \
./Drivers/Components/Common/stm32l475e_iot01_gyro.o \
./Drivers/Components/Common/stm32l475e_iot01_hsensor.o \
./Drivers/Components/Common/stm32l475e_iot01_magneto.o \
./Drivers/Components/Common/stm32l475e_iot01_psensor.o \
./Drivers/Components/Common/stm32l475e_iot01_tsensor.o \
./Drivers/Components/Common/timedate.o \
./Drivers/Components/Common/timingSystem.o \
./Drivers/Components/Common/wifi_net.o 

C_DEPS += \
./Drivers/Components/Common/STM32CubeRTCInterface.d \
./Drivers/Components/Common/cloud.d \
./Drivers/Components/Common/entropy_hardware_poll.d \
./Drivers/Components/Common/flash_l4.d \
./Drivers/Components/Common/heap.d \
./Drivers/Components/Common/http_util.d \
./Drivers/Components/Common/iot_flash_config.d \
./Drivers/Components/Common/mbedtls_net.d \
./Drivers/Components/Common/net.d \
./Drivers/Components/Common/net_tcp_wifi.d \
./Drivers/Components/Common/net_tls_mbedtls.d \
./Drivers/Components/Common/paho_timer.d \
./Drivers/Components/Common/rfu.d \
./Drivers/Components/Common/sensors_data.d \
./Drivers/Components/Common/stm32l475e_iot01.d \
./Drivers/Components/Common/stm32l475e_iot01_accelero.d \
./Drivers/Components/Common/stm32l475e_iot01_gyro.d \
./Drivers/Components/Common/stm32l475e_iot01_hsensor.d \
./Drivers/Components/Common/stm32l475e_iot01_magneto.d \
./Drivers/Components/Common/stm32l475e_iot01_psensor.d \
./Drivers/Components/Common/stm32l475e_iot01_tsensor.d \
./Drivers/Components/Common/timedate.d \
./Drivers/Components/Common/timingSystem.d \
./Drivers/Components/Common/wifi_net.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/Common/%.o Drivers/Components/Common/%.su Drivers/Components/Common/%.cyclo: ../Drivers/Components/Common/%.c Drivers/Components/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' -DUSE_WIFI -DSENSOR -DENABLE_IOT_INFO -DGENERICMQTT -DENABLE_IOT_WARNING -DUSE_MBED_TLS -DENABLE_IOT_ERROR -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Drivers/CayenneUtils -I"../Drivers/CMSIS/Include" -I"../Drivers/Components/Common" -I"../Drivers/Components/cs43l22" -I"../Drivers/Components/m24sr" -I"../Drivers/Components/vl53l0x" -I"../Drivers/GenericMQTT" -I"../Drivers/STM32L4xx_HAL_Driver/Inc" -I"../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"../Drivers/STM32L4xx_HAL_Driver/Src" -I"../Drivers/Wifi" -I"../Middlewares/Third_Party/cJSON" -I"../Middlewares/Third_Party/FreeRTOS/Source" -I"../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"../Middlewares/Third_Party/FreeRTOS/Source/include" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang" -I"../Middlewares/Third_Party/MbedTLS" -I"../Middlewares/Third_Party/MbedTLS/mbedtls" -I"../Middlewares/Third_Party/MQTTClient-C" -I"../Middlewares/Third_Party/MQTTPacket" -I"../Core/Inc" -I"../Core/Src" -I"../Core/Startup" -O0 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Components-2f-Common

clean-Drivers-2f-Components-2f-Common:
	-$(RM) ./Drivers/Components/Common/STM32CubeRTCInterface.cyclo ./Drivers/Components/Common/STM32CubeRTCInterface.d ./Drivers/Components/Common/STM32CubeRTCInterface.o ./Drivers/Components/Common/STM32CubeRTCInterface.su ./Drivers/Components/Common/cloud.cyclo ./Drivers/Components/Common/cloud.d ./Drivers/Components/Common/cloud.o ./Drivers/Components/Common/cloud.su ./Drivers/Components/Common/entropy_hardware_poll.cyclo ./Drivers/Components/Common/entropy_hardware_poll.d ./Drivers/Components/Common/entropy_hardware_poll.o ./Drivers/Components/Common/entropy_hardware_poll.su ./Drivers/Components/Common/flash_l4.cyclo ./Drivers/Components/Common/flash_l4.d ./Drivers/Components/Common/flash_l4.o ./Drivers/Components/Common/flash_l4.su ./Drivers/Components/Common/heap.cyclo ./Drivers/Components/Common/heap.d ./Drivers/Components/Common/heap.o ./Drivers/Components/Common/heap.su ./Drivers/Components/Common/http_util.cyclo ./Drivers/Components/Common/http_util.d ./Drivers/Components/Common/http_util.o ./Drivers/Components/Common/http_util.su ./Drivers/Components/Common/iot_flash_config.cyclo ./Drivers/Components/Common/iot_flash_config.d ./Drivers/Components/Common/iot_flash_config.o ./Drivers/Components/Common/iot_flash_config.su ./Drivers/Components/Common/mbedtls_net.cyclo ./Drivers/Components/Common/mbedtls_net.d ./Drivers/Components/Common/mbedtls_net.o ./Drivers/Components/Common/mbedtls_net.su ./Drivers/Components/Common/net.cyclo ./Drivers/Components/Common/net.d ./Drivers/Components/Common/net.o ./Drivers/Components/Common/net.su ./Drivers/Components/Common/net_tcp_wifi.cyclo ./Drivers/Components/Common/net_tcp_wifi.d ./Drivers/Components/Common/net_tcp_wifi.o ./Drivers/Components/Common/net_tcp_wifi.su ./Drivers/Components/Common/net_tls_mbedtls.cyclo ./Drivers/Components/Common/net_tls_mbedtls.d ./Drivers/Components/Common/net_tls_mbedtls.o ./Drivers/Components/Common/net_tls_mbedtls.su ./Drivers/Components/Common/paho_timer.cyclo ./Drivers/Components/Common/paho_timer.d ./Drivers/Components/Common/paho_timer.o ./Drivers/Components/Common/paho_timer.su ./Drivers/Components/Common/rfu.cyclo ./Drivers/Components/Common/rfu.d ./Drivers/Components/Common/rfu.o ./Drivers/Components/Common/rfu.su ./Drivers/Components/Common/sensors_data.cyclo ./Drivers/Components/Common/sensors_data.d ./Drivers/Components/Common/sensors_data.o ./Drivers/Components/Common/sensors_data.su ./Drivers/Components/Common/stm32l475e_iot01.cyclo ./Drivers/Components/Common/stm32l475e_iot01.d ./Drivers/Components/Common/stm32l475e_iot01.o ./Drivers/Components/Common/stm32l475e_iot01.su ./Drivers/Components/Common/stm32l475e_iot01_accelero.cyclo ./Drivers/Components/Common/stm32l475e_iot01_accelero.d ./Drivers/Components/Common/stm32l475e_iot01_accelero.o ./Drivers/Components/Common/stm32l475e_iot01_accelero.su ./Drivers/Components/Common/stm32l475e_iot01_gyro.cyclo ./Drivers/Components/Common/stm32l475e_iot01_gyro.d ./Drivers/Components/Common/stm32l475e_iot01_gyro.o ./Drivers/Components/Common/stm32l475e_iot01_gyro.su ./Drivers/Components/Common/stm32l475e_iot01_hsensor.cyclo ./Drivers/Components/Common/stm32l475e_iot01_hsensor.d ./Drivers/Components/Common/stm32l475e_iot01_hsensor.o ./Drivers/Components/Common/stm32l475e_iot01_hsensor.su ./Drivers/Components/Common/stm32l475e_iot01_magneto.cyclo ./Drivers/Components/Common/stm32l475e_iot01_magneto.d ./Drivers/Components/Common/stm32l475e_iot01_magneto.o ./Drivers/Components/Common/stm32l475e_iot01_magneto.su ./Drivers/Components/Common/stm32l475e_iot01_psensor.cyclo ./Drivers/Components/Common/stm32l475e_iot01_psensor.d ./Drivers/Components/Common/stm32l475e_iot01_psensor.o ./Drivers/Components/Common/stm32l475e_iot01_psensor.su ./Drivers/Components/Common/stm32l475e_iot01_tsensor.cyclo ./Drivers/Components/Common/stm32l475e_iot01_tsensor.d ./Drivers/Components/Common/stm32l475e_iot01_tsensor.o ./Drivers/Components/Common/stm32l475e_iot01_tsensor.su ./Drivers/Components/Common/timedate.cyclo ./Drivers/Components/Common/timedate.d ./Drivers/Components/Common/timedate.o ./Drivers/Components/Common/timedate.su ./Drivers/Components/Common/timingSystem.cyclo ./Drivers/Components/Common/timingSystem.d ./Drivers/Components/Common/timingSystem.o ./Drivers/Components/Common/timingSystem.su ./Drivers/Components/Common/wifi_net.cyclo ./Drivers/Components/Common/wifi_net.d ./Drivers/Components/Common/wifi_net.o ./Drivers/Components/Common/wifi_net.su

.PHONY: clean-Drivers-2f-Components-2f-Common

