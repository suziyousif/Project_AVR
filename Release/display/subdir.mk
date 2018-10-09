################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../display/Relogio_mux_Timer.c \
../display/displaySerial.c \
../display/lcd.c \
../display/led_display.c \
../display/led_display_simple_mux.c 

OBJS += \
./display/Relogio_mux_Timer.o \
./display/displaySerial.o \
./display/lcd.o \
./display/led_display.o \
./display/led_display_simple_mux.o 

C_DEPS += \
./display/Relogio_mux_Timer.d \
./display/displaySerial.d \
./display/lcd.d \
./display/led_display.d \
./display/led_display_simple_mux.d 


# Each subdirectory must supply rules for building sources it contributes
display/%.o: ../display/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


