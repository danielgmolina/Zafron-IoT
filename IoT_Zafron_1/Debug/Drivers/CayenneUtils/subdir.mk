################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CayenneUtils/CayenneDataArray.c \
../Drivers/CayenneUtils/CayenneUtils.c 

OBJS += \
./Drivers/CayenneUtils/CayenneDataArray.o \
./Drivers/CayenneUtils/CayenneUtils.o 

C_DEPS += \
./Drivers/CayenneUtils/CayenneDataArray.d \
./Drivers/CayenneUtils/CayenneUtils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CayenneUtils/%.o Drivers/CayenneUtils/%.su Drivers/CayenneUtils/%.cyclo: ../Drivers/CayenneUtils/%.c Drivers/CayenneUtils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' -DUSE_WIFI -DSENSOR -DENABLE_IOT_INFO -DGENERICMQTT -DENABLE_IOT_WARNING -DUSE_MBED_TLS -DENABLE_IOT_ERROR -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Drivers/CayenneUtils -I"../Drivers/CMSIS/Include" -I"../Drivers/Components/Common" -I"../Drivers/Components/cs43l22" -I"../Drivers/Components/m24sr" -I"../Drivers/Components/vl53l0x" -I"../Drivers/GenericMQTT" -I"../Drivers/STM32L4xx_HAL_Driver/Inc" -I"../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"../Drivers/STM32L4xx_HAL_Driver/Src" -I"../Drivers/Wifi" -I"../Middlewares/Third_Party/cJSON" -I"../Middlewares/Third_Party/FreeRTOS/Source" -I"../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"../Middlewares/Third_Party/FreeRTOS/Source/include" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang" -I"../Middlewares/Third_Party/MbedTLS" -I"../Middlewares/Third_Party/MbedTLS/mbedtls" -I"../Middlewares/Third_Party/MQTTClient-C" -I"../Middlewares/Third_Party/MQTTPacket" -I"../Core/Inc" -I"../Core/Src" -I"../Core/Startup" -O0 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CayenneUtils

clean-Drivers-2f-CayenneUtils:
	-$(RM) ./Drivers/CayenneUtils/CayenneDataArray.cyclo ./Drivers/CayenneUtils/CayenneDataArray.d ./Drivers/CayenneUtils/CayenneDataArray.o ./Drivers/CayenneUtils/CayenneDataArray.su ./Drivers/CayenneUtils/CayenneUtils.cyclo ./Drivers/CayenneUtils/CayenneUtils.d ./Drivers/CayenneUtils/CayenneUtils.o ./Drivers/CayenneUtils/CayenneUtils.su

.PHONY: clean-Drivers-2f-CayenneUtils

