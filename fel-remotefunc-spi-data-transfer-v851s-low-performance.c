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

#define readl(addr)              (*((volatile u32 *)(addr)))
#define writel(v, addr)          (*((volatile u32 *)(addr)) = (u32)(v))
#define readb(addr)              (*((volatile u8 *)(addr)))
#define writeb(v, addr)          (*((volatile u8 *)(addr)) = (u8)(v))

#define SPI_BCC_STC_MASK         (0xFFFFFF << 0) /* master single mode transmit counter */
#define SPI_INT_STA_RX_RDY       (0x1 <<  0) /* rxFIFO ready, 0:RX_WL < RX_TRIG_LEVEL,1:RX_WL >= RX_TRIG_LEVEL */
#define SPI_INT_STA_RX_EMP       (0x1 <<  1) /* rxFIFO empty, this bit is set when rxFIFO is empty */
#define SPI_INT_STA_RX_FULL      (0x1 <<  2) /* rxFIFO full, this bit is set when rxFIFO is full */
#define SPI_INT_STA_TX_RDY       (0x1 <<  4) /* txFIFO ready, 0:TX_WL > TX_TRIG_LEVEL,1:TX_WL <= TX_TRIG_LEVEL */
#define SPI_INT_STA_TX_EMP       (0x1 <<  5) /* txFIFO empty, this bit is set when txFIFO is empty */
#define SPI_INT_STA_TX_FULL      (0x1 <<  6) /* txFIFO full, this bit is set when txFIFO is full */
#define SPI_INT_STA_RX_OVF       (0x1 <<  8) /* rxFIFO overflow, when set rxFIFO has overflowed */
#define SPI_INT_STA_RX_UDR       (0x1 <<  9) /* rxFIFO underrun, when set rxFIFO has underrun */
#define SPI_INT_STA_TX_OVF       (0x1 << 10) /* txFIFO overflow, when set txFIFO has overflowed */
#define SPI_INT_STA_TX_UDR       (0x1 << 11) /* fxFIFO underrun, when set txFIFO has underrun */
#define SPI_INT_STA_TC           (0x1 << 12) /* Transfer Completed */
#define SPI_INT_STA_SSI          (0x1 << 13) /* SS invalid interrupt, when set SS has changed from valid to invalid */
#define SPI_INT_STA_ERR          (SPI_INT_STA_TX_OVF | SPI_INT_STA_RX_UDR | SPI_INT_STA_RX_OVF) /* NO txFIFO underrun */
#define SPI_INT_STA_MASK         (0x77 | (0x3f << 8))

/* SPI FIFO Control Register Bit Fields & Masks,default value:0x0040_0001 */
#define SPI_FIFO_CTL_RX_LEVEL	 (0xFF <<  0) /* rxFIFO reday request trigger level,default 0x1 */
#define SPI_FIFO_CTL_RX_DRQEN	 (0x1  <<  8) /* rxFIFO DMA request enable,1:enable,0:disable */
#define SPI_FIFO_CTL_RX_TESTEN	 (0x1  << 14) /* rxFIFO test mode enable,1:enable,0:disable */
#define SPI_FIFO_CTL_RX_RST	     (0x1  << 15) /* rxFIFO reset, write 1, auto clear to 0 */
#define SPI_FIFO_CTL_TX_LEVEL	 (0xFF << 16) /* txFIFO empty request trigger level,default 0x40 */
#define SPI_FIFO_CTL_TX_DRQEN	 (0x1  << 24) /* txFIFO DMA request enable,1:enable,0:disable */
#define SPI_FIFO_CTL_TX_TESTEN	 (0x1  << 30) /* txFIFO test mode enable,1:enable,0:disable */
#define SPI_FIFO_CTL_TX_RST	     (0x1  << 31) /* txFIFO reset, write 1, auto clear to 0 */
#define SPI_FIFO_CTL_DRQEN_MASK	 (SPI_FIFO_CTL_TX_DRQEN | SPI_FIFO_CTL_RX_DRQEN)

#define GPIO_BASE                (0x02000000)
#define PF_CFG                   (0x00F0)
#define PF_DAT                   (0x0100)
#define PF_CFG_REG              *(volatile u32*)(GPIO_BASE + PF_CFG)
#define PF_DAT_REG              *(volatile u32*)(GPIO_BASE + PF_DAT)

/* SPI0 controller */
#define SUN8I_SPI0_VER           (0x04025000 + 0x0000) // SPI Version Register
#define SUN8I_SPI0_GCR           (0x04025000 + 0x0004) // SPI Global Control Register
#define SUN8I_SPI0_TCR           (0x04025000 + 0x0008) // SPI Transfer Control Register
#define SUN8I_SPI0_IER           (0x04025000 + 0x0010) // SPI Interrupt Control Register
#define SUN8I_SPI0_ISR           (0x04025000 + 0x0014) // SPI Interrupt Status Register
#define SUN8I_SPI0_FCR           (0x04025000 + 0x0018) // SPI FIFO Control Register
#define SUN8I_SPI0_FSR           (0x04025000 + 0x001C) // SPI FIFO Status Register
#define SUN8I_SPI0_WCR           (0x04025000 + 0x0020) // SPI Wait Clock Register
#define SUN8I_SPI0_CLK_CTL       (0x04025000 + 0x0024) // SPI Clock Rate Control Register
#define SUN8I_SPI0_SAMP_DL       (0x04025000 + 0x0028) // SPI Sample Delay Control Register
#define SUN8I_SPI0_MBC           (0x04025000 + 0x0030) // SPI Master Burst Counter Register
#define SUN8I_SPI0_MTC           (0x04025000 + 0x0034) // SPI Master Transmit Counter Register
#define SUN8I_SPI0_BCC           (0x04025000 + 0x0038) // SPI Master Burst Control Register
#define SUN8I_SPI0_BATCR         (0x04025000 + 0x0040) // SPI Bit-Aligned Transfer Configure Register
#define SUN8I_SPI0_BA_CCR        (0x04025000 + 0x0044) // SPI Bit-Aligned Clock Configuration Register
#define SUN8I_SPI0_TBR           (0x04025000 + 0x0048) // SPI TX Bit Register
#define SUN8I_SPI0_RBR           (0x04025000 + 0x004C) // SPI RX Bit Register
#define SUN8I_SPI0_NDMA_MODE_CTL (0x04025000 + 0x0088) // SPI Normal DMA Mode Control Register
#define SUN8I_SPI0_TXD           (0x04025000 + 0x0200) // SPI TX Data Register
#define SUN8I_SPI0_RXD           (0x04025000 + 0x0300) // SPI RX Data Register

#define TIME_OUT                 (0xFFFFFF)
#define MAX_TX_SIZE              (32)
#define MAX_RX_SIZE              (32)

#define tx_config(txlen)\
({\
    writel(txlen, spi_bc_reg);\
    writel(txlen, spi_tc_reg);\
    if(spi_bcc_reg){\
        u32 bcc_reg = readl(spi_bcc_reg);\
        bcc_reg &= ~SPI_BCC_STC_MASK;\
        bcc_reg |= (SPI_BCC_STC_MASK & txlen);\
        bcc_reg &= ~(0xf << 24);\
        writel(bcc_reg, spi_bcc_reg);\
    }\
})

#define rx_config(rxlen)\
({\
    writel(rxlen, spi_bc_reg);\
    writel(0, spi_tc_reg);\
    if(spi_bcc_reg){\
        u32 bcc_reg = readl(spi_bcc_reg);\
        bcc_reg &= ~SPI_BCC_STC_MASK;\
        bcc_reg |= (SPI_BCC_STC_MASK & 0);\
        bcc_reg &= ~(0xf << 24);\
        writel(bcc_reg, spi_bcc_reg);\
    }\
})

#define spi_reset_fifo(fifo_size)\
({\
    u32 reg_val = readl(SUN8I_SPI0_FCR);\
    reg_val |= (SPI_FIFO_CTL_RX_RST | SPI_FIFO_CTL_TX_RST);\
    reg_val &= ~(SPI_FIFO_CTL_RX_LEVEL | SPI_FIFO_CTL_TX_LEVEL);\
    reg_val |= ((fifo_size) << 16) | (fifo_size); \
    writel(reg_val, SUN8I_SPI0_FCR);\
})

#define goto_error()\
({\
    PF_CFG_REG &= 0xF0FFFFFF;\
    PF_CFG_REG |= 1 << 24;\
    PF_DAT_REG |= 1 << 6;\
    return;\
})

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
    u32  rxsize, rxlen;
    u32  txsize, txlen;
    u8  *rxbuf8;
    u8  *txbuf8;
    u32  cpsr;

    /* Temporarily disable IRQ & FIQ */
    asm volatile("mrs %0, cpsr" : "=r" (cpsr));
    asm volatile("msr cpsr_c, %0" :: "r" (cpsr | 0xC0));

    txsize = (buf[1] << 8) | buf[0];
    rxsize = (buf[3] << 8) | buf[2];

    txbuf8 = &buf[4];
    rxbuf8 = &buf[4 + txsize];

    /* SS_OWNER software */
    writel(readl(spi_ctl_reg) | (1 << 6), spi_ctl_reg);

    /* set SS_LEVEL to low */
    writel(readl(spi_ctl_reg) & ~(1 << 7), spi_ctl_reg);

    /* Initialize fifo */
    spi_reset_fifo(64);

    /* TX process */
    while(txsize) {

        /* clear spi irq pending */
        writel(0xffffffff, spi_sta_reg);

        if(txsize > MAX_TX_SIZE){
            txlen = MAX_TX_SIZE;
        }else{
            txlen = txsize;
        }

        /* config transmition len */
        tx_config(txlen);

        /* fect tx fifo */
        for (int i = 0; i < txlen; i++) {
            /* wait for TX_READY */
            while(!(readl(spi_sta_reg) & SPI_INT_STA_TX_RDY));
            writeb(*txbuf8++, spi_tx_reg);
        }

        /* start spi transfer */
        writel(readl(spi_ctl_reg) | spi_ctl_xch_bitmask, spi_ctl_reg);

        /* wait transfer complete */
        while(!(readl(spi_sta_reg) & SPI_INT_STA_TC));

        /* check int status error */
        if(readl(spi_sta_reg) & SPI_INT_STA_ERR){
            goto_error();
        }

        txsize -= txlen;
    }

    /* Initialize fifo */
    spi_reset_fifo(64);

    /* RX process */
    while(rxsize) {

        /* clear spi irq pending */
        writel(0xffffffff, spi_sta_reg);

        if(rxsize > MAX_RX_SIZE){
            rxlen = MAX_RX_SIZE;
        }else{
            rxlen = rxsize;
        }

        /* config transmition len */
        rx_config(rxlen);

        /* start spi transfer */
        writel(readl(spi_ctl_reg) | spi_ctl_xch_bitmask, spi_ctl_reg);

        /* wait transfer complete */
        while(!(readl(spi_sta_reg) & SPI_INT_STA_TC));

        /* check int status error */
        if(readl(spi_sta_reg) & SPI_INT_STA_ERR) {
            goto_error();
        }

        /* check rx fifo level */
        if((readl(spi_fifo_reg) & 0xff) != rxlen){
            goto_error();
        }

        /* read rx fifo */
        for (int i = 0; i < rxlen; i++) {
            *rxbuf8++ = readb(spi_rx_reg);
        }

        rxsize -= rxlen;
    }

    /* set SS_LEVEL to high */
    writel(readl(spi_ctl_reg) | (1 << 7), spi_ctl_reg);

    /* Restore CPSR */
    asm volatile("msr cpsr_c, %0" :: "r" (cpsr));
}
