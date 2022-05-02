## STM32F1固件库模板工程

适用于STM32F103C8T6 可根据不同芯片更改CMake中的宏并替换.s文件与.ld文件中的FLASH/RAM大小

默认打开assert, 可从CMake中去掉宏定义以关闭

调试使用VSCode插件Cortex-Debug
根据需要可自行编写task进行烧写

若芯片id对不上可查找openocd配置文件更改id

## 开发环境:

    * Arch Linux x86_64
    * arm-none-eabi-gcc-11.3.0
    * cmake version 3.21.6
