################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/acelerometro.c \
../Core/Src/freertos.c \
../Core/Src/giroscopio.c \
../Core/Src/humedad.c \
../Core/Src/magnetometro.c \
../Core/Src/main.c \
../Core/Src/microfono.c \
../Core/Src/presion.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/temperatura.c \
../Core/Src/tof.c 

OBJS += \
./Core/Src/acelerometro.o \
./Core/Src/freertos.o \
./Core/Src/giroscopio.o \
./Core/Src/humedad.o \
./Core/Src/magnetometro.o \
./Core/Src/main.o \
./Core/Src/microfono.o \
./Core/Src/presion.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/temperatura.o \
./Core/Src/tof.o 

C_DEPS += \
./Core/Src/acelerometro.d \
./Core/Src/freertos.d \
./Core/Src/giroscopio.d \
./Core/Src/humedad.d \
./Core/Src/magnetometro.d \
./Core/Src/main.d \
./Core/Src/microfono.d \
./Core/Src/presion.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/temperatura.d \
./Core/Src/tof.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG '-DMQTTCLIENT_PLATFORM_HEADER=paho_mqtt_platform.h' '-DMBEDTLS_CONFIG_FILE=<genmqtt_mbedtls_config.h>' -DUSE_WIFI -DSENSOR -DENABLE_IOT_INFO -DGENERICMQTT -DENABLE_IOT_WARNING -DUSE_MBED_TLS -DENABLE_IOT_ERROR -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Drivers/CayenneUtils -I"../Drivers/CMSIS/Include" -I"../Drivers/Components/Common" -I"../Drivers/Components/cs43l22" -I"../Drivers/Components/m24sr" -I"../Drivers/Components/vl53l0x" -I"../Drivers/GenericMQTT" -I"../Drivers/STM32L4xx_HAL_Driver/Inc" -I"../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy" -I"../Drivers/STM32L4xx_HAL_Driver/Src" -I"../Drivers/Wifi" -I"../Middlewares/Third_Party/cJSON" -I"../Middlewares/Third_Party/FreeRTOS/Source" -I"../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"../Middlewares/Third_Party/FreeRTOS/Source/include" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang" -I"../Middlewares/Third_Party/MbedTLS" -I"../Middlewares/Third_Party/MbedTLS/mbedtls" -I"../Middlewares/Third_Party/MQTTClient-C" -I"../Middlewares/Third_Party/MQTTPacket" -I"../Core/Inc" -I"../Core/Src" -I"../Core/Startup" -O0 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/acelerometro.cyclo ./Core/Src/acelerometro.d ./Core/Src/acelerometro.o ./Core/Src/acelerometro.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/giroscopio.cyclo ./Core/Src/giroscopio.d ./Core/Src/giroscopio.o ./Core/Src/giroscopio.su ./Core/Src/humedad.cyclo ./Core/Src/humedad.d ./Core/Src/humedad.o ./Core/Src/humedad.su ./Core/Src/magnetometro.cyclo ./Core/Src/magnetometro.d ./Core/Src/magnetometro.o ./Core/Src/magnetometro.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/microfono.cyclo ./Core/Src/microfono.d ./Core/Src/microfono.o ./Core/Src/microfono.su ./Core/Src/presion.cyclo ./Core/Src/presion.d ./Core/Src/presion.o ./Core/Src/presion.su ./Core/Src/stm32l4xx_hal_msp.cyclo ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.cyclo ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su ./Core/Src/temperatura.cyclo ./Core/Src/temperatura.d ./Core/Src/temperatura.o ./Core/Src/temperatura.su ./Core/Src/tof.cyclo ./Core/Src/tof.d ./Core/Src/tof.o ./Core/Src/tof.su

.PHONY: clean-Core-2f-Src

