# sunxi-tools for v851s build on Windows

 - Build environment: MinGW msys64 (Mysys2)
 - Shell: msys2
 - Install the below packages:

 ```
   > pacman -S mingw-w64-x86_64-libusb
   > pacman -S mingw-w64-x86_64-zlib
   > make clean tools jtag-loop.bin
 ```

## License
This software is licensed under the terms of GPLv2+ as defined by the
Free Software Foundation, details can be read in the [LICENSE.md](LICENSE.md)
file.

[allwinner soc]: http://linux-sunxi.org/Allwinner_SoC_Family
[fel mode]: http://linux-sunxi.org/FEL
