################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/ADBMS2950/src/adBms2950TestHelper.c \
../Core/ADBMS2950/src/adbms_2950.c \
../Core/ADBMS2950/src/adi_bms_2950cmdlist.c \
../Core/ADBMS2950/src/adi_bms_2950data.c \
../Core/ADBMS2950/src/adi_bms_utility.c \
../Core/ADBMS2950/src/application.c \
../Core/ADBMS2950/src/pal.c \
../Core/ADBMS2950/src/print_result.c 

OBJS += \
./Core/ADBMS2950/src/adBms2950TestHelper.o \
./Core/ADBMS2950/src/adbms_2950.o \
./Core/ADBMS2950/src/adi_bms_2950cmdlist.o \
./Core/ADBMS2950/src/adi_bms_2950data.o \
./Core/ADBMS2950/src/adi_bms_utility.o \
./Core/ADBMS2950/src/application.o \
./Core/ADBMS2950/src/pal.o \
./Core/ADBMS2950/src/print_result.o 

C_DEPS += \
./Core/ADBMS2950/src/adBms2950TestHelper.d \
./Core/ADBMS2950/src/adbms_2950.d \
./Core/ADBMS2950/src/adi_bms_2950cmdlist.d \
./Core/ADBMS2950/src/adi_bms_2950data.d \
./Core/ADBMS2950/src/adi_bms_utility.d \
./Core/ADBMS2950/src/application.d \
./Core/ADBMS2950/src/pal.d \
./Core/ADBMS2950/src/print_result.d 


# Each subdirectory must supply rules for building sources it contributes
Core/ADBMS2950/src/%.o Core/ADBMS2950/src/%.su Core/ADBMS2950/src/%.cyclo: ../Core/ADBMS2950/src/%.c Core/ADBMS2950/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H523xx -c -I../Core/Inc -I/Users/vaibhavmb/Documents/AMS/AMS_H523/Core/ADBMS6830/inc -I/Users/vaibhavmb/Documents/AMS/AMS_H523/Core/ADBMS2950/inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-ADBMS2950-2f-src

clean-Core-2f-ADBMS2950-2f-src:
	-$(RM) ./Core/ADBMS2950/src/adBms2950TestHelper.cyclo ./Core/ADBMS2950/src/adBms2950TestHelper.d ./Core/ADBMS2950/src/adBms2950TestHelper.o ./Core/ADBMS2950/src/adBms2950TestHelper.su ./Core/ADBMS2950/src/adbms_2950.cyclo ./Core/ADBMS2950/src/adbms_2950.d ./Core/ADBMS2950/src/adbms_2950.o ./Core/ADBMS2950/src/adbms_2950.su ./Core/ADBMS2950/src/adi_bms_2950cmdlist.cyclo ./Core/ADBMS2950/src/adi_bms_2950cmdlist.d ./Core/ADBMS2950/src/adi_bms_2950cmdlist.o ./Core/ADBMS2950/src/adi_bms_2950cmdlist.su ./Core/ADBMS2950/src/adi_bms_2950data.cyclo ./Core/ADBMS2950/src/adi_bms_2950data.d ./Core/ADBMS2950/src/adi_bms_2950data.o ./Core/ADBMS2950/src/adi_bms_2950data.su ./Core/ADBMS2950/src/adi_bms_utility.cyclo ./Core/ADBMS2950/src/adi_bms_utility.d ./Core/ADBMS2950/src/adi_bms_utility.o ./Core/ADBMS2950/src/adi_bms_utility.su ./Core/ADBMS2950/src/application.cyclo ./Core/ADBMS2950/src/application.d ./Core/ADBMS2950/src/application.o ./Core/ADBMS2950/src/application.su ./Core/ADBMS2950/src/pal.cyclo ./Core/ADBMS2950/src/pal.d ./Core/ADBMS2950/src/pal.o ./Core/ADBMS2950/src/pal.su ./Core/ADBMS2950/src/print_result.cyclo ./Core/ADBMS2950/src/print_result.d ./Core/ADBMS2950/src/print_result.o ./Core/ADBMS2950/src/print_result.su

.PHONY: clean-Core-2f-ADBMS2950-2f-src

