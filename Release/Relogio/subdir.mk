################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Relogio/Relogio_mux_Timer.c 

OBJS += \
./Relogio/Relogio_mux_Timer.o 

C_DEPS += \
./Relogio/Relogio_mux_Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Relogio/%.o: ../Relogio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


