/*
 * (C) Copyright 2012 Jens Andersen <jens.andersen@gmail.com>
 * (C) Copyright 2012 Henrik Nordstrom <henrik@henriknordstrom.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*

Build instructions:

arm-none-linux-gnueabi-gcc  -g -fno-common -ffixed-r8 -msoft-float -fno-builtin -ffreestanding -nostdinc -mno-thumb-interwork -Wall -Wstrict-prototypes -fno-stack-protector -Wno-format-nonliteral -Wno-format-security -fno-toplevel-reorder -Os jtag-loop.c -c

arm-none-linux-gnueabi-objcopy -O binary jtag-loop.o jtag-loop.bin

mksunxiboot jtag-loop.bin jtag-loop.sunxi
*/

#define GPIO_BASE 0x02000000
#define PF_CFG    0x00F0
#define PF_DAT    0x0100
#define PF_DRV    0x0104
#define PF_PUL    0x0114

#define PH_CFG0   0x0150
#define PH_CFG1   0x0154
#define PH_DAT    0x0160
#define PH_DRV0   0x0164
#define PH_DRV1   0x0168
#define PH_PUL    0x0174

#define PF_CFG_REG  *(volatile unsigned int*)(GPIO_BASE + PF_CFG)
#define PF_DAT_REG  *(volatile unsigned int*)(GPIO_BASE + PF_DAT)
#define PF_DRV_REG  *(volatile unsigned int*)(GPIO_BASE + PF_DRV)
#define PF_PUL_REG  *(volatile unsigned int*)(GPIO_BASE + PF_PUL)

#define PH_CFG1_REG *(volatile unsigned int*)(GPIO_BASE + PH_CFG1)

/*
 *  Build command:
 *     make clean tools jtag-loop.bin
 *
 *  How to load binary using FEL
 *     ./sunxi-fel.exe -p write 0x20000 jtag-loop.bin
 *     ./sunxi-fel.exe exec 0x20000
 */

 /*
  * PF_CFG
  *   PF0 [3:0]  : R_JTAG_MS
  *   FP1 [7:4]  : R_JTAG_DI
  *   PF3 [15:12]: R_JTAG_DO
  *   PF5 [23:20]: R_JTAG_CK
  */

 /*
  * PH_CFG1
  *   PH11 [15:12]: JTAG_MS 0x0010
  *   PH12 [19:16]: JTAG_CK 0x0010
  *   PH13 [23:20]: JTAG_DO 0x0010
  *   PH14 [27:24]: JTAG_DI 0x0010
  */


#define M 100000000
#define N 100000000

void _start(void)
{
    // Test LED on port PF6
    //PF_CFG_REG &= 0xF0FFFFFF;
    //PF_CFG_REG |= 1 << 24; // PF6 output
    //PF_DAT_REG |= 1 << 6;  // PF6 is high

#if 0
    // Configure port F as R_JTAG pins
    //PF_CFG_REG = 0xF16F6F66;
    //PF_DAT_REG |= 1 << 6; // PF6 is high

    // Configure port F as JTAG pins
    PF_CFG_REG = 0xF13F3F33;
    PF_DAT_REG |= 1 << 6; // PF6 is high

#else
    // Configure port H as JTAG pins
    PH_CFG1_REG &= 0xF0000FFF;
    PH_CFG1_REG |= 0xF2222FFF;
    // Test LED on port PF6
    PF_CFG_REG &= 0xF0FFFFFF;
    PF_CFG_REG |= 1 << 24; // PF6 output
    PF_DAT_REG |= 1 << 6;  // PF6 is high
#endif

    while(1);
}
