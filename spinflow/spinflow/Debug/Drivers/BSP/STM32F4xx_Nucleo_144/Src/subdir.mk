################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32F4xx_Nucleo_144/Src/stm32f4xx_nucleo_144.c 

OBJS += \
./Drivers/BSP/STM32F4xx_Nucleo_144/Src/stm32f4xx_nucleo_144.o 

C_DEPS += \
./Drivers/BSP/STM32F4xx_Nucleo_144/Src/stm32f4xx_nucleo_144.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32F4xx_Nucleo_144/Src/%.o Drivers/BSP/STM32F4xx_Nucleo_144/Src/%.su Drivers/BSP/STM32F4xx_Nucleo_144/Src/%.cyclo: ../Drivers/BSP/STM32F4xx_Nucleo_144/Src/%.c Drivers/BSP/STM32F4xx_Nucleo_144/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/neopixels/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/imu/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/BSP/STM32F4xx_Nucleo_144/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/delay/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/log/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32F4xx_Nucleo_144-2f-Src

clean-Drivers-2f-BSP-2f-STM32F4xx_Nucleo_144-2f-Src:
	-$(RM) ./Drivers/BSP/STM32F4xx_Nucleo_144/Src/stm32f4xx_nucleo_144.cyclo ./Drivers/BSP/STM32F4xx_Nucleo_144/Src/stm32f4xx_nucleo_144.d ./Drivers/BSP/STM32F4xx_Nucleo_144/Src/stm32f4xx_nucleo_144.o ./Drivers/BSP/STM32F4xx_Nucleo_144/Src/stm32f4xx_nucleo_144.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32F4xx_Nucleo_144-2f-Src

