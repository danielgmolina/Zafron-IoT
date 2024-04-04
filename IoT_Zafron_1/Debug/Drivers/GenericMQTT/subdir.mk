################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/GenericMQTT/CayenneMQTTClient.c 

OBJS += \
./Drivers/GenericMQTT/CayenneMQTTClient.o 

C_DEPS += \
./Drivers/GenericMQTT/CayenneMQTTClient.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/GenericMQTT/%.o Drivers/GenericMQTT/%.su Drivers/GenericMQTT/%.cyclo: ../Drivers/GenericMQTT/%.c Drivers/GenericMQTT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' -DUSE_WIFI -DSENSOR -DENABLE_IOT_INFO -DGENERICMQTT -DENABLE_IOT_WARNING -DUSE_MBED_TLS -DENABLE_IOT_ERROR -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Middlewares/Third_Party/MQTTPacket -I../Drivers/Components/Common -I../Middlewares/Third_Party/MQTTClient-C -I../Middlewares/Third_Party/MbedTLS -I../Middlewares/Third_Party/cJSON -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-GenericMQTT

clean-Drivers-2f-GenericMQTT:
	-$(RM) ./Drivers/GenericMQTT/CayenneMQTTClient.cyclo ./Drivers/GenericMQTT/CayenneMQTTClient.d ./Drivers/GenericMQTT/CayenneMQTTClient.o ./Drivers/GenericMQTT/CayenneMQTTClient.su

.PHONY: clean-Drivers-2f-GenericMQTT

