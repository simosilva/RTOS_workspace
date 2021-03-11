################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F401xx -DUSE_STDPERIPH_DRIVER -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Led_and_Button_IT/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Led_and_Button_IT/Third-Party/SEGGER/Config" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Led_and_Button_IT/Third-Party/SEGGER/OS" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Led_and_Button_IT/Third-Party/SEGGER/SEGGER" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Led_and_Button_IT/CMSIS/core" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Led_and_Button_IT/Config" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Led_and_Button_IT/Third-Party/FreeRTOS/org/Source/include" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Led_and_Button_IT/CMSIS/device" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Led_and_Button_IT/inc" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Led_and_Button_IT/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


