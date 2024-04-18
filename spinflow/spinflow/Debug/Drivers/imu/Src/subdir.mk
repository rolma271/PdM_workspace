################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/imu/Src/imu_api.c \
../Drivers/imu/Src/imu_port.c 

OBJS += \
./Drivers/imu/Src/imu_api.o \
./Drivers/imu/Src/imu_port.o 

C_DEPS += \
./Drivers/imu/Src/imu_api.d \
./Drivers/imu/Src/imu_port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/imu/Src/%.o Drivers/imu/Src/%.su Drivers/imu/Src/%.cyclo: ../Drivers/imu/Src/%.c Drivers/imu/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/neopixels/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/imu/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/BSP/STM32F4xx_Nucleo_144/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/delay/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/log/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-imu-2f-Src

clean-Drivers-2f-imu-2f-Src:
	-$(RM) ./Drivers/imu/Src/imu_api.cyclo ./Drivers/imu/Src/imu_api.d ./Drivers/imu/Src/imu_api.o ./Drivers/imu/Src/imu_api.su ./Drivers/imu/Src/imu_port.cyclo ./Drivers/imu/Src/imu_port.d ./Drivers/imu/Src/imu_port.o ./Drivers/imu/Src/imu_port.su

.PHONY: clean-Drivers-2f-imu-2f-Src

