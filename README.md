# STM32F103-DualCDC
This is STM32F103 based Dual CDC "Makefile" based skeleton project.
A GPIO (connected to an LED) based feedback is provided for communication testing.

Get the ARM-GCC cross compiler:

    wget https://launchpad.net/gcc-arm-embedded/4.9/4.9-2015-q1-update/+download/gcc-arm-none-eabi-4_9-2015q1-20150306-linux.tar.bz2
    tar xvf gcc-arm-none-eabi-4_9-2015q1-20150306-linux.tar.bz2
    export PATH=$PATH:gcc-arm-none-eabi-4_9-2015q1/bin

Compile it:

    cd STM32F103-DualCDC/Project/DualCDC/src
    make clean
    make -j4

Program the MCU:

    Use "main.bin"
    More to come...

On Linux, the two virtual COM ports show up as:

    /dev/ttyACM0
    /dev/ttyACM1

Set temporary access or add UDEV rule for permanent user access:

    chmod a+rw /dev/ttyACM0
    chmod a+rw /dev/ttyACM1

Ports' settings:

    Baud rate: 115200
    Parity: None (?)
    Flow control: None (?)
    Start bits: 1 (?)
    Stop bits: 1 (?)

More to come...
