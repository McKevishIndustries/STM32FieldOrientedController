## Project Requirements

[CMake](https://cmake.org/download/) tool to manage building of source code

[ARM toolchain](https://learn.arm.com/install-guides/gcc/arm-gnu/) compiler 

[OpenOCD](https://openocd.org)  open source On-chip debugger 

[STM CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) stm tool to select specific mcu, pin assignment and generating code 

[STM ST-LINK](https://www.st.com/en/development-tools/stsw-link004.html) stm tool for loading software to MCU and debug

## How to build the project

```bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=toolchain/gcc-arm-none-eabi.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=true

cd build

make -j4
```

## How to flash the project to the microcontroller

```bash
openocd  -f  ../board/stm_nucleo_446re.cfg -c "tcl_port disabled" -c "gdb_port disabled" -c "tcl_port disabled" -c "program \"stm32fieldorientedcontroller.elf\"" -c reset -c shutdown
```

## How to run the unit tests

```bash
cmake -B build-tests -DCMAKE_BUILD_TYPE=Release

cd build-tests

make -j4

./tests
```

expected results:

```bash
===============================================================================
All tests passed (6 assertions in 1 test case)
```
