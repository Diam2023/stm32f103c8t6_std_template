## STM32F1固件库模板工程

适用于STM32F103C8T6 可根据不同芯片更改CMake中的宏并替换.s文件与.ld文件中的FLASH/RAM大小

默认打开assert, 可从CMake中去掉宏定义以关闭

## 开发环境:

    * Arch Linux x86_64
    * arm-none-eabi-gcc-11.3.0
    * cmake version 3.21.6