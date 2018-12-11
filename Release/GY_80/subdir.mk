################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GY_80/ADXL345.c \
../GY_80/modbus.c 

OBJS += \
./GY_80/ADXL345.o \
./GY_80/modbus.o 

C_DEPS += \
./GY_80/ADXL345.d \
./GY_80/modbus.d 


# Each subdirectory must supply rules for building sources it contributes
GY_80/%.o: ../GY_80/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


