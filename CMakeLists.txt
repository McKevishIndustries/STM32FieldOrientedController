# Template CMakeLists.txt configuration for STM32 MCUS
cmake_minimum_required(VERSION 3.12)

# project name and name of the executable
project(STM32FOC)
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

# Set all used project directories
set(CUBEMX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/board/CubeMX)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/application)

# set startup script and linker script
set(STARTUP_SCRIPT ${CUBEMX_DIR}/startup_stm32f446xx.s)
set(MCU_LINKER_SCRIPT ${CUBEMX_DIR}/stm32f446retx_flash.ld)

# set mcu specific data
set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F446xx)
set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard)

# set programming language
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Headers
set(CUBEMX_INCLUDE_DIRECTORIES
    ${CUBEMX_DIR}/Core/Inc
    ${CUBEMX_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc
    ${CUBEMX_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc/Legacy
    ${CUBEMX_DIR}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    ${CUBEMX_DIR}/Drivers/CMSIS/Include)

set(PROJECT_INCLUDE_DIRECTORIES
    ${PROJECT_DIR}/Inc)

# Sources
file(GLOB_RECURSE STM32CUBEMX_SOURCES
    ${CUBEMX_DIR}/Core/*.c
    ${CUBEMX_DIR}/Drivers/*.c)

file(GLOB_RECURSE PROJECT_SOURCES
    ${PROJECT_DIR}/Src/*.cpp
    ${PROJECT_DIR}/Src/*.c)

# Executable files
add_executable(${EXECUTABLE}
    ${STM32CUBEMX_SOURCES} 
    ${PROJECT_SOURCES}
    ${STARTUP_SCRIPT})

# Embedded macros(defines)
target_compile_definitions(${EXECUTABLE} PRIVATE
    ${MCU_MODEL}
    USE_HAL_DRIVER)

# Add header directories (AFTER add_executable !!)
target_include_directories(${EXECUTABLE} PRIVATE
    ${CUBEMX_INCLUDE_DIRECTORIES}
    ${PROJECT_INCLUDE_DIRECTORIES})

# Compiler and linker options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin)

# clean target
set_target_properties(${EXECUTABLE} PROPERTIES ADDITIONAL_CLEAN_FILES
    "${PROJECT_NAME}.bin;${PROJECT_NAME}.hex;${PROJECT_NAME}.map")