cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE stm32-toolchain.cmake)
project(CMAKE_TEMPLATE)
enable_language(ASM)

set(CMAKE_MAKE_PROGRAM CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE C_SOURCES CONFIGURE_DEPENDS
  Src/*.c
  CMSIS/*.c
  STM32F10x_StdPeriph_Driver/*.c)

add_executable(${CMAKE_PROJECT_NAME}.elf ${C_SOURCES} startup_stm32f10x_md.s)

target_include_directories(${CMAKE_PROJECT_NAME}.elf PRIVATE
  Inc
  CMSIS
  STM32F10x_StdPeriph_Driver/inc)

target_compile_definitions(${CMAKE_PROJECT_NAME}.elf PRIVATE
  # USE_FULL_ASSERT
  USE_STDPERIPH_DRIVER
  STM32F10X_MD)

set(MCU_FLAGS -mcpu=cortex-m0 -mthumb)

target_compile_options(${CMAKE_PROJECT_NAME}.elf PRIVATE ${MCU_FLAGS})
target_link_options(${CMAKE_PROJECT_NAME}.elf PRIVATE ${MCU_FLAGS}
  -T ${PROJECT_SOURCE_DIR}/stm32_flash.ld)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -Oihex ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex
  COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin)
