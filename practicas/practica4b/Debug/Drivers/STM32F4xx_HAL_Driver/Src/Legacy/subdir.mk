################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.c 

OBJS += \
./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o 

C_DEPS += \
./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F4xx_HAL_Driver/Src/Legacy/%.o Drivers/STM32F4xx_HAL_Driver/Src/Legacy/%.su Drivers/STM32F4xx_HAL_Driver/Src/Legacy/%.cyclo: ../Drivers/STM32F4xx_HAL_Driver/Src/Legacy/%.c Drivers/STM32F4xx_HAL_Driver/Src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I"C:/Users/Sandbox/Documents/PdM_workspace/practica4b/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Sandbox/Documents/PdM_workspace/practica4b/Drivers/CMSIS/Include" -I"C:/Users/Sandbox/Documents/PdM_workspace/practica4b/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Sandbox/Documents/PdM_workspace/practica4b/Drivers/BSP/STM32F4xx_Nucleo_144" -I"C:/Users/Sandbox/Documents/PdM_workspace/practica4b/Drivers/Core/Inc" -I"C:/Users/Sandbox/Documents/PdM_workspace/practica4b/Drivers/API/Inc" -I"C:/Users/Sandbox/Documents/PdM_workspace/practica4b/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy

clean-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy:
	-$(RM) ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.cyclo ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o ./Drivers/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.su

.PHONY: clean-Drivers-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy
