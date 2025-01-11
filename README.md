## Project Requirements

[CMake](https://cmake.org/download/) tool to manage building of source code
[ARM toolchain](https://learn.arm.com/install-guides/gcc/arm-gnu/) compiler 

[STM CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) stm tool to select specific mcu, pin assignment and generating code 
[STM ST-LINK](https://www.st.com/en/development-tools/stsw-link004.html) stm tool for loading software to MCU and debug


## How to build the project

```bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=gcc-arm-none-eabi.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=true

cd build

make -j4
```
