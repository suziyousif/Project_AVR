################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Amperimetro_4Escalas/Amperimetro.c 

OBJS += \
./Amperimetro_4Escalas/Amperimetro.o 

C_DEPS += \
./Amperimetro_4Escalas/Amperimetro.d 


# Each subdirectory must supply rules for building sources it contributes
Amperimetro_4Escalas/%.o: ../Amperimetro_4Escalas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


