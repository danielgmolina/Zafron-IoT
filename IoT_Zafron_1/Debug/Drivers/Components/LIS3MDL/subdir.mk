################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Components/LIS3MDL/lis3mdl.c 

OBJS += \
./Drivers/Components/LIS3MDL/lis3mdl.o 

C_DEPS += \
./Drivers/Components/LIS3MDL/lis3mdl.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Components/LIS3MDL/%.o Drivers/Components/LIS3MDL/%.su Drivers/Components/LIS3MDL/%.cyclo: ../Drivers/Components/LIS3MDL/%.c Drivers/Components/LIS3MDL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' -DUSE_WIFI -DSENSOR -DENABLE_IOT_INFO -DGENERICMQTT -DENABLE_IOT_WARNING -DUSE_MBED_TLS -DENABLE_IOT_ERROR -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Drivers/CayenneUtils -I"../Drivers/CMSIS/Include" -I"../Drivers/Components/Common" -I"../Drivers/Components/cs43l22" -I"../Drivers/Components/m24sr" -I"../Drivers/Components/vl53l0x" -I"../Drivers/GenericMQTT" -I"../Drivers/STM32L4xx_HAL_Driver/Inc" -I"../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"../Drivers/STM32L4xx_HAL_Driver/Src" -I"../Drivers/Wifi" -I"../Middlewares/Third_Party/cJSON" -I"../Middlewares/Third_Party/FreeRTOS/Source" -I"../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"../Middlewares/Third_Party/FreeRTOS/Source/include" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang" -I"../Middlewares/Third_Party/MbedTLS" -I"../Middlewares/Third_Party/MbedTLS/mbedtls" -I"../Middlewares/Third_Party/MQTTClient-C" -I"../Middlewares/Third_Party/MQTTPacket" -I"../Core/Inc" -I"../Core/Src" -I"../Core/Startup" -O0 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Components-2f-LIS3MDL

clean-Drivers-2f-Components-2f-LIS3MDL:
	-$(RM) ./Drivers/Components/LIS3MDL/lis3mdl.cyclo ./Drivers/Components/LIS3MDL/lis3mdl.d ./Drivers/Components/LIS3MDL/lis3mdl.o ./Drivers/Components/LIS3MDL/lis3mdl.su

.PHONY: clean-Drivers-2f-Components-2f-LIS3MDL

