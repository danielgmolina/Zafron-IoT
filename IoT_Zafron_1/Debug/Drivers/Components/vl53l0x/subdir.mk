################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/vl53l0x/vl53l0x_api.c \
../Drivers/Components/vl53l0x/vl53l0x_api_calibration.c \
../Drivers/Components/vl53l0x/vl53l0x_api_core.c \
../Drivers/Components/vl53l0x/vl53l0x_api_ranging.c \
../Drivers/Components/vl53l0x/vl53l0x_api_strings.c \
../Drivers/Components/vl53l0x/vl53l0x_platform_log.c \
../Drivers/Components/vl53l0x/vl53l0x_tof.c 

OBJS += \
./Drivers/Components/vl53l0x/vl53l0x_api.o \
./Drivers/Components/vl53l0x/vl53l0x_api_calibration.o \
./Drivers/Components/vl53l0x/vl53l0x_api_core.o \
./Drivers/Components/vl53l0x/vl53l0x_api_ranging.o \
./Drivers/Components/vl53l0x/vl53l0x_api_strings.o \
./Drivers/Components/vl53l0x/vl53l0x_platform_log.o \
./Drivers/Components/vl53l0x/vl53l0x_tof.o 

C_DEPS += \
./Drivers/Components/vl53l0x/vl53l0x_api.d \
./Drivers/Components/vl53l0x/vl53l0x_api_calibration.d \
./Drivers/Components/vl53l0x/vl53l0x_api_core.d \
./Drivers/Components/vl53l0x/vl53l0x_api_ranging.d \
./Drivers/Components/vl53l0x/vl53l0x_api_strings.d \
./Drivers/Components/vl53l0x/vl53l0x_platform_log.d \
./Drivers/Components/vl53l0x/vl53l0x_tof.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/vl53l0x/%.o Drivers/Components/vl53l0x/%.su Drivers/Components/vl53l0x/%.cyclo: ../Drivers/Components/vl53l0x/%.c Drivers/Components/vl53l0x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' -DUSE_WIFI -DSENSOR -DENABLE_IOT_INFO -DGENERICMQTT -DENABLE_IOT_WARNING -DUSE_MBED_TLS -DENABLE_IOT_ERROR -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Drivers/CayenneUtils -I"../Drivers/CMSIS/Include" -I"../Drivers/Components/Common" -I"../Drivers/Components/cs43l22" -I"../Drivers/Components/m24sr" -I"../Drivers/Components/vl53l0x" -I"../Drivers/GenericMQTT" -I"../Drivers/STM32L4xx_HAL_Driver/Inc" -I"../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"../Drivers/STM32L4xx_HAL_Driver/Src" -I"../Drivers/Wifi" -I"../Middlewares/Third_Party/cJSON" -I"../Middlewares/Third_Party/FreeRTOS/Source" -I"../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"../Middlewares/Third_Party/FreeRTOS/Source/include" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang" -I"../Middlewares/Third_Party/MbedTLS" -I"../Middlewares/Third_Party/MbedTLS/mbedtls" -I"../Middlewares/Third_Party/MQTTClient-C" -I"../Middlewares/Third_Party/MQTTPacket" -I"../Core/Inc" -I"../Core/Src" -I"../Core/Startup" -O0 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Components-2f-vl53l0x

clean-Drivers-2f-Components-2f-vl53l0x:
	-$(RM) ./Drivers/Components/vl53l0x/vl53l0x_api.cyclo ./Drivers/Components/vl53l0x/vl53l0x_api.d ./Drivers/Components/vl53l0x/vl53l0x_api.o ./Drivers/Components/vl53l0x/vl53l0x_api.su ./Drivers/Components/vl53l0x/vl53l0x_api_calibration.cyclo ./Drivers/Components/vl53l0x/vl53l0x_api_calibration.d ./Drivers/Components/vl53l0x/vl53l0x_api_calibration.o ./Drivers/Components/vl53l0x/vl53l0x_api_calibration.su ./Drivers/Components/vl53l0x/vl53l0x_api_core.cyclo ./Drivers/Components/vl53l0x/vl53l0x_api_core.d ./Drivers/Components/vl53l0x/vl53l0x_api_core.o ./Drivers/Components/vl53l0x/vl53l0x_api_core.su ./Drivers/Components/vl53l0x/vl53l0x_api_ranging.cyclo ./Drivers/Components/vl53l0x/vl53l0x_api_ranging.d ./Drivers/Components/vl53l0x/vl53l0x_api_ranging.o ./Drivers/Components/vl53l0x/vl53l0x_api_ranging.su ./Drivers/Components/vl53l0x/vl53l0x_api_strings.cyclo ./Drivers/Components/vl53l0x/vl53l0x_api_strings.d ./Drivers/Components/vl53l0x/vl53l0x_api_strings.o ./Drivers/Components/vl53l0x/vl53l0x_api_strings.su ./Drivers/Components/vl53l0x/vl53l0x_platform_log.cyclo ./Drivers/Components/vl53l0x/vl53l0x_platform_log.d ./Drivers/Components/vl53l0x/vl53l0x_platform_log.o ./Drivers/Components/vl53l0x/vl53l0x_platform_log.su ./Drivers/Components/vl53l0x/vl53l0x_tof.cyclo ./Drivers/Components/vl53l0x/vl53l0x_tof.d ./Drivers/Components/vl53l0x/vl53l0x_tof.o ./Drivers/Components/vl53l0x/vl53l0x_tof.su

.PHONY: clean-Drivers-2f-Components-2f-vl53l0x

