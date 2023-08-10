# sunxi-tools for v851s build on Windows

 - Build environment: MinGW msys64 (Mysys2)
 - Shell: msys2
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
   > dd if=jtag-loop.sunxi of=/dev/sdc bs=1k seek=8   
 ```
 
 - Reset YuzukiHD board, jtag-loop will be executed and LED1 will be on. 
 - Note: I have tried to configure JTAG on PH but unfortunately it doesn't work, currently JTAG works only with PF
 
## License
This software is licensed under the terms of GPLv2+ as defined by the
Free Software Foundation, details can be read in the [LICENSE.md](LICENSE.md)
file.

[allwinner soc]: http://linux-sunxi.org/Allwinner_SoC_Family
[fel mode]: http://linux-sunxi.org/FEL
