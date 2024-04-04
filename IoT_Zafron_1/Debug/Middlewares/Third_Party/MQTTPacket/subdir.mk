################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.c \
../Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.c \
../Middlewares/Third_Party/MQTTPacket/MQTTFormat.c \
../Middlewares/Third_Party/MQTTPacket/MQTTPacket.c \
../Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.c \
../Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.c \
../Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.c 

OBJS += \
./Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.o \
./Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.o \
./Middlewares/Third_Party/MQTTPacket/MQTTFormat.o \
./Middlewares/Third_Party/MQTTPacket/MQTTPacket.o \
./Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.o \
./Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.o \
./Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.o 

C_DEPS += \
./Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.d \
./Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.d \
./Middlewares/Third_Party/MQTTPacket/MQTTFormat.d \
./Middlewares/Third_Party/MQTTPacket/MQTTPacket.d \
./Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.d \
./Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.d \
./Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/MQTTPacket/%.o Middlewares/Third_Party/MQTTPacket/%.su Middlewares/Third_Party/MQTTPacket/%.cyclo: ../Middlewares/Third_Party/MQTTPacket/%.c Middlewares/Third_Party/MQTTPacket/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' -DUSE_WIFI -DSENSOR -DENABLE_IOT_INFO -DGENERICMQTT -DENABLE_IOT_WARNING -DUSE_MBED_TLS -DENABLE_IOT_ERROR -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Drivers/CayenneUtils -I"../Drivers/CMSIS/Include" -I"../Drivers/Components/Common" -I"../Drivers/Components/cs43l22" -I"../Drivers/Components/m24sr" -I"../Drivers/Components/vl53l0x" -I"../Drivers/GenericMQTT" -I"../Drivers/STM32L4xx_HAL_Driver/Inc" -I"../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"../Drivers/STM32L4xx_HAL_Driver/Src" -I"../Drivers/Wifi" -I"../Middlewares/Third_Party/cJSON" -I"../Middlewares/Third_Party/FreeRTOS/Source" -I"../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"../Middlewares/Third_Party/FreeRTOS/Source/include" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang" -I"../Middlewares/Third_Party/MbedTLS" -I"../Middlewares/Third_Party/MbedTLS/mbedtls" -I"../Middlewares/Third_Party/MQTTClient-C" -I"../Middlewares/Third_Party/MQTTPacket" -I"../Core/Inc" -I"../Core/Src" -I"../Core/Startup" -O0 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-MQTTPacket

clean-Middlewares-2f-Third_Party-2f-MQTTPacket:
	-$(RM) ./Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.cyclo ./Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.d ./Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.o ./Middlewares/Third_Party/MQTTPacket/MQTTConnectClient.su ./Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.cyclo ./Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.d ./Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.o ./Middlewares/Third_Party/MQTTPacket/MQTTDeserializePublish.su ./Middlewares/Third_Party/MQTTPacket/MQTTFormat.cyclo ./Middlewares/Third_Party/MQTTPacket/MQTTFormat.d ./Middlewares/Third_Party/MQTTPacket/MQTTFormat.o ./Middlewares/Third_Party/MQTTPacket/MQTTFormat.su ./Middlewares/Third_Party/MQTTPacket/MQTTPacket.cyclo ./Middlewares/Third_Party/MQTTPacket/MQTTPacket.d ./Middlewares/Third_Party/MQTTPacket/MQTTPacket.o ./Middlewares/Third_Party/MQTTPacket/MQTTPacket.su ./Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.cyclo ./Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.d ./Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.o ./Middlewares/Third_Party/MQTTPacket/MQTTSerializePublish.su ./Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.cyclo ./Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.d ./Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.o ./Middlewares/Third_Party/MQTTPacket/MQTTSubscribeClient.su ./Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.cyclo ./Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.d ./Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.o ./Middlewares/Third_Party/MQTTPacket/MQTTUnsubscribeClient.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-MQTTPacket

