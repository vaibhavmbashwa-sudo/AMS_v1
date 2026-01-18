################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/ADBMS6830/src/adBms6830GenericType.c \
../Core/ADBMS6830/src/adBms6830ParseCreate.c \
../Core/ADBMS6830/src/adBms_Application.c \
../Core/ADBMS6830/src/custom_calc_func.c \
../Core/ADBMS6830/src/mcuWrapper.c \
../Core/ADBMS6830/src/serialPrintResult.c 

OBJS += \
./Core/ADBMS6830/src/adBms6830GenericType.o \
./Core/ADBMS6830/src/adBms6830ParseCreate.o \
./Core/ADBMS6830/src/adBms_Application.o \
./Core/ADBMS6830/src/custom_calc_func.o \
./Core/ADBMS6830/src/mcuWrapper.o \
./Core/ADBMS6830/src/serialPrintResult.o 

C_DEPS += \
./Core/ADBMS6830/src/adBms6830GenericType.d \
./Core/ADBMS6830/src/adBms6830ParseCreate.d \
./Core/ADBMS6830/src/adBms_Application.d \
./Core/ADBMS6830/src/custom_calc_func.d \
./Core/ADBMS6830/src/mcuWrapper.d \
./Core/ADBMS6830/src/serialPrintResult.d 


# Each subdirectory must supply rules for building sources it contributes
Core/ADBMS6830/src/%.o Core/ADBMS6830/src/%.su Core/ADBMS6830/src/%.cyclo: ../Core/ADBMS6830/src/%.c Core/ADBMS6830/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H523xx -c -I../Core/Inc -I/Users/vaibhavmb/Documents/AMS/AMS_H523/Core/ADBMS6830/inc -I/Users/vaibhavmb/Documents/AMS/AMS_H523/Core/ADBMS2950/inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-ADBMS6830-2f-src

clean-Core-2f-ADBMS6830-2f-src:
	-$(RM) ./Core/ADBMS6830/src/adBms6830GenericType.cyclo ./Core/ADBMS6830/src/adBms6830GenericType.d ./Core/ADBMS6830/src/adBms6830GenericType.o ./Core/ADBMS6830/src/adBms6830GenericType.su ./Core/ADBMS6830/src/adBms6830ParseCreate.cyclo ./Core/ADBMS6830/src/adBms6830ParseCreate.d ./Core/ADBMS6830/src/adBms6830ParseCreate.o ./Core/ADBMS6830/src/adBms6830ParseCreate.su ./Core/ADBMS6830/src/adBms_Application.cyclo ./Core/ADBMS6830/src/adBms_Application.d ./Core/ADBMS6830/src/adBms_Application.o ./Core/ADBMS6830/src/adBms_Application.su ./Core/ADBMS6830/src/custom_calc_func.cyclo ./Core/ADBMS6830/src/custom_calc_func.d ./Core/ADBMS6830/src/custom_calc_func.o ./Core/ADBMS6830/src/custom_calc_func.su ./Core/ADBMS6830/src/mcuWrapper.cyclo ./Core/ADBMS6830/src/mcuWrapper.d ./Core/ADBMS6830/src/mcuWrapper.o ./Core/ADBMS6830/src/mcuWrapper.su ./Core/ADBMS6830/src/serialPrintResult.cyclo ./Core/ADBMS6830/src/serialPrintResult.d ./Core/ADBMS6830/src/serialPrintResult.o ./Core/ADBMS6830/src/serialPrintResult.su

.PHONY: clean-Core-2f-ADBMS6830-2f-src

