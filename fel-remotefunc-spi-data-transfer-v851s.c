/*
 * Copyright © 2016 Siarhei Siamashka <siarhei.siamashka@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

typedef unsigned int  u32;
typedef unsigned char u8;

#define readl(addr)         (*((volatile u32 *)(addr)))
#define writel(v, addr)     (*((volatile u32 *)(addr)) = (u32)(v))
#define readb(addr)         (*((volatile u8 *)(addr)))
#define writeb(v, addr)     (*((volatile u8 *)(addr)) = (u8)(v))

#define SPI_BCC_STC_MASK    (0xFFFFFF << 0) /* master single mode transmit counter */
#define SPI_INT_STA_RX_RDY  (0x1 <<  0) /* rxFIFO ready, 0:RX_WL < RX_TRIG_LEVEL,1:RX_WL >= RX_TRIG_LEVEL */
#define SPI_INT_STA_RX_EMP  (0x1 <<  1) /* rxFIFO empty, this bit is set when rxFIFO is empty */
#define SPI_INT_STA_RX_FULL (0x1 <<  2) /* rxFIFO full, this bit is set when rxFIFO is full */
#define SPI_INT_STA_TX_RDY  (0x1 <<  4) /* txFIFO ready, 0:TX_WL > TX_TRIG_LEVEL,1:TX_WL <= TX_TRIG_LEVEL */
#define SPI_INT_STA_TX_EMP  (0x1 <<  5) /* txFIFO empty, this bit is set when txFIFO is empty */
#define SPI_INT_STA_TX_FULL (0x1 <<  6) /* txFIFO full, this bit is set when txFIFO is full */
#define SPI_INT_STA_RX_OVF  (0x1 <<  8) /* rxFIFO overflow, when set rxFIFO has overflowed */
#define SPI_INT_STA_RX_UDR  (0x1 <<  9) /* rxFIFO underrun, when set rxFIFO has underrun */
#define SPI_INT_STA_TX_OVF  (0x1 << 10) /* txFIFO overflow, when set txFIFO has overflowed */
#define SPI_INT_STA_TX_UDR  (0x1 << 11) /* fxFIFO underrun, when set txFIFO has underrun */
#define SPI_INT_STA_TC      (0x1 << 12) /* Transfer Completed */
#define SPI_INT_STA_SSI     (0x1 << 13) /* SS invalid interrupt, when set SS has changed from valid to invalid */
#define SPI_INT_STA_ERR     (SPI_INT_STA_TX_OVF | SPI_INT_STA_RX_UDR | SPI_INT_STA_RX_OVF) /* NO txFIFO underrun */
#define SPI_INT_STA_MASK    (0x77 | (0x3f << 8))

#define GPIO_BASE           (0x02000000)
#define PF_CFG              (0x00F0)
#define PF_DAT              (0x0100)
#define PF_CFG_REG         *(volatile u32*)(GPIO_BASE + PF_CFG)
#define PF_DAT_REG         *(volatile u32*)(GPIO_BASE + PF_DAT)

/*
 * Because previous implementation is very complicated so for V851S
 * we will implement in a different way, the working buffer(spl_addr)
 * layout is organized as below:
 *
 * | byte 0 | byte 1 | byte 2 | byte 3 |...........|.........|
 *  \_______________/ \_______________/ \_________/ \________/
 *          |                  |             |          |
 *        txlen              rxlen         txbuf      rxbuf
 *
 *  Where: total len = 4 + txlen + rxlen <= spl ram size (4096)
 *
 */

void spi_batch_data_transfer(u8 *buf,
                 void *spi_ctl_reg,
                 u32   spi_ctl_xch_bitmask,
                 void *spi_sta_reg,
                 void *spi_fifo_reg,
                 void *spi_tx_reg,
                 void *spi_rx_reg,
                 void *spi_bc_reg,
                 void *spi_tc_reg,
                 void *spi_bcc_reg)
{
    u32  rxsize;
    u32  txsize;
    u8  *rxbuf8;
    u8  *txbuf8;
    u32  cpsr;

    txsize = (buf[1] << 8) | buf[0];
    rxsize = (buf[3] << 8) | buf[2];

    txbuf8 = &buf[4];
    rxbuf8 = &buf[4 + txsize];

    /* clear spi irq pending */
    writel(0xffffffff, spi_sta_reg);
    /* turn off LED if there was an error before */
    PF_DAT_REG &= ~(1 << 6);

    /* V851S SPI0 implementation */
    /* SPI_MBC = tx_len + rx_len + dummy_cnt(=0) */
    writel(txsize + rxsize, spi_bc_reg);
    /* SPI_MTC = tx_len */
    writel(txsize, spi_tc_reg);
    /* SPI_BCC -> stc & dummy_cnt */
    if (spi_bcc_reg) {
        u32 bcc_reg = readl(spi_bcc_reg);
        bcc_reg &= ~SPI_BCC_STC_MASK;
        bcc_reg |= (SPI_BCC_STC_MASK & txsize);
        bcc_reg &= ~(0xf << 24); /* dummy_cnt = 0 */
        writel(bcc_reg, spi_bcc_reg);
    }

    /* Temporarily disable IRQ & FIQ */
    asm volatile("mrs %0, cpsr" : "=r" (cpsr));
    asm volatile("msr cpsr_c, %0" :: "r" (cpsr | 0xC0));

    /* Start the data transfer */
    writel(readl(spi_ctl_reg) | spi_ctl_xch_bitmask, spi_ctl_reg);

    /* tx data processing */
    while(txsize) {
        /* wait for TX_READY */
        while(!(readl(spi_sta_reg) & SPI_INT_STA_TX_RDY));
        writeb(*txbuf8++, spi_tx_reg);
        txsize--;
        /* read rx data as soon as when it is available */
        if(rxsize){
            if(readl(spi_fifo_reg) & 0xf) {
                *rxbuf8++ = readb(spi_rx_reg);
                rxsize--;
            }
        }
    }

    /* rx data processing */
    while(rxsize) {
        /* read rx data as soon as when it is available */
        if(readl(spi_fifo_reg) & 0xf) {
            *rxbuf8++ = readb(spi_rx_reg);
            rxsize--;
        }
    }

    /* check int status error */
    if(readl(spi_sta_reg) & SPI_INT_STA_ERR){
        // Turn on LED on port PF6
        PF_CFG_REG &= 0xF0FFFFFF;
        PF_CFG_REG |= 1 << 24; // PF6 output
        PF_DAT_REG |= 1 << 6;  // PF6 is high
    }

    /* Restore CPSR */
    asm volatile("msr cpsr_c, %0" :: "r" (cpsr));
}
