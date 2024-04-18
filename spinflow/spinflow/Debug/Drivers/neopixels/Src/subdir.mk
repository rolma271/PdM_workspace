################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/neopixels/Src/npx_api.c \
../Drivers/neopixels/Src/npx_port.c 

OBJS += \
./Drivers/neopixels/Src/npx_api.o \
./Drivers/neopixels/Src/npx_port.o 

C_DEPS += \
./Drivers/neopixels/Src/npx_api.d \
./Drivers/neopixels/Src/npx_port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/neopixels/Src/%.o Drivers/neopixels/Src/%.su Drivers/neopixels/Src/%.cyclo: ../Drivers/neopixels/Src/%.c Drivers/neopixels/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/neopixels/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/imu/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/BSP/STM32F4xx_Nucleo_144/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/delay/Inc" -I"C:/Users/Sandbox/Documents/spinflow/spinflow/Drivers/log/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-neopixels-2f-Src

clean-Drivers-2f-neopixels-2f-Src:
	-$(RM) ./Drivers/neopixels/Src/npx_api.cyclo ./Drivers/neopixels/Src/npx_api.d ./Drivers/neopixels/Src/npx_api.o ./Drivers/neopixels/Src/npx_api.su ./Drivers/neopixels/Src/npx_port.cyclo ./Drivers/neopixels/Src/npx_port.d ./Drivers/neopixels/Src/npx_port.o ./Drivers/neopixels/Src/npx_port.su

.PHONY: clean-Drivers-2f-neopixels-2f-Src

