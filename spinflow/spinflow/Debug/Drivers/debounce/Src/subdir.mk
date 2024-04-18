################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/debounce/Src/API_debounce.c 

OBJS += \
./Drivers/debounce/Src/API_debounce.o 

C_DEPS += \
./Drivers/debounce/Src/API_debounce.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/debounce/Src/%.o Drivers/debounce/Src/%.su Drivers/debounce/Src/%.cyclo: ../Drivers/debounce/Src/%.c Drivers/debounce/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/neopixels/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/imu/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/BSP/STM32F4xx_Nucleo_144/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/debounce/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/delay/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/log/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-debounce-2f-Src

clean-Drivers-2f-debounce-2f-Src:
	-$(RM) ./Drivers/debounce/Src/API_debounce.cyclo ./Drivers/debounce/Src/API_debounce.d ./Drivers/debounce/Src/API_debounce.o ./Drivers/debounce/Src/API_debounce.su

.PHONY: clean-Drivers-2f-debounce-2f-Src

