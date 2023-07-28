################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DIO_program.c \
../src/EXTI_program.c \
../src/GI_program.c \
../src/SERVO_program.c \
../src/TIMER_program.c \
../src/US_SENSOR_program.c \
../src/main.c 

OBJS += \
./src/DIO_program.o \
./src/EXTI_program.o \
./src/GI_program.o \
./src/SERVO_program.o \
./src/TIMER_program.o \
./src/US_SENSOR_program.o \
./src/main.o 

C_DEPS += \
./src/DIO_program.d \
./src/EXTI_program.d \
./src/GI_program.d \
./src/SERVO_program.d \
./src/TIMER_program.d \
./src/US_SENSOR_program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


