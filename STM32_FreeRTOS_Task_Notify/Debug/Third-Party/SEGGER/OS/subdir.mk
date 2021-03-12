################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Third-Party/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.c 

OBJS += \
./Third-Party/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.o 

C_DEPS += \
./Third-Party/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
Third-Party/SEGGER/OS/%.o: ../Third-Party/SEGGER/OS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F401xx -DUSE_STDPERIPH_DRIVER -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Task_Notify/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Task_Notify/Third-Party/SEGGER/Config" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Task_Notify/Third-Party/SEGGER/OS" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Task_Notify/Third-Party/SEGGER/SEGGER" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Task_Notify/CMSIS/core" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Task_Notify/Config" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Task_Notify/Third-Party/FreeRTOS/org/Source/include" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Task_Notify/CMSIS/device" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Task_Notify/inc" -I"C:/Users/silvestros/Documents/Corso_FreeRTOS/RTOS_workspace/STM32_FreeRTOS_Task_Notify/StdPeriph_Driver/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


