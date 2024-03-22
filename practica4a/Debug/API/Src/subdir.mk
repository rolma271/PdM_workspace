################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../API/Src/API_delay.c 

OBJS += \
./API/Src/API_delay.o 

C_DEPS += \
./API/Src/API_delay.d 


# Each subdirectory must supply rules for building sources it contributes
API/Src/%.o API/Src/%.su API/Src/%.cyclo: ../API/Src/%.c API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I"/home/marco/cese/PdM_workspace/practica3/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/marco/cese/PdM_workspace/practica3/Drivers/CMSIS/Include" -I"/home/marco/cese/PdM_workspace/practica3/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/marco/cese/PdM_workspace/practica3/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/home/marco/cese/PdM_workspace/practica3/Drivers/Core/Inc" -I"/home/marco/cese/PdM_workspace/practica3/API/Inc" -I"/home/marco/cese/PdM_workspace/practica3/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-API-2f-Src

clean-API-2f-Src:
	-$(RM) ./API/Src/API_delay.cyclo ./API/Src/API_delay.d ./API/Src/API_delay.o ./API/Src/API_delay.su

.PHONY: clean-API-2f-Src

