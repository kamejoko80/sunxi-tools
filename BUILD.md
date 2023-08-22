# sunxi-tools for v851s build on Windows

 - Build environment: MinGW msys64 (Mysys2)
 - Shell: msys2 (mingw64.exe)
 - Install the below packages:

 ```
   > pacman -S mingw-w64-x86_64-libusb
   > pacman -S mingw-w64-x86_64-zlib
   > make clean tools jtag-loop.bin
 ```

# How to flash fel-sdboot.sunxi

 - Run msys2 shell as administrator user
 - Execute the below dd command:

 ```
   > dd if=bin/fel-sdboot.sunxi of=/dev/sdc bs=1k seek=8
 ```

 - Reset YuzukiHD board, FEL mode will apear imidiately

# How to flash jtag-loop.sunxi

 - First build sunxi bootable image:

 ```
   > mksunxiboot.exe jtag-loop.bin jtag-loop.sunxi
 ```

 - For SD card boot:

 ```
    > dd if=jtag-loop.sunxi of=/dev/sdc bs=1k seek=8
 ```

 - For SPI flash boot:

 ```
    > ./sunxi-fel.exe -p spiflash-write 0 jtag-loop.sunxi
 ```

 - Reset YuzukiHD board, jtag-loop will be executed and LED1 will be on.
 - Note:
        • Must flip the USB cable to switch USB to UART bridge mode so that V851s can boot from SD or SPI flash.
        • LED1 will be on when booting successfully.
        • I have tried to configure JTAG on PH but unfortunately it doesn't work, currently JTAG works only with PF

# How to start opencd gdb server:

 ```
    > openocd -f interface/jlink.cfg -f target/allwinner_v851s.cfg
 ```

# How to generate fel-remotefunc-spi-data-transfer-v851s.h ?

 - Install ruby on Windows (using rubyinstaller-devkit-3.2.2-1-x64.exe)
 - On Windows bat shell execute the below command:

 ```
   > ruby fel-remotefunc-compiler-v851s.rb fel-remotefunc-spi-data-transfer-v851s.c fel-remotefunc-spi-data-transfer-v851s.h
 ```

## License
This software is licensed under the terms of GPLv2+ as defined by the
Free Software Foundation, details can be read in the [LICENSE.md](LICENSE.md)
file.

[allwinner soc]: http://linux-sunxi.org/Allwinner_SoC_Family
[fel mode]: http://linux-sunxi.org/FEL
