################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bmp085/AVR_I2C.c \
../bmp085/bmp085.c 

OBJS += \
./bmp085/AVR_I2C.o \
./bmp085/bmp085.o 

C_DEPS += \
./bmp085/AVR_I2C.d \
./bmp085/bmp085.d 


# Each subdirectory must supply rules for building sources it contributes
bmp085/%.o: ../bmp085/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


