/*
 * (C) Copyright 2016 Siarhei Siamashka <siarhei.siamashka@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fel_lib.h"
#include "progress.h"

#include "fel-remotefunc-spi-data-transfer-v851s.h"

/*****************************************************************************/

struct sunxi_ccm_reg {
    uint32_t pll1_cfg;           /* 0x000 pll1 (cpux) control */
    uint8_t reserved_0x004[12];
    uint32_t pll5_cfg;           /* 0x010 pll5 (ddr) control */
    uint8_t reserved_0x014[12];
    uint32_t pll6_cfg;           /* 0x020 pll6 (periph0) control */
    uint8_t reserved_0x020[4];
    uint32_t pll_periph1_cfg;    /* 0x028 pll periph1 control */
    uint8_t reserved_0x028[4];
    uint32_t pll7_cfg;           /* 0x030 pll7 (gpu) control */
    uint8_t reserved_0x034[12];
    uint32_t pll3_cfg;           /* 0x040 pll3 (video0) control */
    uint8_t reserved_0x044[4];
    uint32_t pll_csi_cfg;        /* 0x048 pll csi control */
    uint8_t reserved_0x04c[12];
    uint32_t pll4_cfg;           /* 0x058 pll4 (ve) control */
    uint8_t reserved_0x05c[4];
    uint32_t pll10_cfg;          /* 0x060 pll10 (de) control */
    uint8_t reserved_0x064[12];
    uint32_t pll9_cfg;           /* 0x070 pll9 (hsic) control */
    uint8_t reserved_0x074[4];
    uint32_t pll2_cfg;           /* 0x078 pll2 (audio) control */
    uint8_t reserved_0x07c[148];
    uint32_t pll5_pat;           /* 0x110 pll5 (ddr) pattern */
    uint8_t reserved_0x114[20];
    uint32_t pll_periph1_pat0;   /* 0x128 pll periph1 pattern0 */
    uint32_t pll_periph1_pat1;   /* 0x12c pll periph1 pattern1 */
    uint32_t pll7_pat0;          /* 0x130 pll7 (gpu) pattern0 */
    uint32_t pll7_pat1;          /* 0x134 pll7 (gpu) pattern1 */
    uint8_t reserved_0x138[8];
    uint32_t pll3_pat0;          /* 0x140 pll3 (video0) pattern0 */
    uint32_t pll3_pat1;          /* 0x144 pll3 (video0) pattern1 */
    uint32_t pll_csi_pat0;       /* 0x148 pll csi pattern0 */
    uint32_t pll_csi_pat1;       /* 0x14c pll csi pattern1 */
    uint8_t reserved_0x150[8];
    uint32_t pll4_pat0;          /* 0x158 pll4 (ve) pattern0 */
    uint32_t pll4_pat1;          /* 0x15c pll4 (ve) pattern1 */
    uint32_t pll10_pat0;         /* 0x160 pll10 (de) pattern0 */
    uint32_t pll10_pat1;         /* 0x164 pll10 (de) pattern1 */
    uint8_t reserved_0x168[8];
    uint32_t pll9_pat0;          /* 0x170 pll9 (hsic) pattern0 */
    uint32_t pll9_pat1;          /* 0x174 pll9 (hsic) pattern1 */
    uint32_t pll2_pat0;          /* 0x178 pll2 (audio) pattern0 */
    uint32_t pll2_pat1;          /* 0x17c pll2 (audio) pattern1 */
    uint8_t reserved_0x180[384];
    uint32_t pll1_bias;          /* 0x300 pll1 (cpux) bias */
    uint8_t reserved_0x304[12];
    uint32_t pll5_bias;          /* 0x310 pll5 (ddr) bias */
    uint8_t reserved_0x314[12];
    uint32_t pll6_bias;          /* 0x320 pll6 (periph0) bias */
    uint8_t reserved_0x324[4];
    uint32_t pll_periph1_bias;   /* 0x328 pll periph1 bias */
    uint8_t reserved_0x32c[4];
    uint32_t pll7_bias;          /* 0x330 pll7 (gpu) bias */
    uint8_t reserved_0x334[12];
    uint32_t pll3_bias;          /* 0x340 pll3 (video0) bias */
    uint8_t reserved_0x344[4];
    uint32_t pll_csi_bias;       /* 0x348 pll video1 bias */
    uint8_t reserved_0x34c[12];
    uint32_t pll4_bias;          /* 0x358 pll4 (ve) bias */
    uint8_t reserved_0x35c[4];
    uint32_t pll10_bias;         /* 0x360 pll10 (de) bias */
    uint8_t reserved_0x364[12];
    uint32_t pll9_bias;          /* 0x370 pll9 (hsic) bias */
    uint8_t reserved_0x374[4];
    uint32_t pll2_bias;          /* 0x378 pll2 (audio) bias */
    uint8_t reserved_0x37c[132];
    uint32_t pll1_tun;           /* 0x400 pll1 (cpux) tunning */
    uint8_t reserved_0x404[252];
    uint32_t cpu_axi_cfg;        /* 0x500 CPUX/AXI clock control*/
    uint8_t reserved_0x504[12];
    uint32_t psi_ahb1_ahb2_cfg;  /* 0x510 PSI/AHB1/AHB2 clock control */
    uint8_t reserved_0x514[8];
    uint32_t ahb3_cfg;           /* 0x51c AHB3 clock control */
    uint32_t apb0_cfg;           /* 0x520 APB0 clock control */
    uint32_t apb1_cfg;           /* 0x524 APB1 clock control */
    uint8_t reserved_0x528[24];
    uint32_t mbus_cfg;           /* 0x540 MBUS clock control */
    uint8_t reserved_0x544[188];
    uint32_t de_clk_cfg;        /* 0x600 DE clock control */
    uint8_t reserved_0x604[8];
    uint32_t de_gate_reset;    /* 0x60c DE gate/reset control */
    uint8_t reserved_0x610[16];
    uint32_t di_clk_cfg;        /* 0x620 DI clock control */
    uint8_t reserved_0x024[8];
    uint32_t di_gate_reset;    /* 0x62c DI gate/reset control */
    uint8_t reserved_0x630[64];
    uint32_t gpu_clk_cfg;    /* 0x670 GPU clock control */
    uint8_t reserved_0x674[8];
    uint32_t gpu_gate_reset;    /* 0x67c GPU gate/reset control */
    uint32_t ce_clk_cfg;        /* 0x680 CE clock control */
    uint8_t reserved_0x684[8];
    uint32_t ce_gate_reset;    /* 0x68c CE gate/reset control */
    uint32_t ve_clk_cfg;        /* 0x690 VE clock control */
    uint8_t reserved_0x694[8];
    uint32_t ve_gate_reset;    /* 0x69c VE gate/reset control */
    uint8_t reserved_0x6a0[16];
    uint32_t emce_clk_cfg;    /* 0x6b0 EMCE clock control */
    uint8_t reserved_0x6b4[8];
    uint32_t emce_gate_reset;    /* 0x6bc EMCE gate/reset control */
    uint32_t vp9_clk_cfg;    /* 0x6c0 VP9 clock control */
    uint8_t reserved_0x6c4[8];
    uint32_t vp9_gate_reset;    /* 0x6cc VP9 gate/reset control */
    uint8_t reserved_0x6d0[60];
    uint32_t dma_gate_reset;    /* 0x70c DMA gate/reset control */
    uint8_t reserved_0x710[12];
    uint32_t msgbox_gate_reset;    /* 0x71c Message Box gate/reset control */
    uint8_t reserved_0x720[12];
    uint32_t spinlock_gate_reset;/* 0x72c Spinlock gate/reset control */
    uint8_t reserved_0x730[12];
    uint32_t hstimer_gate_reset;    /* 0x73c HS Timer gate/reset control */
    uint32_t avs_gate_reset;    /* 0x740 AVS gate/reset control */
    uint8_t reserved_0x744[72];
    uint32_t dbgsys_gate_reset;    /* 0x78c Debugging system gate/reset control */
    uint8_t reserved_0x790[12];
    uint32_t psi_gate_reset;    /* 0x79c PSI gate/reset control */
    uint8_t reserved_0x7a0[12];
    uint32_t pwm_gate_reset;    /* 0x7ac PWM gate/reset control */
    uint8_t reserved_0x7b0[12];
    uint32_t iommu_gate_reset;    /* 0x7bc IOMMU gate/reset control */
    uint8_t reserved_0x7c0[64];
    uint32_t dram_clk_cfg;        /* 0x800 DRAM clock control */
    uint32_t mbus_gate;        /* 0x804 MBUS gate control */
    uint8_t reserved_0x808[4];
    uint32_t dram_gate_reset;    /* 0x80c DRAM gate/reset control */
    uint32_t nand0_clk_cfg;    /* 0x810 NAND0 clock control */
    uint32_t nand1_clk_cfg;    /* 0x814 NAND1 clock control */
    uint8_t reserved_0x818[20];
    uint32_t nand_gate_reset;    /* 0x82c NAND gate/reset control */
    uint32_t sd0_clk_cfg;    /* 0x830 MMC0 clock control */
    uint32_t sd1_clk_cfg;    /* 0x834 MMC1 clock control */
    uint32_t sd2_clk_cfg;    /* 0x838 MMC2 clock control */
    uint8_t reserved_0x83c[16];
    uint32_t sd_gate_reset;    /* 0x84c MMC gate/reset control */
    uint8_t reserved_0x850[188];
    uint32_t uart_gate_reset;    /* 0x90c UART gate/reset control */
    uint8_t reserved_0x910[12];
    uint32_t twi_gate_reset;    /* 0x91c I2C gate/reset control */
    uint8_t reserved_0x920[28];
    uint32_t scr_gate_reset;    /* 0x93c SCR gate/reset control */
    uint32_t spi0_clk_cfg;    /* 0x940 SPI0 clock control */
    uint32_t spi1_clk_cfg;    /* 0x944 SPI1 clock control */
    uint8_t reserved_0x948[8];
    uint32_t spif_clk_cfg;       /* 0x950 SPIF clock control */
    uint8_t reserved_0x954[24];
    uint32_t spi_gate_reset;    /* 0x96c SPI gate/reset control */
    uint8_t reserved_0x970[12];
    uint32_t emac_gate_reset;    /* 0x97c EMAC gate/reset control */
    uint8_t reserved_0x980[48];
    uint32_t ts_clk_cfg;        /* 0x9b0 TS clock control */
    uint8_t reserved_0x9b4[8];
    uint32_t ts_gate_reset;    /* 0x9bc TS gate/reset control */
    uint32_t irtx_clk_cfg;    /* 0x9c0 IR TX clock control */
    uint8_t reserved_0x9c4[8];
    uint32_t irtx_gate_reset;    /* 0x9cc IR TX gate/reset control */
    uint8_t reserved_0x9d0[32];
    uint32_t gpadc_gate_reset;    /*0x9ec gpadc gate/reset control*/
    uint8_t reserved_0x9f0[8];
    uint32_t ths_gate_reset;    /* 0x9fc THS gate/reset control */
    uint8_t reserved_0xa00[12];
    uint32_t i2s3_clk_cfg;    /* 0xa0c I2S3 clock control */
    uint32_t i2s0_clk_cfg;    /* 0xa10 I2S0 clock control */
    uint32_t i2s1_clk_cfg;    /* 0xa14 I2S1 clock control */
    uint32_t i2s2_clk_cfg;    /* 0xa18 I2S2 clock control */
    uint32_t i2s_gate_reset;    /* 0xa1c I2S gate/reset control */
    uint32_t spdif_clk_cfg;    /* 0xa20 SPDIF clock control */
    uint8_t reserved_0xa24[8];
    uint32_t spdif_gate_reset;    /* 0xa2c SPDIF gate/reset control */
    uint8_t reserved_0xa30[16];
    uint32_t dmic_clk_cfg;    /* 0xa40 DMIC clock control */
    uint8_t reserved_0xa44[8];
    uint32_t dmic_gate_reset;    /* 0xa4c DMIC gate/reset control */
    uint8_t reserved_0xa50[16];
    uint32_t ahub_clk_cfg;    /* 0xa60 Audio HUB clock control */
    uint8_t reserved_0xa64[8];
    uint32_t ahub_gate_reset;    /* 0xa6c Audio HUB gate/reset control */
    uint32_t usb0_clk_cfg;    /* 0xa70 USB0(OTG) clock control */
    uint32_t usb1_clk_cfg;    /* 0xa74 USB1(XHCI) clock control */
    uint8_t reserved_0xa78[4];
    uint32_t usb3_clk_cfg;    /* 0xa78 USB3 clock control */
    uint8_t reserved_0xa80[12];
    uint32_t usb_gate_reset;    /* 0xa8c USB gate/reset control */
    uint8_t reserved_0xa90[32];
    uint32_t pcie_ref_clk_cfg;    /* 0xab0 PCIE REF clock control */
    uint32_t pcie_axi_clk_cfg;    /* 0xab4 PCIE AXI clock control */
    uint32_t pcie_aux_clk_cfg;    /* 0xab8 PCIE AUX clock control */
    uint32_t dpss_top_bgr;    /* 0xabc DPSS TOP BUS Gating Reset */
    uint8_t reserved_0xac0[64];
    uint32_t hdmi_clk_cfg;    /* 0xb00 HDMI clock control */
    uint32_t hdmi_slow_clk_cfg;    /* 0xb04 HDMI slow clock control */
    uint8_t reserved_0xb08[8];
    uint32_t hdmi_cec_clk_cfg;    /* 0xb10 HDMI CEC clock control */
    uint8_t reserved_0xb14[8];
    uint32_t hdmi_gate_reset;    /* 0xb1c HDMI gate/reset control */
    uint8_t reserved_0xb20[60];
    uint32_t tcon_top_gate_reset;/* 0xb5c TCON TOP gate/reset control */
    uint32_t tcon_lcd0_clk_cfg;    /* 0xb60 TCON LCD0 clock control */
    uint8_t reserved_0xb64[24];
    uint32_t tcon_lcd_gate_reset;/* 0xb7c TCON LCD gate/reset control */
    uint32_t tcon_tv0_clk_cfg;    /* 0xb80 TCON TV0 clock control */
    uint8_t reserved_0xb84[24];
    uint32_t tcon_tv_gate_reset;    /* 0xb9c TCON TV gate/reset control */
    uint8_t reserved_0xba0[96];
    uint32_t csi_misc_clk_cfg;    /* 0xc00 CSI MISC clock control */
    uint32_t csi_top_clk_cfg;    /* 0xc04 CSI TOP clock control */
    uint32_t csi_mclk_cfg;    /* 0xc08 CSI Master clock control */
    uint8_t reserved_0xc0c[32];
    uint32_t csi_gate_reset;    /* 0xc2c CSI gate/reset control */
    uint8_t reserved_0xc30[16];
    uint32_t hdcp_clk_cfg;    /* 0xc40 HDCP clock control */
    uint8_t reserved_0xc44[8];
    uint32_t hdcp_gate_reset;    /* 0xc4c HDCP gate/reset control */
    uint8_t reserved_0xc50[688];
    uint32_t ccu_sec_switch;    /* 0xf00 CCU security switch */
    uint32_t gpadc_clk_sel;    /* 0xf04 PLL lock debugging control */
};

struct core_pll_freq_tbl {
    int FactorN;
    int FactorK;
    int FactorM;
    int FactorP;
    int pading;
};

/* Debugging */
#define DBG_INFO(...)
//#define DBG_INFO(...) printf(__VA_ARGS__)

/* V851S defines */
#define CONFIG_MACH_SUN8IW21
#define SUNXI_CCM_BASE         (0x02001000)
#define SUNXI_RTC_BASE         (0x07090000)
#define SPI_XFER_END           (1<<1)
#define SPI_XFER_BEGIN         (1<<0)

/* pll1 bit field */
#define CCM_PLL1_CTRL_EN		BIT(31)
#define CCM_PLL1_LOCK_EN		BIT(29)
#define CCM_PLL1_LOCK			BIT(28)
#define CCM_PLL1_CLOCK_TIME_2		(2 << 24)
#define CCM_PLL1_CTRL_N(n)		((n) << 8)

/* pll5 bit field */
#define CCM_PLL5_CTRL_EN		BIT(31)
#define CCM_PLL5_LOCK_EN		BIT(29)
#define CCM_PLL5_LOCK			BIT(28)
#define CCM_PLL5_CTRL_N(n)		((n) << 8)
#define CCM_PLL5_CTRL_DIV1(div1)	((div1) << 0)
#define CCM_PLL5_CTRL_DIV2(div0)	((div0) << 1)

/* pll6 bit field */
#define CCM_PLL6_CTRL_EN		BIT(31)
#define CCM_PLL6_LOCK_EN		BIT(29)
#define CCM_PLL6_LOCK			BIT(28)
#define CCM_PLL6_CTRL_N_SHIFT		8
#define CCM_PLL6_CTRL_N_MASK		(0xff << CCM_PLL6_CTRL_N_SHIFT)
#define CCM_PLL6_CTRL_DIV2_SHIFT	1
#define CCM_PLL6_CTRL_DIV2_MASK		(0x1 << CCM_PLL6_CTRL_DIV2_SHIFT)
#define CCM_PLL6_DEFAULT		0x48216310

/* cpu_axi bit field*/
#define CCM_CPU_AXI_MUX_MASK		(0x3 << 24)
#define CCM_CPU_AXI_MUX_PLL_CPUX	(0x3 << 24)

/* ahb0 bit field */
#define CCM_AHB3_DEFAULT		0x00000000

/* apb1 bit field */
#define CCM_APB1_DEFAULT		0x00000100

/* SPIF clock bit field */
#define CCM_SPIF_CTRL_M(x)		((x) - 1)
#define CCM_SPIF_CTRL_N(x)		((x) << 8)
#define CCM_SPIF_CTRL_HOSC		(0x0 << 24)
#define CCM_SPIF_CTRL_PERI400M		(0x1 << 24)
#define CCM_SPIF_CTRL_PERI300M		(0x2 << 24)
#define CCM_SPIF_CTRL_ENABLE		(0x1 << 31)
#define GET_SPIF_CLK_SOURECS(x)		(x == CCM_SPIF_CTRL_PERI400M ? 400000000 : 300000000)
#define CCM_SPIF_CTRL_PERI		CCM_SPIF_CTRL_PERI400M
#define SPIF_RESET_SHIFT		(20)
#define SPIF_GATING_SHIFT		(4)

/* spi gate/reset shift*/
#define RESET_SHIFT			    (16)
#define GATING_SHIFT			(0)

/* MMC clock bit field */
#define CCM_MMC_CTRL_M(x)		((x) - 1)
#define CCM_MMC_CTRL_N(x)		((x) << 8)
#define CCM_MMC_CTRL_OSCM24		(0x0 << 24)
#define CCM_MMC_CTRL_PLL6X2		(0x2 << 24)
#define CCM_MMC_CTRL_PLL_PERIPH2X2	(0x2 << 24)
#define CCM_MMC_CTRL_ENABLE		(0x1 << 31)
/* if doesn't have these delays */
#define CCM_MMC_CTRL_OCLK_DLY(a)	((void) (a), 0)
#define CCM_MMC_CTRL_SCLK_DLY(a)	((void) (a), 0)

/*CE*/
#define CE_CLK_SRC_MASK                   (0x7)
#define CE_CLK_SRC_SEL_BIT                (24)
#define CE_CLK_SRC                        (0x02)

#define CE_CLK_DIV_RATION_N_BIT           (0)
#define CE_CLK_DIV_RATION_N_MASK          (0)
#define CE_CLK_DIV_RATION_N               (0)

#define CE_CLK_DIV_RATION_M_BIT           (0)
#define CE_CLK_DIV_RATION_M_MASK          (0xF)
#define CE_CLK_DIV_RATION_M               (0)

#define CE_SCLK_ONOFF_BIT                 (31)
#define CE_SCLK_ON                        (1)

#define CE_GATING_BASE                    CCMU_CE_BGR_REG
#define CE_GATING_PASS                    (1)
#define CE_GATING_BIT                     (0)
#define CE_SYS_GATING_BIT                 (1)

#define CE_RST_REG_BASE                   CCMU_CE_BGR_REG
#define CE_RST_BIT                        (16)
#define CE_SYS_RST_BIT                    (17)
#define CE_DEASSERT                       (1)

#define CE_MBUS_GATING_MASK               (1)
#define CE_MBUS_GATING_BIT		  (2)
#define CE_MBUS_GATING			  (1)

#define FORCE_DETECTER_OUTPUT		  (1 << 7)
#define VCCIO_THRESHOLD_VOLTAGE_2_5	  (0 << 4)
#define VCCIO_THRESHOLD_VOLTAGE_2_6	  (1 << 4)
#define VCCIO_THRESHOLD_VOLTAGE_2_7	  (2 << 4)
#define VCCIO_THRESHOLD_VOLTAGE_2_8	  (3 << 4)
#define VCCIO_THRESHOLD_VOLTAGE_2_9	  (4 << 4)
#define VCCIO_THRESHOLD_VOLTAGE_3_0	  (5 << 4)
#define VCCIO_DET_BYPASS_EN		  (1 << 0)

// V851S SPI define ===================================================================================

#define SPI_MODULE_NUM		(4)
#define SPI_FIFO_DEPTH		(128)
#define MAX_FIFU		64
#define BULK_DATA_BOUNDARY	64	 /* can modify to adapt the application */
#define SPI_MAX_FREQUENCY	100000000 /* spi controller just support 80Mhz */

/* SPI Registers offsets from peripheral base address */
#define SPI_VER_REG          (0x00)  /* version number register */
#define SPI_GC_REG           (0x04)  /* global control register */
#define SPI_TC_REG           (0x08)  /* transfer control register */
#define SPI_INT_CTL_REG      (0x10)  /* interrupt control register */
#define SPI_INT_STA_REG      (0x14)  /* interrupt status register */
#define SPI_FIFO_CTL_REG     (0x18)  /* fifo control register */
#define SPI_FIFO_STA_REG     (0x1C)  /* fifo status register */
#define SPI_WAIT_CNT_REG     (0x20)  /* wait clock counter register */
#define SPI_CLK_CTL_REG      (0x24)  /* clock rate control register */
#define SPI_SDC_REG          (0x28)  /* sample delay control register */
#define SPI_BURST_CNT_REG    (0x30)  /* burst counter register */
#define SPI_TRANSMIT_CNT_REG (0x34)  /* transmit counter register */
#define SPI_BCC_REG          (0x38)  /* burst control counter register */
#define SPI_BATCR_REG        (0x40)  /* bit-aligned transfer configure register */
#define SPI_DMA_CTL_REG      (0x88)  /* DMA control register, only for 1639 */
#define SPI_TXDATA_REG       (0x200) /* tx data register */
#define SPI_RXDATA_REG       (0x300) /* rx data register */

/* SPI Global Control Register Bit Fields & Masks,default value:0x0000_0080 */
#define SPI_GC_EN		(0x1 <<  0) /* SPI module enable control 1:enable; 0:disable; default:0 */
#define SPI_GC_MODE		(0x1 <<  1) /* SPI function mode select 1:master; 0:slave; default:0 */
#define SPI_GC_TP_EN	(0x1 <<  7) /* SPI transmit stop enable 1:stop transmit data when RXFIFO is full; 0:ignore RXFIFO status; default:1 */
#define SPI_GC_SRST		(0x1 << 31) /* soft reset, write 1 will clear SPI control, auto clear to 0 */

/* SPI Transfer Control Register Bit Fields & Masks,default value:0x0000_0087 */
#define SPI_TC_PHA		(0x1 <<  0) /* SPI Clock/Data phase control,0: phase0,1: phase1;default:1 */
#define SPI_TC_POL		(0x1 <<  1) /* SPI Clock polarity control,0:low level idle,1:high level idle;default:1 */
#define SPI_TC_SPOL		(0x1 <<  2) /* SPI Chip select signal polarity control,default: 1,low effective like this:~~|_____~~ */
#define SPI_TC_SSCTL	(0x1 <<  3) /* SPI chip select control,default 0:SPI_SSx remains asserted between SPI bursts,1:negate SPI_SSx between SPI bursts */
#define SPI_TC_SS_MASK	(0x3 <<  4) /* SPI chip select:00-SPI_SS0;01-SPI_SS1;10-SPI_SS2;11-SPI_SS3*/
#define SPI_TC_SS_OWNER	(0x1 <<  6) /* SS output mode select default is 0:automatic output SS;1:manual output SS */
#define SPI_TC_SS_LEVEL	(0x1 <<  7) /* defautl is 1:set SS to high;0:set SS to low */
#define SPI_TC_DHB		(0x1 <<  8) /* Discard Hash Burst,default 0:receiving all spi burst in BC period 1:discard unused,fectch WTC bursts */
#define SPI_TC_DDB		(0x1 <<  9) /* Dummy burst Type,default 0: dummy spi burst is zero;1:dummy spi burst is one */
#define SPI_TC_RPSM		(0x1 << 10) /* select mode for high speed write,0:normal write mode,1:rapids write mode,default 0 */
#define SPI_TC_SDC		(0x1 << 11) /* master sample data control, 1: delay--high speed operation;0:no delay. */
#define SPI_TC_FBS		(0x1 << 12) /* LSB/MSB transfer first select 0:MSB,1:LSB,default 0:MSB first */
#define SPI_TC_SDM		(0x1 << 13) /* master sample data mode, SDM = 1:Normal Sample Mode, SDM = 0:Delay Sample Mode */
#define SPI_TC_SDC1		(0x1 << 15) /* master sample data mode, SDM = 1:Normal Sample Mode, SDM = 0:Delay Sample Mode */
#define SPI_TC_XCH		(0x1 << 31) /* Exchange burst default 0:idle,1:start exchange;when BC is zero,this bit cleared by SPI controller*/
#define SPI_TC_SS_BIT_POS	(4)

/* SPI Interrupt Control Register Bit Fields & Masks,default value:0x0000_0000 */
#define SPI_INTEN_RX_RDY	(0x1 <<  0) /* rxFIFO Ready Interrupt Enable,---used for immediately received,0:disable;1:enable */
#define SPI_INTEN_RX_EMP	(0x1 <<  1) /* rxFIFO Empty Interrupt Enable ---used for IRQ received */
#define SPI_INTEN_RX_FULL	(0x1 <<  2) /* rxFIFO Full Interrupt Enable ---seldom used */
#define SPI_INTEN_TX_ERQ	(0x1 <<  4) /* txFIFO Empty Request Interrupt Enable ---seldom used */
#define SPI_INTEN_TX_EMP	(0x1 <<  5) /* txFIFO Empty Interrupt Enable ---used  for IRQ tx */
#define SPI_INTEN_TX_FULL	(0x1 <<  6) /* txFIFO Full Interrupt Enable ---seldom used */
#define SPI_INTEN_RX_OVF	(0x1 <<  8) /* rxFIFO Overflow Interrupt Enable ---used for error detect */
#define SPI_INTEN_RX_UDR	(0x1 <<  9) /* rxFIFO Underrun Interrupt Enable ---used for error detect */
#define SPI_INTEN_TX_OVF	(0x1 << 10) /* txFIFO Overflow Interrupt Enable ---used for error detect */
#define SPI_INTEN_TX_UDR	(0x1 << 11) /* txFIFO Underrun Interrupt Enable ---not happened */
#define SPI_INTEN_TC		(0x1 << 12) /* Transfer Completed Interrupt Enable  ---used */
#define SPI_INTEN_SSI		(0x1 << 13) /* SSI interrupt Enable,chip select from valid state to invalid state,for slave used only */
#define SPI_INTEN_ERR		(SPI_INTEN_TX_OVF|SPI_INTEN_RX_UDR|SPI_INTEN_RX_OVF) /* NO txFIFO underrun */
#define SPI_INTEN_MASK		(0x77|(0x3f<<8))

/* SPI Interrupt Status Register Bit Fields & Masks,default value:0x0000_0022 */
#define SPI_INT_STA_RX_RDY	(0x1 <<  0) /* rxFIFO ready, 0:RX_WL < RX_TRIG_LEVEL,1:RX_WL >= RX_TRIG_LEVEL */
#define SPI_INT_STA_RX_EMP	(0x1 <<  1) /* rxFIFO empty, this bit is set when rxFIFO is empty */
#define SPI_INT_STA_RX_FULL	(0x1 <<  2) /* rxFIFO full, this bit is set when rxFIFO is full */
#define SPI_INT_STA_TX_RDY	(0x1 <<  4) /* txFIFO ready, 0:TX_WL > TX_TRIG_LEVEL,1:TX_WL <= TX_TRIG_LEVEL */
#define SPI_INT_STA_TX_EMP	(0x1 <<  5) /* txFIFO empty, this bit is set when txFIFO is empty */
#define SPI_INT_STA_TX_FULL	(0x1 <<  6) /* txFIFO full, this bit is set when txFIFO is full */
#define SPI_INT_STA_RX_OVF	(0x1 <<  8) /* rxFIFO overflow, when set rxFIFO has overflowed */
#define SPI_INT_STA_RX_UDR	(0x1 <<  9) /* rxFIFO underrun, when set rxFIFO has underrun */
#define SPI_INT_STA_TX_OVF	(0x1 << 10) /* txFIFO overflow, when set txFIFO has overflowed */
#define SPI_INT_STA_TX_UDR	(0x1 << 11) /* fxFIFO underrun, when set txFIFO has underrun */
#define SPI_INT_STA_TC		(0x1 << 12) /* Transfer Completed */
#define SPI_INT_STA_SSI		(0x1 << 13) /* SS invalid interrupt, when set SS has changed from valid to invalid */
#define SPI_INT_STA_ERR		(SPI_INT_STA_TX_OVF|SPI_INT_STA_RX_UDR|SPI_INT_STA_RX_OVF) /* NO txFIFO underrun */
#define SPI_INT_STA_MASK	(0x77|(0x3f<<8))

/* SPI FIFO Control Register Bit Fields & Masks,default value:0x0040_0001 */
#define SPI_FIFO_CTL_RX_LEVEL	(0xFF <<  0) /* rxFIFO reday request trigger level,default 0x1 */
#define SPI_FIFO_CTL_RX_DRQEN	(0x1  <<  8) /* rxFIFO DMA request enable,1:enable,0:disable */
#define SPI_FIFO_CTL_RX_TESTEN	(0x1  << 14) /* rxFIFO test mode enable,1:enable,0:disable */
#define SPI_FIFO_CTL_RX_RST	    (0x1  << 15) /* rxFIFO reset, write 1, auto clear to 0 */
#define SPI_FIFO_CTL_TX_LEVEL	(0xFF << 16) /* txFIFO empty request trigger level,default 0x40 */
#define SPI_FIFO_CTL_TX_DRQEN	(0x1  << 24) /* txFIFO DMA request enable,1:enable,0:disable */
#define SPI_FIFO_CTL_TX_TESTEN	(0x1  << 30) /* txFIFO test mode enable,1:enable,0:disable */
#define SPI_FIFO_CTL_TX_RST	    (0x1  << 31) /* txFIFO reset, write 1, auto clear to 0 */
#define SPI_FIFO_CTL_DRQEN_MASK	(SPI_FIFO_CTL_TX_DRQEN | SPI_FIFO_CTL_RX_DRQEN)

/* SPI FIFO Status Register Bit Fields & Masks,default value:0x0000_0000 */
#define SPI_FIFO_STA_RX_CNT	(0xFF <<  0) /* rxFIFO counter,how many bytes in rxFIFO */
#define SPI_FIFO_STA_RB_CNT	(0x7  << 12) /* rxFIFO read buffer counter,how many bytes in rxFIFO read buffer */
#define SPI_FIFO_STA_RB_WR	(0x1  << 15) /* rxFIFO read buffer write enable */
#define SPI_FIFO_STA_TX_CNT	(0xFF << 16) /* txFIFO counter,how many bytes in txFIFO */
#define SPI_FIFO_STA_TB_CNT	(0x7  << 28) /* txFIFO write buffer counter,how many bytes in txFIFO write buffer */
#define SPI_FIFO_STA_TB_WR	(0x1  << 31) /* txFIFO write buffer write enable */
#define SPI_RXCNT_BIT_POS	(0)
#define SPI_TXCNT_BIT_POS	(16)

/* SPI Wait Clock Register Bit Fields & Masks,default value:0x0000_0000 */
#define SPI_WAIT_WCC_MASK	(0xFFFF <<  0) /* used only in master mode: Wait Between Transactions */
#define SPI_WAIT_SWC_MASK	(0xF    << 16) /* used only in master mode: Wait before start dual data transfer in dual SPI mode */

/* SPI Clock Control Register Bit Fields & Masks,default:0x0000_0002 */
#define SPI_CLK_CTL_CDR2	(0xFF <<  0) /* Clock Divide Rate 2,master mode only : SPI_CLK = AHB_CLK/(2*(n+1)) */
#define SPI_CLK_CTL_CDR1	(0xF  <<  8) /* Clock Divide Rate 1,master mode only : SPI_CLK = AHB_CLK/2^n */
#define SPI_CLK_CTL_DRS		(0x1  << 12) /* Divide rate select,default,0:rate 1;1:rate 2 */
#define SPI_CLK_SCOPE		(SPI_CLK_CTL_CDR2+1)

/* SPI Master Burst Counter Register Bit Fields & Masks,default:0x0000_0000 */
/* master mode: when SMC = 1,BC specifies total burst number, Max length is 16Mbytes */
#define SPI_BC_CNT_MASK		(0xFFFFFF << 0) /* Total Burst Counter, tx length + rx length ,SMC=1 */

/* SPI Master Transmit Counter reigster default:0x0000_0000 */
#define SPI_TC_CNT_MASK		(0xFFFFFF << 0) /* Write Transmit Counter, tx length, NOT rx length!!! */

/* SPI Master Burst Control Counter reigster Bit Fields & Masks,default:0x0000_0000 */
#define SPI_BCC_STC_MASK	(0xFFFFFF <<  0) /* master single mode transmit counter */
#define SPI_BCC_DBC_MASK	(0xF	  << 24) /* master dummy burst counter */
#define SPI_BCC_DUAL_MODE	(0x1	  << 28) /* master dual mode RX enable */
#define SPI_BCC_QUAD_MODE	(0x1	  << 29) /* master quad mode RX enable */


#define SPI_PHA_ACTIVE_		(0x01)
#define SPI_POL_ACTIVE_		(0x02)

#define SPI_MODE_0_ACTIVE_	(0|0)
#define SPI_MODE_1_ACTIVE_	(0|SPI_PHA_ACTIVE_)
#define SPI_MODE_2_ACTIVE_	(SPI_POL_ACTIVE_|0)
#define SPI_MODE_3_ACTIVE_	(SPI_POL_ACTIVE_|SPI_PHA_ACTIVE_)
#define SPI_CS_HIGH_ACTIVE_	(0x04)
#define SPI_LSB_FIRST_ACTIVE_	(0x08)
#define SPI_DUMMY_ONE_ACTIVE_	(0x10)
#define SPI_RECEIVE_ALL_ACTIVE_	(0x20)

/* About SUNXI */
#define SUNXI_SPI_DEV_NAME	"spi"
#define SUNXI_SPI_CHAN_MASK(ch)	BIT(ch)

#define SUNXI_SPI_DRQ_RX(ch)	(DRQSRC_SPI0_RX + ch)
#define SUNXI_SPI_DRQ_TX(ch)	(DRQDST_SPI0_TX + ch)

/* About DMA */
#ifdef CONFIG_ARCH_SUN9IW1P1
#define SPI_DMA_WAIT_MODE	0xA5
#define SPI_DMA_SHAKE_MODE	0xEA
#define spi_set_dma_mode(base)	writel(SPI_DMA_SHAKE_MODE, base + SPI_DMA_CTL_REG)
#else
#define spi_set_dma_mode(base)
#endif

/* sample delay mode */
#define SPI_SAMP_MODE_EN	(1U << 2)
#define SPI_SAMP_DL_SW_EN	(1U << 7)
#define DELAY_NORMAL_SAMPLE	(0x100)
#define DELAY_0_5_CYCLE_SAMPLE	(0x000)
#define DELAY_1_CYCLE_SAMPLE	(0x010)
#define DELAY_1_5_CYCLE_SAMPLE	(0x110)
#define DELAY_2_CYCLE_SAMPLE	(0x101)
#define DELAY_2_5_CYCLE_SAMPLE	(0x001)
#define DELAY_3_CYCLE_SAMPLE	(0x011)

// V851S SPI define ===================================================================================

typedef struct {
	uint32_t  id;
	uint8_t   write_enable_cmd;
	uint8_t   large_erase_cmd;
	uint32_t  large_erase_size;
	uint8_t   small_erase_cmd;
	uint32_t  small_erase_size;
	uint8_t   program_cmd;
	uint32_t  program_size;
	char     *text_description;
} spi_flash_info_t;

spi_flash_info_t spi_flash_info[] = {
	{ .id = 0xEF40, .write_enable_cmd = 0x6,
	  .large_erase_cmd = 0xD8, .large_erase_size = 64 * 1024,
	  .small_erase_cmd = 0x20, .small_erase_size =  4 * 1024,
	  .program_cmd = 0x02, .program_size = 256,
	  .text_description = "Winbond W25Qxx" },
	{ .id = 0xC220, .write_enable_cmd = 0x6,
	  .large_erase_cmd = 0xD8, .large_erase_size = 64 * 1024,
	  .small_erase_cmd = 0x20, .small_erase_size =  4 * 1024,
	  .program_cmd = 0x02, .program_size = 256,
	  .text_description = "Macronix MX25Lxxxx" },
	{ .id = 0x1C70, .write_enable_cmd = 0x6,
	  .large_erase_cmd = 0xD8, .large_erase_size = 64 * 1024,
	  .small_erase_cmd = 0x20, .small_erase_size =  4 * 1024,
	  .program_cmd = 0x02, .program_size = 256,
	  .text_description = "Eon EN25QHxx" },
};

spi_flash_info_t default_spi_flash_info = {
	.id = 0x0000, .write_enable_cmd = 0x6,
	.large_erase_cmd = 0xD8, .large_erase_size = 64 * 1024,
	.small_erase_cmd = 0x20, .small_erase_size =  4 * 1024,
	.program_cmd = 0x02, .program_size = 256,
	.text_description = "Unknown",
};

spi_flash_info_t f35sqa001g_spi_flash_info = {
	.id = 0xcd71, .write_enable_cmd = 0x6,
	.large_erase_cmd = 0xD8, .large_erase_size = 64 * 2048, // block erase
	.small_erase_cmd = 0x00, .small_erase_size = 0,         // not applicated
	.program_cmd = 0x02, .program_size = 2048,              // page program
	.text_description = "Foresee F35SQA001G",
};

/*****************************************************************************/

uint32_t fel_readl(feldev_handle *dev, uint32_t addr);
void fel_writel(feldev_handle *dev, uint32_t addr, uint32_t val);
#define readl(addr)                 fel_readl(dev, (addr))
#define writel(val, addr)           fel_writel(dev, (addr), (val))

#define PA                          (0)
#define PB                          (1)
#define PC                          (2)

#define CCM_SPI0_CLK                (0x01C20000 + 0xA0)
#define CCM_AHB_GATING0             (0x01C20000 + 0x60)
#define CCM_AHB_GATE_SPI0           (1 << 20)
#define SUN6I_BUS_SOFT_RST_REG0     (0x01C20000 + 0x2C0)
#define SUN6I_SPI0_RST              (1 << 20)
#define SUNIV_PLL6_CTL              (0x01c20000 + 0x28)
#define SUNIV_AHB_APB_CFG           (0x01c20000 + 0x54)

#define H6_CCM_SPI0_CLK             (0x03001000 + 0x940)
#define H6_CCM_SPI_BGR              (0x03001000 + 0x96C)
#define H6_CCM_SPI0_GATE_RESET      (1 << 0 | 1 << 16)

#define SUNIV_GPC_SPI0              (2)
#define SUNXI_GPC_SPI0              (3)
#define SUN50I_GPC_SPI0             (4)
#define SUN8I_GPC_SPI0              (4)

#define SUN4I_CTL_ENABLE            (1 << 0)
#define SUN4I_CTL_MASTER            (1 << 1)
#define SUN4I_CTL_TF_RST            (1 << 8)
#define SUN4I_CTL_RF_RST            (1 << 9)
#define SUN4I_CTL_XCH               (1 << 10)

#define SUN6I_TCR_XCH               (1U << 31)

#define SUN4I_SPI0_CCTL             (spi_base(dev) + 0x1C)
#define SUN4I_SPI0_CTL              (spi_base(dev) + 0x08)
#define SUN4I_SPI0_RX               (spi_base(dev) + 0x00)
#define SUN4I_SPI0_TX               (spi_base(dev) + 0x04)
#define SUN4I_SPI0_FIFO_STA         (spi_base(dev) + 0x28)
#define SUN4I_SPI0_BC               (spi_base(dev) + 0x20)
#define SUN4I_SPI0_TC               (spi_base(dev) + 0x24)

#define SUN6I_SPI0_CCTL             (spi_base(dev) + 0x24)
#define SUN6I_SPI0_GCR              (spi_base(dev) + 0x04)
#define SUN6I_SPI0_TCR              (spi_base(dev) + 0x08)
#define SUN6I_SPI0_FIFO_STA         (spi_base(dev) + 0x1C)
#define SUN6I_SPI0_MBC              (spi_base(dev) + 0x30)
#define SUN6I_SPI0_MTC              (spi_base(dev) + 0x34)
#define SUN6I_SPI0_BCC              (spi_base(dev) + 0x38)
#define SUN6I_SPI0_TXD              (spi_base(dev) + 0x200)
#define SUN6I_SPI0_RXD              (spi_base(dev) + 0x300)

/* V851S CCMU */
#define V851S_CPU_CLK_REG           (0x02001000 + 0x0500)
#define V851S_CPU_GATING_REG        (0x02001000 + 0x0504)
#define V851S_AHB_CLK_REG           (0x02001000 + 0x0510)
#define V851S_SPI0_CLK_REG          (0x02001000 + 0x0940)
#define V851S_SRC_GATE_RST          (0x02001000 + 0x093C)
#define V851S_SPIF_CLK_CFG          (0x02001000 + 0x0950)
#define V851S_SPI_GATE_RST          (0x02001000 + 0x096C)

/* SPI0 controller */
#define SUN8I_SPI0_VER              (spi_base(dev) + 0x0000) // SPI Version Register
#define SUN8I_SPI0_GCR              (spi_base(dev) + 0x0004) // SPI Global Control Register
#define SUN8I_SPI0_TCR              (spi_base(dev) + 0x0008) // SPI Transfer Control Register
#define SUN8I_SPI0_IER              (spi_base(dev) + 0x0010) // SPI Interrupt Control Register
#define SUN8I_SPI0_ISR              (spi_base(dev) + 0x0014) // SPI Interrupt Status Register
#define SUN8I_SPI0_FCR              (spi_base(dev) + 0x0018) // SPI FIFO Control Register
#define SUN8I_SPI0_FSR              (spi_base(dev) + 0x001C) // SPI FIFO Status Register
#define SUN8I_SPI0_WCR              (spi_base(dev) + 0x0020) // SPI Wait Clock Register
#define SUN8I_SPI0_SAMP_DL          (spi_base(dev) + 0x0028) // SPI Sample Delay Control Register
#define SUN8I_SPI0_MBC              (spi_base(dev) + 0x0030) // SPI Master Burst Counter Register
#define SUN8I_SPI0_MTC              (spi_base(dev) + 0x0034) // SPI Master Transmit Counter Register
#define SUN8I_SPI0_BCC              (spi_base(dev) + 0x0038) // SPI Master Burst Control Register
#define SUN8I_SPI0_BATCR            (spi_base(dev) + 0x0040) // SPI Bit-Aligned Transfer Configure Register
#define SUN8I_SPI0_BA_CCR           (spi_base(dev) + 0x0044) // SPI Bit-Aligned Clock Configuration Register
#define SUN8I_SPI0_TBR              (spi_base(dev) + 0x0048) // SPI TX Bit Register
#define SUN8I_SPI0_RBR              (spi_base(dev) + 0x004C) // SPI RX Bit Register
#define SUN8I_SPI0_NDMA_MODE_CTL    (spi_base(dev) + 0x0088) // SPI Normal DMA Mode Control Register
#define SUN8I_SPI0_TXD              (spi_base(dev) + 0x0200) // SPI TX Data Register
#define SUN8I_SPI0_RXD              (spi_base(dev) + 0x0300) // SPI RX Data Register

/* SPI0 bit field */
#define SUN8I_TCR_XCH		        (0x1 << 31)

#define CCM_SPI0_CLK_DIV_BY_2       (0x1000)
#define CCM_SPI0_CLK_DIV_BY_4       (0x1001)
#define CCM_SPI0_CLK_DIV_BY_6       (0x1002)
#define CCM_SPI0_CLK_DIV_BY_32      (0x100f)

void delay(void)
{
    /* TODO: Try to find and fix the bug, which needs this workaround */
    struct timespec req = { .tv_nsec = 250000000 }; /* 250ms */
    nanosleep(&req, NULL);
}

uint32_t clock_get_pll6(feldev_handle *dev)
{
	struct sunxi_ccm_reg *const ccm = (struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	uint32_t reg_val;
	uint32_t factor_n, factor_m0, factor_m1, factor_p0, pll6;

	reg_val = readl((uint32_t)&ccm->pll6_cfg);

	factor_p0 = ((reg_val >> 16) & 0x7) + 1;
	factor_n = ((reg_val >> 8) & 0xff) + 1;
	factor_m0 = ((reg_val >> 0) & 0x01) + 1;
	factor_m1 = ((reg_val >> 1) & 0x01) + 1;
	pll6 = (24 * factor_n /factor_m0/factor_m1/factor_p0)>>1;

	return pll6;
}

uint32_t clock_get_corepll(feldev_handle *dev)
{
	struct sunxi_ccm_reg *const ccm = (struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	uint32_t reg_val;
	uint32_t div_m, div_p;
	uint32_t factor_n;
	uint32_t clock, clock_src;

	reg_val   = readl((uint32_t)&ccm->cpu_axi_cfg);
	clock_src = (reg_val >> 24) & 0x03;

	switch (clock_src) {
	case 0://OSC24M
		clock = 24;
		break;
	case 1://RTC32K
		clock = 32/1000 ;
		break;
	case 2://RC16M
		clock = 16;
		break;
	case 3://PLL_CPUX
		div_p	 = 1<<((reg_val >>16) & 0x3);
		reg_val  = readl((uint32_t)&ccm->pll1_cfg);
		factor_n = ((reg_val >> 8) & 0xff) + 1;
		div_m    = ((reg_val >> 0) & 0x3) + 1;

		clock = 24*factor_n/div_m/div_p;
		break;
	default:
		return 0;
	}
	return clock;
}

uint32_t clock_get_axi(feldev_handle *dev)
{
	struct sunxi_ccm_reg *const ccm = (struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	uint32_t reg_val = 0;
	uint32_t factor = 0;
	uint32_t clock = 0;

	reg_val   = readl((uint32_t)&ccm->cpu_axi_cfg);
	factor    = ((reg_val >> 0) & 0x03) + 1;
	clock = clock_get_corepll(dev)/factor;

	return clock;
}

uint32_t clock_get_ahb(feldev_handle *dev)
{
	struct sunxi_ccm_reg *const ccm = (struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	uint32_t reg_val = 0;
	uint32_t factor_m = 0, factor_n = 0;
	uint32_t clock = 0;
	uint32_t src = 0, src_clock = 0;

	reg_val = readl((uint32_t)&ccm->psi_ahb1_ahb2_cfg);
	src = (reg_val >> 24) & 0x3;
	factor_m  = ((reg_val >> 0) & 0x03) + 1;
	factor_n  = 1<< ((reg_val >> 8) & 0x03);

	switch (src) {
	case 0://OSC24M
		src_clock = 24;
		break;
	case 1://CCMU_32K
		src_clock = 32/1000;
		break;
	case 2:	//RC16M
		src_clock = 16;
		break;
	case 3://PLL_PERI0(1X)
		src_clock = clock_get_pll6(dev);
		break;
	default:
			return 0;
	}

	clock = src_clock/factor_m/factor_n;

	return clock;
}

uint32_t clock_get_apb1(feldev_handle *dev)
{
	struct sunxi_ccm_reg *const ccm = (struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	uint32_t reg_val = 0;
	uint32_t src = 0, src_clock = 0;
	uint32_t clock = 0, factor_m = 0, factor_n = 0;

	reg_val = readl((uint32_t)&ccm->apb1_cfg);
	factor_m  = ((reg_val >> 0) & 0x03) + 1;
	factor_n  = 1<<((reg_val >> 8) & 0x03);
	src = (reg_val >> 24)&0x3;

	switch (src) {
	case 0://OSC24M
		src_clock = 24;
		break;
	case 1://CCMU_32K
		src_clock = 32/1000;
		break;
	case 2:	//PSI
		src_clock = clock_get_ahb(dev);
		break;
	case 3://PLL_PERI0(1X)
		src_clock = clock_get_pll6(dev);
		break;
	default:
		return 0;
	}

	clock = src_clock/factor_m/factor_n;

	return clock;
}

uint32_t clock_get_pll_ddr(feldev_handle *dev)
{
	struct sunxi_ccm_reg *const ccm = (struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	uint32_t reg_val;
	uint32_t clock = 0;
	uint32_t clock_src = 0;

	reg_val = readl((uint32_t)&ccm->dram_clk_cfg);
	clock_src = (reg_val >> 24) & 0x03;

	switch (clock_src) {
	case 0:/*peri(2x)*/
		clock = clock_get_pll6(dev) * 2;
		break;
	case 1:/*RTC32K*/
		clock = 800;
		break;
	case 2:/*pll_audio0*/
		clock = 0;
		break;
	case 3:
		clock = 0;
		break;
	default:
		return 0;
	}

	return clock;
}

uint32_t clock_get_mbus(feldev_handle *dev)
{
	uint32_t clock;

	clock = clock_get_pll_ddr(dev);
	clock = clock/4;

	return clock;
}

static int clk_get_pll_para(struct core_pll_freq_tbl *factor, int pll_clk)
{
	int index;
	int index_p;

	index = pll_clk / 24;
	for (index_p = 0; index_p < 3; index_p++) {
		factor->FactorP = index_p;
		/* printf("pll_clk:%d  index:%d\n", pll_clk, index * 24 / (1 << index_p)); */
		if (pll_clk == (index * 24 / (1 << index_p))) {
			break;
		}
	}
	if (index_p >= 3) {
		factor->FactorP = 0;
	}
	factor->FactorN = (index - 1);
	factor->FactorM = 0;

	return 0;
}

void rtc_set_vccio_det_spare(feldev_handle *dev)
{
	uint32_t val = 0;
	val = readl(SUNXI_RTC_BASE + 0x1f4);
	val &= ~(0xff << 4);
	val |= (VCCIO_THRESHOLD_VOLTAGE_2_9 | FORCE_DETECTER_OUTPUT);
	val &= ~VCCIO_DET_BYPASS_EN;
	writel(val, SUNXI_RTC_BASE + 0x1f4);
}

int clock_set_corepll(feldev_handle *dev, int frequency)
{
	unsigned int reg_val = 0;
	struct sunxi_ccm_reg *const ccm = (struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	struct core_pll_freq_tbl pll_factor;

	/*fix reset circuit detection threshold*/
	rtc_set_vccio_det_spare(dev);

	if (frequency == clock_get_corepll(dev))
		return 0;
	else if (frequency >= 1440)
		frequency = 1440;

	/* switch to 24M*/
	reg_val = readl((uint32_t)&ccm->cpu_axi_cfg);
	reg_val &= ~(0x07 << 24);
	writel(reg_val, (uint32_t)&ccm->cpu_axi_cfg);
	delay();

	/*pll output disable*/
	reg_val = readl((uint32_t)&ccm->pll1_cfg);
	reg_val &= ~(0x01 << 31);
	writel(reg_val, (uint32_t)&ccm->pll1_cfg);

	/*get config para form freq table*/
	clk_get_pll_para(&pll_factor, frequency);

	reg_val = readl((uint32_t)&ccm->pll1_cfg);
	reg_val &= ~((0xff << 8)  | (0x03 << 0));
	reg_val |= (pll_factor.FactorN << 8) | (pll_factor.FactorM << 0) ;
	writel(reg_val, (uint32_t)&ccm->pll1_cfg);
	delay();

	reg_val = readl((uint32_t)&ccm->cpu_axi_cfg);
	reg_val &= ~(0x03 << 16);
	reg_val |= (pll_factor.FactorP << 16);
	writel(reg_val, (uint32_t)&ccm->cpu_axi_cfg);
	delay();

	/*enable lock*/
	reg_val = readl((uint32_t)&ccm->pll1_cfg);
	reg_val |=  (0x1 << 29);
	writel(reg_val, (uint32_t)&ccm->pll1_cfg);

	/*enable pll*/
	reg_val = readl((uint32_t)&ccm->pll1_cfg);
	reg_val |=	(0x1 << 31);
	writel(reg_val, (uint32_t)&ccm->pll1_cfg);

#ifndef FPGA_PLATFORM
	do {
		reg_val = readl((uint32_t)&ccm->pll1_cfg);
	} while (!(reg_val & (0x1 << 28)));
#endif

	/*disable lock*/
	reg_val = readl((uint32_t)&ccm->pll1_cfg);
	reg_val &= ~(0x1 << 29);
	writel(reg_val, (uint32_t)&ccm->pll1_cfg);

	/* switch clk src to COREPLL*/
	reg_val = readl((uint32_t)&ccm->cpu_axi_cfg);
	reg_val &= ~(0x07 << 24);
	reg_val |=  (0x03 << 24);
	writel(reg_val, (uint32_t)&ccm->cpu_axi_cfg);

	return  0;
}

static int sunxi_spi_clk_init(feldev_handle *dev, uint32_t mod_clk)
{
	struct sunxi_ccm_reg *const ccm = (struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	uint32_t source_clk = 0;
	uint32_t rval;
	uint32_t m, n, div, factor_m;

	/* SCLK = src/M/N */
	/* N: 00:1 01:2 10:4 11:8 */
    /* M: factor_m + 1 */
#ifdef FPGA_PLATFORM
	n = 0;
	m = 1;
	factor_m = m - 1;
	rval = (1U << 31);
	source_clk = 24000000;
#else
#if defined(CONFIG_MACH_SUN8IW21)
	source_clk = 300000000;
#else
	source_clk = clock_get_pll6(dev) * 1000000;
#endif
	//printf("source_clk: %d Hz, mod_clk: %d Hz\n", source_clk, mod_clk);

	div = (source_clk + mod_clk - 1) / mod_clk;
	div = div == 0 ? 1 : div;
	if (div > 128) {
		m = 1;
		n = 0;
		return -1;
	} else if (div > 64) {
		n = 3;
		m = div >> 3;
	} else if (div > 32) {
		n = 2;
		m = div >> 2;
	} else if (div > 16) {
		n = 1;
		m = div >> 1;
	} else {
		n = 0;
		m = div;
	}

	factor_m = m - 1;
#if defined(CONFIG_MACH_SUN8IW11)
	rval = (1U << 31) | (0x1 << 24) | (n << 16) | factor_m;
#else
	rval = (1U << 31) | (0x1 << 24) | (n << 8) | factor_m;
#endif

#endif
	writel(rval, (uint32_t)&ccm->spi0_clk_cfg);

#if defined(CONFIG_MACH_SUN8IW11)
	/* spi reset */
	writel(readl(&ccm->ahb_reset0_cfg) & ~(1 << 20), &ccm->ahb_reset0_cfg);
	writel(readl(&ccm->ahb_reset0_cfg) | (1 << 20), &ccm->ahb_reset0_cfg);

	/* spi gating */
	writel(readl(&ccm->ahb_gate0) | (1 << 20), &ccm->ahb_gate0);
#else

    /* spi0 reset */
    writel(0, (uint32_t)&ccm->spi_gate_reset);
    writel(1 << 16, (uint32_t)&ccm->spi_gate_reset);
    delay();
    /* spi0 gating */
    writel((1 << 16) | (1 << 0), (uint32_t)&ccm->spi_gate_reset);

#endif

    DBG_INFO("src: %d Hz, spic: %d Hz, n=%d, m=%d\n", source_clk, source_clk/(1 << n)/m, n, m);

	return 0;
}

static int sunxi_get_spic_clk(feldev_handle *dev)
{
	struct sunxi_ccm_reg *const ccm = (struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	uint32_t reg_val = 0;
	uint32_t src = 0, clk = 0, sclk_freq = 0;
	uint32_t n, m;

	reg_val = readl((uint32_t)&ccm->spi0_clk_cfg);
	src = (reg_val >> 24)&0x7;
	n = (reg_val >> 8)&0x3;
	m = ((reg_val >> 0)&0xf) + 1;

	switch(src) {
		case 0:
			clk = 24000000;
			break;
		case 1:
#if defined(CONFIG_MACH_SUN8IW21)
			clk = 300000000;
#else
			clk = clock_get_pll6(dev) * 1000000;
#endif
			break;
		default:
			clk = 0;
			break;
	}
	sclk_freq = clk / (1 << n) / m;
	DBG_INFO("sclk_freq = %d Hz, reg_val: %x , n=%d, m=%d\n", sclk_freq, reg_val, n, m);
	return sclk_freq;
}

#define V851S_SPI0_BASE (0x04025000)
static void spi_config_tc(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_TC_REG);
	uint32_t sclk_freq = 0;

	sclk_freq = sunxi_get_spic_clk(dev);

	if (sclk_freq >= 60000000)
		reg_val |= SPI_TC_SDC;
	else if (sclk_freq <= 24000000)
		reg_val |= SPI_TC_SDM;
	else
		reg_val &= ~(SPI_TC_SDM | SPI_TC_SDC);

	reg_val |= SPI_TC_DHB | SPI_TC_SS_LEVEL | SPI_TC_SPOL;
	
    /* SPI MODE_0 CPOL=0, CPHA=0 */
    reg_val &= ~(SPI_TC_PHA | SPI_TC_POL);

    /* SDC = 0 */
    reg_val &= ~SPI_TC_SDC; /* very important */

    /* SDM = 1 */
    reg_val |= SPI_TC_SDM; /* very important */

    writel(reg_val, V851S_SPI0_BASE + SPI_TC_REG);

    DBG_INFO("SPI_TC_REG = %X\r\n", readl(V851S_SPI0_BASE + SPI_TC_REG));

}

void spi_init_clk(feldev_handle *dev, uint32_t spi_clk)
{
    /* Init spi clock */
    sunxi_spi_clk_init(dev, spi_clk);

    /* Config SPI */
    spi_config_tc(dev);
}

/* soft reset spi controller */
static void spi_soft_reset(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_GC_REG);

	reg_val |= SPI_GC_SRST;
	writel(reg_val, V851S_SPI0_BASE + SPI_GC_REG);
}

/* enable spi bus */
static void spi_enable_bus(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_GC_REG);

	reg_val |= SPI_GC_EN;
	writel(reg_val, V851S_SPI0_BASE + SPI_GC_REG);
}

/* config chip select */
static void spi_set_cs(feldev_handle *dev, uint32_t chipselect)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_TC_REG);

	if (chipselect < 4) {
		reg_val &= ~SPI_TC_SS_MASK;/* SS-chip select, clear two bits */
		reg_val |= chipselect << SPI_TC_SS_BIT_POS;/* set chip select */
		writel(reg_val, V851S_SPI0_BASE + SPI_TC_REG);
	} else {
		printf("Chip Select set fail! cs = %d\n", chipselect);
	}
}

/* set master mode */
static void spi_set_master(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_GC_REG);

	reg_val |= SPI_GC_MODE;
	writel(reg_val, V851S_SPI0_BASE + SPI_GC_REG);
}

/* set spi clock
 * cdr1: spi_sclk =source_clk/(2^cdr1_M)
 * cdr2: spi_sclk =source_clk/(2*(cdr2_N+1))
 * spi_clk : the spi final clk.
 * ahb_clk: source_clk - the clk from ccmu config, spic clk src is osc24M or peri0_1X.
*/

static void spi_set_clk(feldev_handle *dev, uint32_t spi_clk, uint32_t ahb_clk, uint32_t cdr)
{
	uint32_t reg_val = 0;
	uint32_t div_clk = 0;

	DBG_INFO("set spi clock %d, mclk %d\n", spi_clk, ahb_clk);
	reg_val = readl(V851S_SPI0_BASE + SPI_CLK_CTL_REG);

	/* CDR2 */
	if (cdr) {
		div_clk = ahb_clk / (spi_clk * 2) - 1;
		reg_val &= ~SPI_CLK_CTL_CDR2;
		reg_val |= (div_clk | SPI_CLK_CTL_DRS);
		DBG_INFO("CDR2 - n = %d\n", div_clk);
	} else { /* CDR1 */
		while (ahb_clk > spi_clk) {
			div_clk++;
			ahb_clk >>= 1;
		}
		reg_val &= ~(SPI_CLK_CTL_CDR1 | SPI_CLK_CTL_DRS);
		reg_val |= (div_clk << 8);
		DBG_INFO("CDR1 - n = %d\n", div_clk);
	}

	writel(reg_val, V851S_SPI0_BASE + SPI_CLK_CTL_REG);

    DBG_INFO("SPI_CLK_CTL_REG = %X\r\n", readl(V851S_SPI0_BASE + SPI_CLK_CTL_REG));
}

/* set ss level */
static void spi_ss_level(feldev_handle *dev, uint32_t hi_lo)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_TC_REG);

	hi_lo &= 0x1;
	if (hi_lo)
		reg_val |= SPI_TC_SS_LEVEL;
	else
		reg_val &= ~SPI_TC_SS_LEVEL;
	writel(reg_val, V851S_SPI0_BASE + SPI_TC_REG);
}

/* enable transmit pause */
static void spi_enable_tp(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_GC_REG);

	reg_val |= SPI_GC_TP_EN;
	writel(reg_val, V851S_SPI0_BASE + SPI_GC_REG);
}

/* set ss control */
static void spi_ss_owner(feldev_handle *dev, uint32_t on_off)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_TC_REG);

	on_off &= 0x1;
	if (on_off)
		reg_val |= SPI_TC_SS_OWNER;
	else
		reg_val &= ~SPI_TC_SS_OWNER;
	writel(reg_val, V851S_SPI0_BASE + SPI_TC_REG);
}

/* config bit-aligned transfer  */
static void spi_config_batcr(feldev_handle *dev)
{
    uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_BATCR_REG);

    /* Configure the length of serial data frame (burst) of RX */
    reg_val |= (8 << 16); // 8 bits

    /* Configure the length of serial data frame (burst) of TX */
    reg_val |= (8 << 8);  // 8 bits

    // Work Mode Select
    // 00: Data frame is byte aligned in standard SPI, dual-output/dual
    // input SPI, dual IO SPI, and quad-output/quad-input SPI
    // 01: Reserved
    // 10: Data frame is bit aligned in 3-wire SPI
    // 11: Data frame is bit aligned in standard SPI
    reg_val |= 0x3; // bit aligned

    writel(reg_val, V851S_SPI0_BASE + SPI_BATCR_REG);
}

/* disable irq type */
static void spi_disable_irq(feldev_handle *dev, uint32_t bitmap)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_INT_CTL_REG);

	bitmap &= SPI_INTEN_MASK;
	reg_val &= ~bitmap;
	writel(reg_val, V851S_SPI0_BASE + SPI_INT_CTL_REG);
}

/* query irq pending */
static uint32_t spi_qry_irq_pending(feldev_handle *dev)
{
	return (SPI_INT_STA_MASK & readl(V851S_SPI0_BASE + SPI_INT_STA_REG));
}

/* clear irq pending */
static void spi_clr_irq_pending(feldev_handle *dev, uint32_t pending_bit)
{
	pending_bit &= SPI_INT_STA_MASK;
	writel(pending_bit, V851S_SPI0_BASE + SPI_INT_STA_REG);
}

/* query txfifo bytes */
static uint32_t spi_query_txfifo(feldev_handle *dev)
{
	uint32_t reg_val = (SPI_FIFO_STA_TX_CNT & readl(V851S_SPI0_BASE + SPI_FIFO_STA_REG));

	reg_val >>= SPI_TXCNT_BIT_POS;
	return reg_val;
}

/* query rxfifo bytes */
static uint32_t spi_query_rxfifo(feldev_handle *dev)
{
	uint32_t reg_val = (SPI_FIFO_STA_RX_CNT & readl(V851S_SPI0_BASE + SPI_FIFO_STA_REG));

	reg_val >>= SPI_RXCNT_BIT_POS;
	return reg_val;
}

/* reset fifo */
static void spi_reset_fifo(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_FIFO_CTL_REG);

	reg_val |= (SPI_FIFO_CTL_RX_RST|SPI_FIFO_CTL_TX_RST);
	/* Set the trigger level of RxFIFO/TxFIFO. */
	reg_val &= ~(SPI_FIFO_CTL_RX_LEVEL|SPI_FIFO_CTL_TX_LEVEL);
    reg_val |= (0x40<<16) | 0x40; // TX_TRIG_LEVEL = 64, RX_TRIG_LEVEL = 64
	writel(reg_val, V851S_SPI0_BASE + SPI_FIFO_CTL_REG);
}

static int sunxi_spi_cpu_writel(feldev_handle *dev, const unsigned char *buf, unsigned int len)
{
	unsigned char *tx_buf = (unsigned char *)buf;
    unsigned int i, word_cnt, rbyte_cnt;
    uint32_t data;
    unsigned char *pdata = (unsigned char *)&data;

    word_cnt = len / 4;
    rbyte_cnt = len % 4;

    if(word_cnt) {
        for(i = 0; i < word_cnt; i++){
            pdata[0] = *tx_buf++;
            pdata[1] = *tx_buf++;
            pdata[2] = *tx_buf++;
            pdata[3] = *tx_buf++;
            /* wait for TX fifo ready */
            while(!(readl(V851S_SPI0_BASE + SPI_INT_STA_REG) & SPI_INT_STA_TX_RDY));
            writel(data, V851S_SPI0_BASE + SPI_TXDATA_REG);
        }
    }

    if(rbyte_cnt) {
        for(i = 0; i < rbyte_cnt; i++){
            pdata[i] = *tx_buf++;
        }
        /* wait for TX fifo ready */
        while(!(readl(V851S_SPI0_BASE + SPI_INT_STA_REG) & SPI_INT_STA_TX_RDY));
		writel(data, V851S_SPI0_BASE + SPI_TXDATA_REG);
    }

	return 0;
}

static int sunxi_spi_cpu_readl(feldev_handle *dev, unsigned char *buf, unsigned int len)
{
	unsigned char *rx_buf = buf;
    unsigned int i, act_len, word_cnt, rbyte_cnt;
    uint32_t data;

    /*
     * because fel only supports 32bit access so we need
     * to compine into word, rxfifo underun will occur if len is not
     * multiple of 4 bytes
     */
    act_len = spi_query_rxfifo(dev);
    word_cnt = act_len / 4;
    rbyte_cnt = act_len % 4;

    if(word_cnt) {
        for(i = 0; i < word_cnt; i++)
        {
            data = readl(V851S_SPI0_BASE + SPI_RXDATA_REG);
            *rx_buf++ = (unsigned char)data;
            *rx_buf++ = (unsigned char)(data >> 8);
            *rx_buf++ = (unsigned char)(data >> 16);
            *rx_buf++ = (unsigned char)(data >> 24);
        }
    }

    if(rbyte_cnt) {
        data = readl(V851S_SPI0_BASE + SPI_RXDATA_REG);
        for(i = 0; i < rbyte_cnt; i++)
        {
            *rx_buf++ = (unsigned char)data;
            data >>= 8;
        }
    }

	return 0;
}

/* start spi transfer */
static void spi_start_xfer(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_TC_REG);

	reg_val |= SPI_TC_XCH;
	writel(reg_val, V851S_SPI0_BASE + SPI_TC_REG);
}

/* set transfer total length BC, transfer length TC and single transmit length STC */
static void spi_set_bc_tc_stc(feldev_handle *dev, uint32_t tx_len, uint32_t rx_len, uint32_t stc_len, uint32_t dummy_cnt)
{
    // SPI_MBC
    // MBC
    // Master Burst Counter
    // In master mode, this field specifies the total burst number. The
    // total transfer data include the TXD, RXD, and dummy burst.
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_BURST_CNT_REG);

	reg_val &= ~SPI_BC_CNT_MASK;
	reg_val |= (SPI_BC_CNT_MASK & (tx_len + rx_len + dummy_cnt));
	writel(reg_val, V851S_SPI0_BASE + SPI_BURST_CNT_REG);

    // SPI_MTC
    // MWTC
    // Master Write Transmit Counter
    // In master mode, this field specifies the burst number that should
    // be sent to TXFIFO before automatically sending dummy bursts. For
    // saving bus bandwidth, the dummy bursts (all zero bits or all one
    // bits) are sent by SPI Controller automatically.-
	reg_val = readl(V851S_SPI0_BASE + SPI_TRANSMIT_CNT_REG);
	reg_val &= ~SPI_TC_CNT_MASK;
	reg_val |= (SPI_TC_CNT_MASK & tx_len);
	writel(reg_val, V851S_SPI0_BASE + SPI_TRANSMIT_CNT_REG);

    // SPI_BCC
    // Quad_EN[29]
    // DRM [28]
    // DBC [27:24]
    // Master Dummy Burst Counter
    // In master mode, this field specifies the burst number that should
    // be sent before receiving in dual SPI mode. The data does not care
    // by the device.
    // STC [23:0]
    // Master Single Mode Transmit Counter
    // In master mode, this field specifies the burst number that should
    // be sent in the single mode before automatically sending dummy
    // bursts. This is the first transmit counter in all bursts.
	reg_val = readl(V851S_SPI0_BASE + SPI_BCC_REG);
	reg_val &= ~SPI_BCC_STC_MASK;
	reg_val |= (SPI_BCC_STC_MASK & stc_len);
	reg_val &= ~(0xf << 24);
	reg_val |= (dummy_cnt << 24);
	writel(reg_val, V851S_SPI0_BASE + SPI_BCC_REG);
}

static void spi_disable_dual(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_BCC_REG);
	reg_val &= ~SPI_BCC_DUAL_MODE;
	writel(reg_val, V851S_SPI0_BASE + SPI_BCC_REG);
}

static void spi_enable_dual(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_BCC_REG);
	reg_val &= ~SPI_BCC_QUAD_MODE;
	reg_val |= SPI_BCC_DUAL_MODE;
	writel(reg_val, V851S_SPI0_BASE + SPI_BCC_REG);
}

static void spi_disable_quad(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_BCC_REG);

	reg_val &= ~SPI_BCC_QUAD_MODE;
	writel(reg_val, V851S_SPI0_BASE + SPI_BCC_REG);
}

static void spi_enable_quad(feldev_handle *dev)
{
	uint32_t reg_val = readl(V851S_SPI0_BASE + SPI_BCC_REG);

	reg_val |= SPI_BCC_QUAD_MODE;
	writel(reg_val, V851S_SPI0_BASE + SPI_BCC_REG);
}

void spi_samp_dl_sw_status(feldev_handle *dev, unsigned int status)
{
	unsigned int rval = readl(V851S_SPI0_BASE + SPI_SDC_REG);

	if (status)
		rval |= SPI_SAMP_DL_SW_EN;
	else
		rval &= ~SPI_SAMP_DL_SW_EN;

	writel(rval, V851S_SPI0_BASE +  SPI_SDC_REG);
}

static void spi_samp_mode(feldev_handle *dev, unsigned int status)
{
	unsigned int rval = readl(V851S_SPI0_BASE + SPI_GC_REG);

	if (status)
		rval |= SPI_SAMP_MODE_EN;
	else
		rval &= ~SPI_SAMP_MODE_EN;

	writel(rval, V851S_SPI0_BASE + SPI_GC_REG);
}

#if 0
#define SPINOR_OP_READ_1_1_4	0x6b	/* Read data bytes (Quad Output SPI) */
#define SPINOR_OP_READ_1_1_4_4B	0x6c	/* Read data bytes (Quad Output SPI) */
#define SPINOR_OP_PP_1_1_4	    0x32	/* Quad page program */
#define SPINOR_OP_PP_1_1_4_4B	0x34	/* Quad page program */
#define SPINOR_OP_READ_1_1_2	0x3b	/* Read data bytes (Dual Output SPI) */
#define SPINOR_OP_READ_1_1_2_4B	0x3c	/* Read data bytes (Dual Output SPI) */

static int sunxi_spi_mode_check(feldev_handle *dev, uint32_t tcnt, uint32_t rcnt, uint8_t cmd)
{
	/* single mode transmit counter*/
	unsigned int stc = 0;

	if (SPINOR_OP_READ_1_1_4 == cmd || SPINOR_OP_READ_1_1_4_4B == cmd ||
		SPINOR_OP_PP_1_1_4 == cmd || SPINOR_OP_PP_1_1_4_4B == cmd) {
		/*tcnt is cmd len, use single mode to transmit*/
		/*rcnt is  the len of recv data, use quad mode to transmit*/
		stc = tcnt;
		spi_enable_quad(dev);
		spi_set_bc_tc_stc(dev, tcnt, rcnt, stc, 0);
	} else if (SPINOR_OP_READ_1_1_2 == cmd || SPINOR_OP_READ_1_1_2_4B == cmd) {
		/*tcnt is cmd len, use single mode to transmit*/
		/*rcnt is  the len of recv data, use dual mode to transmit*/
		stc = tcnt;
		spi_enable_dual(dev);
		spi_set_bc_tc_stc(dev, tcnt, rcnt, stc, 0);
	} else {
		/*tcnt is the len of cmd, rcnt is the len of recv data. use single mode to transmit*/
		stc = tcnt + rcnt;
		spi_disable_dual(dev);
		spi_disable_quad(dev);
		spi_set_bc_tc_stc(dev, tcnt, rcnt, stc, 0);
	}

	return 0;
}
#endif

int spi_xfer(feldev_handle *dev, const uint8_t *tx, size_t tx_len, size_t dummy_len, uint8_t *rx, size_t rx_len)
{
	int timeout = 0xfffff;
    uint32_t redundant_txfifo;

	/* No data */
	if (!tx && !rx)
		return 0;

	spi_disable_irq(dev, 0xffffffff);
	spi_clr_irq_pending(dev, 0xffffffff);

	spi_set_bc_tc_stc(dev, tx_len, rx_len, tx_len, dummy_len);
    spi_ss_level(dev, 1);

	/* tx */
	if (tx_len) {
		if (sunxi_spi_cpu_writel(dev, tx, tx_len))
			return -1;
	}

    /* start transfer */
    spi_start_xfer(dev);

	/* check tx/rx finish */
	/* wait transfer complete */
	while (!(spi_qry_irq_pending(dev)&SPI_INT_STA_TC)) {
		timeout--;
		if (!timeout) {
			printf("SPI_ISR time_out \n");
			return -1;
		}
        delay();
	}

	/* check SPI_EXCHANGE when SPI_MBC is 0 */
	if (readl(V851S_SPI0_BASE + SPI_BURST_CNT_REG) == 0) {
		if (readl(V851S_SPI0_BASE + SPI_TC_REG) & SPI_TC_XCH) {
			printf("XCH Control Error!!\n");
			return -1;
		}
	} else {
		printf("SPI_MBC Error!\n");
		return -1;
	}

    DBG_INFO("RX FIFO CNT %d\r\n", spi_query_rxfifo(dev));

	/* check int status error */
	if (spi_qry_irq_pending(dev) & SPI_INT_STA_ERR) {
		printf("int status error");
		return -1;
	}

	/* rx */
	if (rx_len) {
		if (sunxi_spi_cpu_readl(dev, rx, rx_len))
            return -1;
	}

    /* check if having redundant TXFIO entry */
    redundant_txfifo = spi_query_txfifo(dev);

    if(redundant_txfifo) {
        DBG_INFO("redundant txfifo cnt %d\r\n", redundant_txfifo);
        spi_reset_fifo(dev);
    }

	spi_clr_irq_pending(dev, 0xffffffff);

	return 0;
}

static void spi_print_info(feldev_handle *dev)
{
	char buf[1024] = {0};
	snprintf(buf, sizeof(buf)-1,
			"sspi->base_addr = 0x%x, the SPI control register:\n"
			"[VER]   0x%02x = 0x%08x, [GCR]   0x%02x = 0x%08x, [TCR]   0x%02x = 0x%08x\n"
			"[IER]   0x%02x = 0x%08x, [ISR]   0x%02x = 0x%08x, [FCR]   0x%02x = 0x%08x\n"
			"[FSR]   0x%02x = 0x%08x, [WCR]   0x%02x = 0x%08x, [CCR]   0x%02x = 0x%08x\n"
			"[DCR]   0x%02x = 0x%08x, [BCR]   0x%02x = 0x%08x, [MTC]   0x%02x = 0x%08x\n"
			"[BCC]   0x%02x = 0x%08x, [BATCR] 0x%02x = 0x%08x, [DMA]   0x%02x = 0x%08x",
			V851S_SPI0_BASE,
			SPI_VER_REG, readl(V851S_SPI0_BASE + SPI_VER_REG),
			SPI_GC_REG, readl(V851S_SPI0_BASE + SPI_GC_REG),
			SPI_TC_REG, readl(V851S_SPI0_BASE + SPI_TC_REG),
			SPI_INT_CTL_REG, readl(V851S_SPI0_BASE + SPI_INT_CTL_REG),
			SPI_INT_STA_REG, readl(V851S_SPI0_BASE + SPI_INT_STA_REG),

			SPI_FIFO_CTL_REG, readl(V851S_SPI0_BASE + SPI_FIFO_CTL_REG),
			SPI_FIFO_STA_REG, readl(V851S_SPI0_BASE + SPI_FIFO_STA_REG),
			SPI_WAIT_CNT_REG, readl(V851S_SPI0_BASE + SPI_WAIT_CNT_REG),
			SPI_CLK_CTL_REG, readl(V851S_SPI0_BASE + SPI_CLK_CTL_REG),
			SPI_SDC_REG, readl(V851S_SPI0_BASE + SPI_SDC_REG),

			SPI_BURST_CNT_REG, readl(V851S_SPI0_BASE + SPI_BURST_CNT_REG),
			SPI_TRANSMIT_CNT_REG, readl(V851S_SPI0_BASE + SPI_TRANSMIT_CNT_REG),
			SPI_BCC_REG, readl(V851S_SPI0_BASE + SPI_BCC_REG),
			SPI_BATCR_REG, readl(V851S_SPI0_BASE + SPI_BATCR_REG),
			SPI_DMA_CTL_REG, readl(V851S_SPI0_BASE + SPI_DMA_CTL_REG));
			printf("%s\n", buf);
}

// =============================================================================================

static uint32_t gpio_base(feldev_handle *dev)
{
	soc_info_t *soc_info = dev->soc_info;
	switch (soc_info->soc_id) {
	case 0x1816: /* V536 */
	case 0x1817: /* V831 */
	case 0x1728: /* H6 */
	case 0x1823: /* H616 */
		return 0x0300B000;
	case 0x1886: /* V851s */
		return 0x02000000;
	default:
		return 0x01C20800;
	}
}

static uint32_t spi_base(feldev_handle *dev)
{
	soc_info_t *soc_info = dev->soc_info;
	switch (soc_info->soc_id) {
	case 0x1623: /* A10 */
	case 0x1625: /* A13 */
	case 0x1651: /* A20 */
	case 0x1663: /* F1C100s */
	case 0x1701: /* R40 */
		return 0x01C05000;
	case 0x1816: /* V536 */
	case 0x1817: /* V831 */
	case 0x1728: /* H6 */
	case 0x1823: /* H616 */
		return 0x05010000;
	case 0x1886: /* V851s */
		return 0x04025000;
	default:
		return 0x01C68000;
	}
}

static bool spi_is_sun8i(feldev_handle *dev)
{
	soc_info_t *soc_info = dev->soc_info;
	switch (soc_info->soc_id) {
	case 0x1886: /* V851s */
		return true;
	default:
		return false;
	}
}

/*
 * Configure pin function on a GPIO port
 */
static void gpio_set_cfgpin(feldev_handle *dev, int port_num, int pin_num,
			    int val)
{
    if(spi_is_sun8i(dev)){
        uint32_t port_base = gpio_base(dev) + port_num * 0x30;
        uint32_t cfg_reg   = port_base + 4 * (pin_num / 8);
        uint32_t pin_idx   = pin_num % 8;
        uint32_t x = readl(cfg_reg);
        x &= ~(0xf << (pin_idx * 4));
        x |= val << (pin_idx * 4);
        writel(x, cfg_reg);
    }else {
        uint32_t port_base = gpio_base(dev) + port_num * 0x24;
        uint32_t cfg_reg   = port_base + 4 * (pin_num / 8);
        uint32_t pin_idx   = pin_num % 8;
        uint32_t x = readl(cfg_reg);
        x &= ~(0x7 << (pin_idx * 4));
        x |= val << (pin_idx * 4);
        writel(x, cfg_reg);
    }
}

static bool spi_is_sun6i(feldev_handle *dev)
{
	soc_info_t *soc_info = dev->soc_info;
	switch (soc_info->soc_id) {
	case 0x1623: /* A10 */
	case 0x1625: /* A13 */
	case 0x1651: /* A20 */
		return false;
	default:
		return true;
	}
}

static bool soc_is_h6_style(feldev_handle *dev)
{
	soc_info_t *soc_info = dev->soc_info;
	switch (soc_info->soc_id) {
	case 0x1816: /* V536 */
	case 0x1817: /* V831 */
	case 0x1728: /* H6 */
	case 0x1823: /* H616 */
		return true;
	default:
		return false;
	}
}

/*
 * Init the SPI0 controller and setup pins muxing.
 */
static bool spi0_init(feldev_handle *dev)
{
	uint32_t reg_val;
	soc_info_t *soc_info = dev->soc_info;
	if (!soc_info) {
		printf("Unable to fetch device information. "
		       "Possibly unknown device.\n");
		return false;
	}

	/* Setup SPI0 pins muxing */
	switch (soc_info->soc_id) {
	case 0x1663: /* Allwinner F1C100s/F1C600/R6/F1C100A/F1C500 */
		gpio_set_cfgpin(dev, PC, 0, SUNIV_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 1, SUNIV_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 2, SUNIV_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 3, SUNIV_GPC_SPI0);
		break;
	case 0x1625: /* Allwinner A13 */
	case 0x1680: /* Allwinner H3 */
	case 0x1681: /* Allwinner V3s */
	case 0x1718: /* Allwinner H5 */
		gpio_set_cfgpin(dev, PC, 0, SUNXI_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 1, SUNXI_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 2, SUNXI_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 3, SUNXI_GPC_SPI0);
		break;
	case 0x1623: /* Allwinner A10 */
	case 0x1651: /* Allwinner A20 */
	case 0x1701: /* Allwinner R40 */
		gpio_set_cfgpin(dev, PC, 0, SUNXI_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 1, SUNXI_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 2, SUNXI_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 23, SUNXI_GPC_SPI0);
		break;
	case 0x1689: /* Allwinner A64 */
		gpio_set_cfgpin(dev, PC, 0, SUN50I_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 1, SUN50I_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 2, SUN50I_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 3, SUN50I_GPC_SPI0);
		break;
	case 0x1816: /* Allwinner V536 */
	case 0x1817: /* Allwinner V831 */
		gpio_set_cfgpin(dev, PC, 1, SUN50I_GPC_SPI0);	/* SPI0-CS */
		/* fall-through */
	case 0x1728: /* Allwinner H6 */
		gpio_set_cfgpin(dev, PC, 0, SUN50I_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 2, SUN50I_GPC_SPI0);
		gpio_set_cfgpin(dev, PC, 3, SUN50I_GPC_SPI0);
		/* PC5 is SPI0-CS on the H6, and SPI0-HOLD on the V831 */
		gpio_set_cfgpin(dev, PC, 5, SUN50I_GPC_SPI0);
		break;
	case 0x1823: /* Allwinner H616 */
		gpio_set_cfgpin(dev, PC, 0, SUN50I_GPC_SPI0);	/* SPI0_CLK */
		gpio_set_cfgpin(dev, PC, 2, SUN50I_GPC_SPI0);	/* SPI0_MOSI */
		gpio_set_cfgpin(dev, PC, 3, SUN50I_GPC_SPI0);	/* SPI0_CS0 */
		gpio_set_cfgpin(dev, PC, 4, SUN50I_GPC_SPI0);	/* SPI0_MISO */
		break;
	case 0x1886: /* Allwinner V851s */
		gpio_set_cfgpin(dev, PC, 0, SUN8I_GPC_SPI0);	/* SPI0_CLK      */
		gpio_set_cfgpin(dev, PC, 2, SUN8I_GPC_SPI0);	/* SPI0_MOSI     */
		gpio_set_cfgpin(dev, PC, 1, SUN8I_GPC_SPI0);	/* SPI0_CS0      */
		gpio_set_cfgpin(dev, PC, 3, SUN8I_GPC_SPI0);    /* SPI0_MISO/DO  */
        gpio_set_cfgpin(dev, PC, 4, SUN8I_GPC_SPI0);	/* SPI0_WP/IO2   */
        gpio_set_cfgpin(dev, PC, 5, SUN8I_GPC_SPI0);	/* SPI0_HOLD/IO3 */
		break;
	default: /* Unknown/Unsupported SoC */
		printf("SPI support not implemented yet for %x (%s)!\n",
		       soc_info->soc_id, soc_info->name);
		return false;
	}

    /* Init V851s SPI clock (chip = F35SQA001G) */
    if(spi_is_sun8i(dev)) {

        /* configure cpu clock */
        clock_set_corepll(dev, 900);
        /* fix reset circuit detection threshold */
	    rtc_set_vccio_det_spare(dev);
        DBG_INFO("CPU=%d MHz, PLL6=%d Mhz, AHB=%d Mhz, APB1=%dMhz, MBus=%dMhz\n",
		clock_get_corepll(dev),
		clock_get_pll6(dev), clock_get_ahb(dev),
		clock_get_apb1(dev),clock_get_mbus(dev));

        /* init spi clock */
        spi_init_clk(dev, 100000000); /* SPI module clock rate */

        uint32_t sclk_freq = 0;

        sclk_freq = sunxi_get_spic_clk(dev);
        if(!sclk_freq)
            exit(1);

        spi_soft_reset(dev);
        delay();

        /* 1. enable the spi module */
        spi_enable_bus(dev);
        /* 2. set the default chip select */
        spi_set_cs(dev, 0);

        /* 3. master: set spi module clock;
         * 4. set the default frequency	10MHz
         */
        spi_set_master(dev);
        /*
         * There is an issue related to read/write SPI spead
         * V851s CPU will adjust SPI spi sck pin depends on tx/rx size
         */
        spi_set_clk(dev, 40000000, sclk_freq, 0); /* SPI clock pin rate */
        /* 5. master : set POL,PHA,SSOPL,LMTF,DDB,DHB; default: SSCTL=0,SMC=1,TBW=0.
         * 6. set bit width-default: 8 bits
	     */
        //spi_config_batcr(dev);
	    spi_ss_level(dev, 1);
        spi_enable_tp(dev);
        /* 7. spi controller sends ss signal automatically */
        spi_ss_owner(dev, 0);
        /* 8. reset fifo */
        spi_reset_fifo(dev);

/* For debuging purpose only */
#if 0
        printf("soc_info->name         %s\r\n", soc_info->name);
        printf("soc_info->spl_addr     %X\r\n", soc_info->spl_addr);
        printf("soc_info->scratch_addr %X\r\n", soc_info->scratch_addr);
        printf("soc_info->sram_size    %d\r\n", soc_info->sram_size);

        /* SPI register info */
        spi_print_info(dev);

        /*
         *  [VER] 0x00 = 0x00010001,
         *  [GCR] 0x04 = 0x00000083, TP_EN=1, MODE=1, EN=1
         *  [TCR] 0x08 = 0x00000987, SDC=0, DHB=1, SS_LEVEL=1, SPOL=1, CPOL=0, CPHA=0
         *  [IER] 0x10 = 0x00000000,
         *  [ISR] 0x14 = 0x00000032,
         *  [FCR] 0x18 = 0x00200020,
         *  [FSR] 0x1c = 0x00000000,
         *  [WCR] 0x20 = 0x00000000,
         *  [CCR] 0x24 = 0x00000302,
         *  [DCR] 0x28 = 0x00002000,
         *  [BCR] 0x30 = 0x00000000,
         *  [MTC] 0x34 = 0x00000000,
         *  [BCC] 0x38 = 0x00000000,
         *  [DMA] 0x88 = 0x000000e5,
         */

        uint8_t	tx[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        uint8_t rx[32];
        int i;

        // Read status
        //tx[0] = 0x0F;
        //tx[1] = 0xC0;  // Protect 0xA0, Config 0xB0, Status 0xC0
        //memset(rx, 0x00, 32);
        //spi_xfer(dev, tx, 2, 0, rx, 1);
        //printf("Status register = %X\r\n", rx[0]);

        // Page read 0x13 (read to cache)
        tx[0] = 0x13;
        tx[1] = 0x00; // Dummy
        tx[2] = 0x00; // PA[15-8]
        tx[3] = 0x00; // PA[7-0]
        spi_xfer(dev, tx, 4, 0, NULL, 0);
        delay();

        // Read from cache 0x03
        tx[0] = 0x3;
        tx[1] = 0x00; // CA[15-8]
        tx[2] = 0x00; // CA[7-0]
        memset(rx, 0x00, 32);
        spi_xfer(dev, tx, 3, 1, rx, 16);
        for (i = 0; i < 16; i++){
            printf("rx[%d]= %X\r\n", i, rx[i]);
        }

        exit(1);
#endif

    } else {
        if (soc_is_h6_style(dev)) {
            reg_val = readl(H6_CCM_SPI_BGR);
            reg_val |= H6_CCM_SPI0_GATE_RESET;
            writel(reg_val, H6_CCM_SPI_BGR);
        } else {
            if (spi_is_sun6i(dev)) {
                /* Deassert SPI0 reset */
                reg_val = readl(SUN6I_BUS_SOFT_RST_REG0);
                reg_val |= SUN6I_SPI0_RST;
                writel(reg_val, SUN6I_BUS_SOFT_RST_REG0);
            }

            reg_val = readl(CCM_AHB_GATING0);
            reg_val |= CCM_AHB_GATE_SPI0;
            writel(reg_val, CCM_AHB_GATING0);
        }

        if (soc_info->soc_id == 0x1663) {	/* suniv F1C100s */
            /*
            * suniv doesn't have a module clock for SPI0 and the clock
            * source is always the AHB clock. Setup AHB to 200 MHz by
            * setting PLL6 to 600 MHz with a divider of 3, then program
            * the internal SPI dividier to 32.
            */

            /* Set PLL6 to 600MHz */
            writel(0x80041801, SUNIV_PLL6_CTL);
            /* PLL6:AHB:APB = 6:2:1 */
            writel(0x00003180, SUNIV_AHB_APB_CFG);
            /* divide by 32 */
            writel(CCM_SPI0_CLK_DIV_BY_32, SUN6I_SPI0_CCTL);
        } else {
            /* divide 24MHz OSC by 4 */
            writel(CCM_SPI0_CLK_DIV_BY_4,
                spi_is_sun6i(dev) ? SUN6I_SPI0_CCTL : SUN4I_SPI0_CCTL);
            /* Choose 24MHz from OSC24M and enable clock */
            writel(1U << 31,
                soc_is_h6_style(dev) ? H6_CCM_SPI0_CLK : CCM_SPI0_CLK);
        }

        if (spi_is_sun6i(dev)) {
            /* Enable SPI in the master mode and do a soft reset */
            reg_val = readl(SUN6I_SPI0_GCR);
            reg_val |= (1U << 31) | 3;
            writel(reg_val, SUN6I_SPI0_GCR);
            /* Wait for completion */
            while (readl(SUN6I_SPI0_GCR) & (1U << 31)) {}
        } else {
            reg_val = readl(SUN4I_SPI0_CTL);
            reg_val |= SUN4I_CTL_MASTER;
            reg_val |= SUN4I_CTL_ENABLE | SUN4I_CTL_TF_RST | SUN4I_CTL_RF_RST;
            writel(reg_val, SUN4I_SPI0_CTL);
        }
    }

	return true;
}

/*
 * Backup/restore the initial portion of the SRAM, which can be used as
 * a temporary data buffer.
 */
static void *backup_sram(feldev_handle *dev)
{
	soc_info_t *soc_info = dev->soc_info;
	size_t bufsize = soc_info->scratch_addr - soc_info->spl_addr;
	void *buf = malloc(bufsize);
	aw_fel_read(dev, soc_info->spl_addr, buf, bufsize);
	return buf;
}

static void restore_sram(feldev_handle *dev, void *buf)
{
	soc_info_t *soc_info = dev->soc_info;
	size_t bufsize = soc_info->scratch_addr - soc_info->spl_addr;
	aw_fel_write(dev, buf, soc_info->spl_addr, bufsize);
	free(buf);
}

#define SUN8I_SPI0_VER              (spi_base(dev) + 0x0000) // SPI Version Register
#define SUN8I_SPI0_GCR              (spi_base(dev) + 0x0004) // SPI Global Control Register
#define SUN8I_SPI0_TCR              (spi_base(dev) + 0x0008) // SPI Transfer Control Register
#define SUN8I_SPI0_IER              (spi_base(dev) + 0x0010) // SPI Interrupt Control Register
#define SUN8I_SPI0_ISR              (spi_base(dev) + 0x0014) // SPI Interrupt Status Register
#define SUN8I_SPI0_FCR              (spi_base(dev) + 0x0018) // SPI FIFO Control Register
#define SUN8I_SPI0_FSR              (spi_base(dev) + 0x001C) // SPI FIFO Status Register
#define SUN8I_SPI0_WCR              (spi_base(dev) + 0x0020) // SPI Wait Clock Register
#define SUN8I_SPI0_SAMP_DL          (spi_base(dev) + 0x0028) // SPI Sample Delay Control Register
#define SUN8I_SPI0_MBC              (spi_base(dev) + 0x0030) // SPI Master Burst Counter Register
#define SUN8I_SPI0_MTC              (spi_base(dev) + 0x0034) // SPI Master Transmit Counter Register
#define SUN8I_SPI0_BCC              (spi_base(dev) + 0x0038) // SPI Master Burst Control Register
#define SUN8I_SPI0_BATCR            (spi_base(dev) + 0x0040) // SPI Bit-Aligned Transfer Configure Register
#define SUN8I_SPI0_BA_CCR           (spi_base(dev) + 0x0044) // SPI Bit-Aligned Clock Configuration Register
#define SUN8I_SPI0_TBR              (spi_base(dev) + 0x0048) // SPI TX Bit Register
#define SUN8I_SPI0_RBR              (spi_base(dev) + 0x004C) // SPI RX Bit Register
#define SUN8I_SPI0_NDMA_MODE_CTL    (spi_base(dev) + 0x0088) // SPI Normal DMA Mode Control Register
#define SUN8I_SPI0_TXD              (spi_base(dev) + 0x0200) // SPI TX Data Register
#define SUN8I_SPI0_RXD              (spi_base(dev) + 0x0300) // SPI RX Data Register

static void prepare_spi_batch_data_transfer(feldev_handle *dev, uint32_t buf)
{
    if(spi_is_sun8i(dev)) {
		aw_fel_remotefunc_prepare_spi_batch_data_transfer(dev,
							    buf,
							    SUN8I_SPI0_TCR,
							    SUN8I_TCR_XCH,
                                SUN8I_SPI0_ISR,
							    SUN8I_SPI0_FSR,
							    SUN8I_SPI0_TXD,
							    SUN8I_SPI0_RXD,
							    SUN8I_SPI0_MBC,
							    SUN8I_SPI0_MTC,
							    SUN8I_SPI0_BCC);
    }

#if 0 /* disable */
    if (spi_is_sun6i(dev)) {
		aw_fel_remotefunc_prepare_spi_batch_data_transfer(dev,
							    buf,
							    SUN6I_SPI0_TCR,
							    SUN6I_TCR_XCH,
							    SUN6I_SPI0_FIFO_STA,
							    SUN6I_SPI0_TXD,
							    SUN6I_SPI0_RXD,
							    SUN6I_SPI0_MBC,
							    SUN6I_SPI0_MTC,
							    SUN6I_SPI0_BCC);
	} else {
		aw_fel_remotefunc_prepare_spi_batch_data_transfer(dev,
							    buf,
							    SUN4I_SPI0_CTL,
							    SUN4I_CTL_XCH,
							    SUN4I_SPI0_FIFO_STA,
							    SUN4I_SPI0_TX,
							    SUN4I_SPI0_RX,
							    SUN4I_SPI0_BC,
							    SUN4I_SPI0_TC,
							    0);
	}
#endif

}

#define F35SQA001G_PAGE_SIZE (2048)
//#define USE_PROGRAM_LOAD_QUAD 

#define SR1_ADDR (0xA0) /* Protection register */
#define SR2_ADDR (0xB0) /* Configuration register */
#define SR3_ADDR (0xC0) /* Status register */
#define SR4_ADDR (0x80) /* Sector 0 ECC */
#define SR5_ADDR (0x84) /* Sector 1 ECC */
#define SR6_ADDR (0x88) /* Sector 2 ECC */
#define SR6_ADDR (0x8C) /* Sector 3 ECC */

/*
 * Because previous implementation is very complicated so for V851S
 * we will implement in a different way, the working buffer(spl_addr)
 * layout is organized as below:
 *
 * | byte 0 | byte 1 | byte 2 | byte 3 |...........|...........|.........|
 *  \_______________/ \_______________/ \_________/ \_________/ \________/
 *          |                  |             |           |          |
 *        txlen              rxlen          cmd        txbuf      rxbuf
 *                                      <---------> <-------->  <-------->
 *                                           |          |           |
 *                                           |          |         rxlen
 *                                 txlen = cmdlen  +  txdlen
 *
 *  Where: total len = 4 + txlen + rxlen <= spl ram size (4096)
 *
 */

 typedef struct spi_buf{
    void *buf;
    uint8_t *cmd;
    uint8_t *txbuf;
    uint8_t *rxbuf;
    size_t len;
    size_t cmdlen;
    size_t txdlen;
    size_t rxlen;
}spi_buf;

/*
 * spi buffer generation
 */
static void aw_fel_spiflash_spibuf_create(spi_buf *spibuf,
    uint8_t *cmd, size_t cmdlen, size_t txdlen, size_t rxlen)
{
    if((NULL == cmd) || (0 == cmdlen)){
        return;
    }

    spibuf->len = 4 + txdlen + cmdlen + rxlen;
    spibuf->buf = malloc(spibuf->len);

    uint8_t *buf8 = (uint8_t *)spibuf->buf;

    if(NULL == spibuf->buf) {
        printf("Memmory allocation failed\r\n");
        return;
    }

    /* prepare tx/rx len */
    buf8[0] = (txdlen + cmdlen) & 0xff;
    buf8[1] = ((txdlen + cmdlen) >> 8) & 0xff;
    buf8[2] = rxlen & 0xff;
    buf8[3] = (rxlen >> 8) & 0xff;

    /* cmd */
    spibuf->cmd = &buf8[4];
    spibuf->cmdlen = cmdlen;
    memcpy((void *)spibuf->cmd, (void *)cmd, cmdlen);

    /* txdata */
    if(txdlen) {
        spibuf->txbuf = &spibuf->cmd[cmdlen];
        spibuf->txdlen = txdlen;
        memset((void *)spibuf->txbuf, 0x00, spibuf->txdlen);
    } else {
        spibuf->txdlen = 0;
        spibuf->txbuf = NULL;
    }

    /* reset rxbuf if any */
    if(rxlen) {
        if(txdlen) {
            spibuf->rxbuf = &spibuf->txbuf[txdlen];
            spibuf->rxlen = rxlen;
            memset((void *)spibuf->rxbuf, 0x00, rxlen);
        } else {
            spibuf->rxbuf = &spibuf->cmd[cmdlen];
            spibuf->rxlen = rxlen;
            memset((void *)spibuf->rxbuf, 0x00, rxlen);
        }
    } else {
        spibuf->rxbuf = NULL;
        spibuf->rxlen = 0;
    }
}

static void aw_fel_spiflash_spibuf_free(spi_buf *spibuf)
{
    if(NULL == spibuf){
        return;
    }

    spibuf->len = 0;
    spibuf->cmdlen = 0;
    spibuf->txdlen = 0;
    spibuf->rxlen = 0;

    spibuf->cmd= NULL;
    spibuf->txbuf = NULL;
    spibuf->rxbuf = NULL;

    if(NULL != spibuf->buf){
        free(spibuf->buf);
    }
}

/*
 * Read status command
 */
static uint8_t aw_fel_spiflash_read_status(feldev_handle *dev, uint8_t sta_addr)
{
    soc_info_t *soc_info = dev->soc_info;

    /* get feature command: 0x0F sta_addr S7-0 */
    uint8_t cmdbuf[] = { 2, 0, 1, 0, 0x0F, 0x00, 0x00};

    /* prepare command */
    cmdbuf[5] = sta_addr;

    /* execure spi */
    aw_fel_write(dev, cmdbuf, soc_info->spl_addr, sizeof(cmdbuf));
    aw_fel_remotefunc_execute(dev, NULL);
    aw_fel_read(dev, soc_info->spl_addr, cmdbuf, sizeof(cmdbuf));

    return cmdbuf[6];
}

/*
 * Write status command
 */
static void aw_fel_spiflash_write_status(feldev_handle *dev, uint8_t sta_addr, uint8_t value)
{
    soc_info_t *soc_info = dev->soc_info;

    /* set feature command: 0x1F sta_addr S7-0 */
    uint8_t cmdbuf[] = { 3, 0, 0, 0, 0x1F, 0x00, 0x00};

    /* prepare command */
    cmdbuf[5] = sta_addr;
    cmdbuf[6] = value;

    /* execure spi */
    aw_fel_write(dev, cmdbuf, soc_info->spl_addr, sizeof(cmdbuf));
    aw_fel_remotefunc_execute(dev, NULL);
}

/*
 * Wait for SPI flash operation
 */
static uint8_t aw_fel_spiflash_wait_for_busy(feldev_handle *dev)
{
    uint8_t status;
    uint32_t timeout = 0xFFFFFF;
    do {
        // delay();
        status = aw_fel_spiflash_read_status(dev, SR3_ADDR);
        if(status & 0x8){
            printf("Warning! P-FAIL occured\r\n");
        }
        if(status & 0x4){
            printf("Warning! E-FAIL occured\r\n");
        }
        if(!timeout){
            printf("Timeout! wait for busy\r\n");
        }
        timeout--;
    } while(status & 0x1);
}

/*
 * Read spi flash cache
 */
static void aw_fel_spiflash_read_to_cache(feldev_handle *dev, uint32_t page_addr)
{
    soc_info_t *soc_info = dev->soc_info;

    /* read cache command: 0x13 dummy PA15-8 PA7-0 */
    uint8_t cmdbuf[] = { 4, 0, 0, 0, 0x13, 0, 0x00, 0x00};

    /* prepare command */
    cmdbuf[4] = 0x13;
    cmdbuf[6] = (page_addr >> 8) & 0xff;
    cmdbuf[7] = page_addr & 0xff;

    /* execure spi */
    aw_fel_write(dev, cmdbuf, soc_info->spl_addr, sizeof(cmdbuf));
    aw_fel_remotefunc_execute(dev, NULL);
}

/*
 * Read data from the SPI flash. Use the first 4KiB of SRAM as the data buffer.
 */
void aw_fel_spiflash_read(feldev_handle *dev,
			  uint32_t offset, void *buf, size_t len,
			  progress_cb_t progress)
{
	soc_info_t *soc_info = dev->soc_info;
	void *backup = backup_sram(dev);
    uint8_t *buf8 = (uint8_t *)buf;
    size_t max_chunk_size = soc_info->scratch_addr - soc_info->spl_addr;
    uint32_t page_addr, pos, copy_size;

    /*
     * read data from cache(1): 0x03 CA15-8 CA7-0 Dummy D0 D1 D2...
     * read data from cache(4): 0x6b CA15-8 CA7-0 Dummy D0 D1 D2...
     */
    spi_buf spibuf;
    uint8_t cmd[] = {0x6b, 0x00, 0x00, 0};
    aw_fel_spiflash_spibuf_create(&spibuf, cmd, sizeof(cmd), 0, F35SQA001G_PAGE_SIZE);

    if(NULL == spibuf.buf){
        printf("Error memory\r\n");
        return;
    }

    /*
     *  pos indicates byte offset in a page.
     *
     *  page_addr n  page_addr n+1  page_addr n+2
     *
     *  [..........][..........][..........]
     *     |       |
     *     |-------|
     *     |   \
     *    pos   \____ page size - pos
     *
     *     |-----|        : In case of len < (page size - pos)
     *                      • copy data size = len
     *                      • pos = pos + copy data size
     *                      • len = len - copy data size
     *
     *     |------------| : In case of len >= (page size - pos)
     *                      • copy data size = (page size - pos)
     *                      • pos = 0
     *                      • len = len - copy data size
     */

	if (!spi0_init(dev))
		return;

    prepare_spi_batch_data_transfer(dev, soc_info->spl_addr);

    /* set QE bit */
    if(0x6b == cmd[0]) {
        uint8_t config = aw_fel_spiflash_read_status(dev, SR2_ADDR);
        config |= 0x1;
        aw_fel_spiflash_write_status(dev, SR2_ADDR, config);
    }

    /* For F35SQA001G, max chunk size = page size = 2K */
	if (max_chunk_size > F35SQA001G_PAGE_SIZE)
		max_chunk_size = F35SQA001G_PAGE_SIZE;

    /* Calculate page_addr and first_post */
    page_addr = offset / max_chunk_size;
    pos = offset % max_chunk_size;

    progress_start(progress, len);

    while (len > 0) {

        /* reach to cache */
        aw_fel_spiflash_read_to_cache(dev, page_addr);

        /* read data from cache */
        aw_fel_write(dev, spibuf.buf, soc_info->spl_addr, spibuf.len);
        aw_fel_remotefunc_execute(dev, NULL);
        aw_fel_read(dev, soc_info->spl_addr, spibuf.buf, spibuf.len);

        if(len < (max_chunk_size - pos)){
            copy_size = len;
            progress_update(copy_size);
            // printf("len < (max_chunk_size - pos)\r\n");
            // printf("page_addr = %X\r\n", page_addr);
            // printf("pos       = %d\r\n", pos);
            // printf("len       = %d\r\n", len);
            // printf("copy_size = %d\r\n", copy_size);
            memcpy((void*)buf8, (void*)&spibuf.rxbuf[pos], copy_size);
            buf8 += copy_size;
            pos  += copy_size;
            len  -= copy_size;
        }else {
            copy_size = max_chunk_size - pos;
            progress_update(copy_size);
            // printf("len >= (max_chunk_size - pos)\r\n");
            // printf("page_addr = %X\r\n", page_addr);
            // printf("pos       = %d\r\n", pos);
            // printf("len       = %d\r\n", len);
            //printf("copy_size = %d\r\n", copy_size);
            memcpy((void*)buf8, (void*)&spibuf.rxbuf[pos], copy_size);
            buf8 += copy_size;
            pos = 0;
            len -= copy_size;
        }
        page_addr += 1;
    }

    /* free memory */
    aw_fel_spiflash_spibuf_free(&spibuf);
	restore_sram(dev, backup);
}

/*
 * Write enable command
 */
static void aw_fel_spiflash_write_enable(feldev_handle *dev)
{
    soc_info_t *soc_info = dev->soc_info;

    /* write enable command: 0x06 */
    uint8_t cmdbuf[] = { 1, 0, 0, 0, 0x06};

    /* execure spi */
    aw_fel_write(dev, cmdbuf, soc_info->spl_addr, sizeof(cmdbuf));
    aw_fel_remotefunc_execute(dev, NULL);

    /* make sure WEL is set */
    uint8_t status;
    uint32_t timeout = 0xFFFFFF;
    do {
        status = aw_fel_spiflash_read_status(dev, SR3_ADDR);
        if(!timeout){
            printf("Timeout! WEL is not set\r\n");
        }
        timeout--;
    }while(!(status & 0x2));
}

/*
 * read data from cache (for debuging only)
 */
static void aw_fel_spiflash_read_from_cache(feldev_handle *dev, size_t len)
{
    soc_info_t *soc_info = dev->soc_info;
    spi_buf spibuf;

    /*           [4]     [5]    [6]    [7] ...
     * command: 0x03   CA15-8  CA7-0  Dummy  D0 D1 D2...
     */

    uint8_t cmd[] = {0x03, 0x00, 0x00, 0};
    aw_fel_spiflash_spibuf_create(&spibuf, cmd, sizeof(cmd), 0, len);

    /* read data from cache */
    aw_fel_write(dev, spibuf.buf, soc_info->spl_addr, spibuf.len);
    aw_fel_remotefunc_execute(dev, NULL);
    aw_fel_read(dev, soc_info->spl_addr, spibuf.buf, spibuf.len);

    /* print data from cache */
    printf("\r\nRead data from spi cache:");
    size_t i;
    for(int i=0; i < len; i++) {
        if(!(i % 16)) {
            if(i <= 0xF){
                printf("\r\n00%X:", i);
            }else if(i <= 0xFF) {
                printf("\r\n0%X:", i);
            }else{
                printf("\r\n%X:", i);
            }
        }
        if(spibuf.rxbuf[i] <= 0xF){
            printf(" 0%X", spibuf.rxbuf[i]);
        }else{
            printf(" %X", spibuf.rxbuf[i]);
        }
    }
    /* free memory */
    aw_fel_spiflash_spibuf_free(&spibuf);
}


#ifdef USE_PROGRAM_LOAD_QUAD

/*
 * Load program data quad
 */
static void aw_fel_spiflash_program_data_load_quad(feldev_handle *dev, uint8_t *buf, size_t len)
{

    soc_info_t *soc_info = dev->soc_info;
    spi_buf spibuf;

    if(len > F35SQA001G_PAGE_SIZE){
        printf("Warning! len exceeds memory page size %d\r\n", F35SQA001G_PAGE_SIZE);
        len = F35SQA001G_PAGE_SIZE;
    }

    /*
     * load program data cmd format: 0x32 CA15-8 CA7-0 D0 D1 D2...
     */
    uint8_t cmd[] = {0x32, 0x00, 0x00 };
    aw_fel_spiflash_spibuf_create(&spibuf, cmd, sizeof(cmd), len, 0);
    memcpy((void *)spibuf.txbuf, (void *)buf, len);

    /* Execute command */
    aw_fel_write(dev, spibuf.buf, soc_info->spl_addr, spibuf.len);
    aw_fel_remotefunc_execute(dev, NULL);

    /* print data in cache (debugging) */
    //aw_fel_spiflash_read_from_cache(dev, F35SQA001G_PAGE_SIZE);

    /* free memory */
    aw_fel_spiflash_spibuf_free(&spibuf);
}

#else /* USE_PROGRAM_LOAD_QUAD */

/*
 * Load program data
 */
static void aw_fel_spiflash_program_data_load(feldev_handle *dev, uint8_t *buf, size_t len)
{

    soc_info_t *soc_info = dev->soc_info;
    spi_buf spibuf;

    if(len > F35SQA001G_PAGE_SIZE){
        printf("Warning! len exceeds memory page size %d\r\n", F35SQA001G_PAGE_SIZE);
        len = F35SQA001G_PAGE_SIZE;
    }

    /*
     * load program data cmd format: 0x2 CA15-8 CA7-0 D0 D1 D2...
     */
    uint8_t cmd[] = {0x2, 0x00, 0x00 };
    aw_fel_spiflash_spibuf_create(&spibuf, cmd, sizeof(cmd), len, 0);
    memcpy((void *)spibuf.txbuf, (void *)buf, len);

    /* Execute command */
    aw_fel_write(dev, spibuf.buf, soc_info->spl_addr, spibuf.len);
    aw_fel_remotefunc_execute(dev, NULL);

    /* print data in cache (debugging) */
    //aw_fel_spiflash_read_from_cache(dev, F35SQA001G_PAGE_SIZE);

    /* free memory */
    aw_fel_spiflash_spibuf_free(&spibuf);
}

#endif /* USE_PROGRAM_LOAD_QUAD */

/*
 * Program execute
 */
static void aw_fel_spiflash_program_execute(feldev_handle *dev, uint32_t page_addr)
{
    soc_info_t *soc_info = dev->soc_info;

    /* write enable */
    aw_fel_spiflash_write_enable(dev);

    /* program execute cmd: 0x10 dummy PA15-8 PA7-0 */
    uint8_t cmdbuf[] = { 4, 0, 0, 0, 0x10, 0, 0x00, 0x00};

    /* prepare page addr parameter */
    cmdbuf[6] = (page_addr >> 8) & 0xff;
    cmdbuf[7] = page_addr & 0xff;

    /* Execute command */
    aw_fel_write(dev, cmdbuf, soc_info->spl_addr, sizeof(cmdbuf));
    aw_fel_remotefunc_execute(dev, NULL);

    /* wait for busy flag */
    aw_fel_spiflash_wait_for_busy(dev);
}

/*
 * Page program
 */
static void aw_fel_spiflash_page_program(feldev_handle *dev, uint32_t page_addr, uint8_t *buf, size_t len)
{
#ifdef USE_PROGRAM_LOAD_QUAD    
    aw_fel_spiflash_program_data_load_quad(dev, buf, len);
#else
    aw_fel_spiflash_program_data_load(dev, buf, len);    
#endif    
    aw_fel_spiflash_program_execute(dev, page_addr);
}

/*
 * Erase blocks of SPI flash memory
 */
static int aw_fel_spiflash_erase_block(feldev_handle *dev, uint32_t page_addr, size_t block_cnt, progress_cb_t progress)
{
    soc_info_t *soc_info = dev->soc_info;
    spi_flash_info_t *flash_info = &f35sqa001g_spi_flash_info;
    uint8_t status;

    /* read protect status register */
    status = aw_fel_spiflash_read_status(dev, SR1_ADDR);
    //printf("Protection status before = %X\r\n", status);

    status &= 0x87; /* clear BP3-0, unprotect all blocks */
    aw_fel_spiflash_write_status(dev, SR1_ADDR, status);
    status = aw_fel_spiflash_read_status(dev, SR1_ADDR);
    //printf("Protection status after = %X\r\n", status);

    printf("Erase block[s]:\r\n");

    /* Block erase command: 0xd8 dummy PA15-8 PA7-0 */
    uint8_t cmdbuf[] = { 4, 0, 0, 0, 0x00, 0, 0x00, 0x00};

    /* block erase cmd */
    cmdbuf[4] = flash_info->large_erase_cmd;
    cmdbuf[5] = 0x0; /* dummy */

    progress_start(progress, block_cnt);
    while(block_cnt){

        /* write enable */
        aw_fel_spiflash_write_enable(dev);

        /* prepare page addr parameter */
        cmdbuf[6] = (page_addr >> 8) & 0xff;
        cmdbuf[7] = page_addr & 0xff;

        /* Execute command */
        aw_fel_write(dev, cmdbuf, soc_info->spl_addr, sizeof(cmdbuf));
        aw_fel_remotefunc_execute(dev, NULL);

        /* wait for busy flag */
        aw_fel_spiflash_wait_for_busy(dev);

        /* update page addr and block count */
        progress_update(1);
        page_addr += 64;
        block_cnt--;
    }

    return 0;
}

/*
 * block read (maximum 128K bytes)
 */
static aw_fel_spiflash_block_read(feldev_handle *dev, uint32_t page_addr, uint8_t *buf, size_t len)
{
    soc_info_t *soc_info = dev->soc_info;
    spi_buf spibuf;

    if((NULL==buf) || (len==0)) {
        return;
    }

    if(len > (64*F35SQA001G_PAGE_SIZE)){
        printf("Warning! len should not greater than block size %d\r\n", 64*F35SQA001G_PAGE_SIZE);
        len = 64*F35SQA001G_PAGE_SIZE;
    }

    /*           [4]     [5]    [6]    [7] ...
     * command: 0x6b   CA15-8  CA7-0  Dummy  D0 D1 D2...
     */

    uint8_t cmd[] = {0x6b, 0x00, 0x00, 0};
    aw_fel_spiflash_spibuf_create(&spibuf, cmd, sizeof(cmd), 0, F35SQA001G_PAGE_SIZE);

    /* read block */
    for(uint32_t i=0; i<64; i++){
        /* reach to cache */
        aw_fel_spiflash_read_to_cache(dev, page_addr + i);

        /* read data from cache(quad) */
        aw_fel_write(dev, spibuf.buf, soc_info->spl_addr, spibuf.len);
        aw_fel_remotefunc_execute(dev, NULL);
        aw_fel_read(dev, soc_info->spl_addr, spibuf.buf, spibuf.len);

        /* copy buffer */
        if(len > F35SQA001G_PAGE_SIZE){
            memcpy((void*)buf, (void*)spibuf.rxbuf, F35SQA001G_PAGE_SIZE);
            buf += F35SQA001G_PAGE_SIZE;
            len -= F35SQA001G_PAGE_SIZE;
        } else if (len > 0) {
            memcpy((void*)buf, (void*)spibuf.rxbuf, len);
            buf += len;
            len -= len;
            break;
        }
    }

    /* free memory */
    aw_fel_spiflash_spibuf_free(&spibuf);
}

/*
 * Block programming
 */
static aw_fel_spiflash_block_program(feldev_handle *dev, uint32_t page_addr, uint8_t *buf, size_t len)
{
    if((NULL==buf) || (len==0)) {
        return;
    }

    if(len > (64*F35SQA001G_PAGE_SIZE)){
        printf("Warning! len should not greater than block size %d\r\n", 64*F35SQA001G_PAGE_SIZE);
        len = 64*F35SQA001G_PAGE_SIZE;
    }

    while(len) {
        if(len > F35SQA001G_PAGE_SIZE) {
            aw_fel_spiflash_page_program(dev, page_addr, buf, F35SQA001G_PAGE_SIZE);
            buf += F35SQA001G_PAGE_SIZE;
            len -= F35SQA001G_PAGE_SIZE;
        }else {
            aw_fel_spiflash_page_program(dev, page_addr, buf, len);
            buf += len;
            len -= len;
        }
        page_addr += 1;
    }
}

/*
 *  flash programming algorithm
 *     ______   ___
 *    |      |   |
 * b0 |      |   |  offset
 *    |______|   |        _______ backup 1 start
 *    |      |   |
 * b2 |      |  -|- block start = (offset / 128K), block_offset_1 = offset % 128K
 *    |______|   |
 * .  |      |   |
 * .  |      |   |  len
 *    |______|   |
 *    |      |  _|_ block end = (offset + len) / 128K, block_offset_2 = (offset + len) % 128K
 * bn |      |   |
 *    |______|  _|___________
 *                            backup 2 end
 *    backup 1:
 *       • start page_addr = block start(PA)
 *       • end   page_addr = offset / 2K
 *       • page offset     = offset % 2K
 *
 *
 */
void aw_fel_spiflash_write(feldev_handle *dev,
			   uint32_t offset, void *buf, size_t len,
			   progress_cb_t progress)
{
    soc_info_t *soc_info = dev->soc_info;
    void *backup = backup_sram(dev);

	if (!spi0_init(dev))
		return;

    prepare_spi_batch_data_transfer(dev, soc_info->spl_addr);

    uint32_t block_start, block_end, block_cnt, block_offset_1, block_offset_2, copy_len;
    uint8_t *block_start_buf = NULL, *block_end_buf = NULL;
    uint8_t *buf8 = (uint8_t *)buf;

    block_start = offset / (64 * F35SQA001G_PAGE_SIZE);
    block_end = (offset + len) / (64 * F35SQA001G_PAGE_SIZE);
    block_offset_1 = offset % (64 * F35SQA001G_PAGE_SIZE);
    block_offset_2 = (offset + len) % (64 * F35SQA001G_PAGE_SIZE);

    if(block_offset_2 == 0){
        block_cnt = block_end - block_start;
    }else {
        block_cnt = block_end - block_start + 1;
    }

    printf("len            = %d\r\n", len);
    printf("block start    = %d\r\n", block_start);
    printf("block end      = %d\r\n", block_end);
    printf("block_offset_1 = %d\r\n", block_offset_1);
    printf("block_offset_2 = %d\r\n", block_offset_2);
    printf("block cnt      = %d\r\n", block_cnt);

    /* allocate backup buffers */
    block_start_buf = malloc(64 * F35SQA001G_PAGE_SIZE);
    block_end_buf = malloc(64 * F35SQA001G_PAGE_SIZE);
    /* read backup 1 */
    aw_fel_spiflash_block_read(dev, block_start * 64, block_start_buf, 64 * F35SQA001G_PAGE_SIZE);
    /* read backup 2 */
    if(block_offset_2){
        aw_fel_spiflash_block_read(dev, block_end * 64, block_end_buf, 64 * F35SQA001G_PAGE_SIZE);
    }
    /* erase blocks */
    aw_fel_spiflash_erase_block(dev, block_start * 64, block_cnt, progress);

    /* programming process */
    progress_start(progress, len);

    /* update backup 1 buf and program */
    copy_len = (64 * F35SQA001G_PAGE_SIZE) - block_offset_1;
    memcpy((void *)&block_start_buf[block_offset_1], (void *)buf8, copy_len);
    buf8 += copy_len;
    len -= copy_len;

#ifdef USE_PROGRAM_LOAD_QUAD
    /* set QE bit */
    uint8_t config = aw_fel_spiflash_read_status(dev, SR2_ADDR);
    config |= 0x1;
    aw_fel_spiflash_write_status(dev, SR2_ADDR, config);    
#endif

    /* block program process */
    printf("Program block[s]:\r\n");

    /* program block start */
    aw_fel_spiflash_block_program(dev, block_start * 64, block_start_buf, 64 * F35SQA001G_PAGE_SIZE);
    progress_update(copy_len);

    /* program other blocks */
    for(uint32_t i = block_start + 1; i < block_end; i++) {
        aw_fel_spiflash_block_program(dev, i*64, buf8, 64 * F35SQA001G_PAGE_SIZE);
        buf8 += 64 * F35SQA001G_PAGE_SIZE;
        len -= 64 * F35SQA001G_PAGE_SIZE;
        progress_update(64 * F35SQA001G_PAGE_SIZE);
    }

    /* update backup 2 buf and program */
    if(block_offset_2) {
        copy_len = block_offset_2;
        memcpy((void *)block_end_buf, (void *)buf8, copy_len);
        buf8 += copy_len;
        len -= copy_len;

        /* program last block */
        aw_fel_spiflash_block_program(dev, block_end * 64, block_end_buf, 64 * F35SQA001G_PAGE_SIZE);
        progress_update(copy_len);
    }

    if(block_start_buf)
        free(block_start_buf);

    if(block_end_buf)
        free(block_end_buf);

    restore_sram(dev, backup);
}

/*
 * Erase spi flash
 */
void aw_fel_spiflash_erase_blocks(feldev_handle *dev,
			   uint32_t page_addr, size_t block_cnt,
			   progress_cb_t progress)
{
    soc_info_t *soc_info = dev->soc_info;
    void *backup = backup_sram(dev);

	if (!spi0_init(dev))
		return;

    prepare_spi_batch_data_transfer(dev, soc_info->spl_addr);

    /* erase blocks */
    aw_fel_spiflash_erase_block(dev, page_addr, block_cnt, progress);

    restore_sram(dev, backup);
}

/*
 * Use the read JEDEC ID (9Fh) command.
 */
void aw_fel_spiflash_info(feldev_handle *dev)
{
	soc_info_t *soc_info = dev->soc_info;
	const char *manufacturer;
    /* F35SQA001G JEDEC CMD 0x9F Dummy MID DID DID */
	unsigned char buf[] = { 2, 0, 3, 0, 0x9F, 0, 0x00, 0x00, 0x00 };
	void *backup = backup_sram(dev);

	if (!spi0_init(dev))
		return;

	aw_fel_write(dev, buf, soc_info->spl_addr, sizeof(buf));
	prepare_spi_batch_data_transfer(dev, soc_info->spl_addr);
	aw_fel_remotefunc_execute(dev, NULL);
	aw_fel_read(dev, soc_info->spl_addr, buf, sizeof(buf));

	restore_sram(dev, backup);

	/* Assume that the MISO pin is either pulled up or down */
	if (buf[6] == 0x00 || buf[6] == 0xFF) {
		printf("No SPI flash detected.\n");
		return;
	}

	switch (buf[6]) {
	case 0xEF:
		manufacturer = "Winbond";
		break;
	case 0xC2:
		manufacturer = "Macronix";
		break;
	case 0x1C:
		manufacturer = "Eon";
		break;
	case 0xCD:
		manufacturer = "Foresee";
		break;
	default:
		manufacturer = "Unknown";
		break;
	}

	printf("Manufacturer: %s (%02Xh), model: %02Xh, size: %d bytes.\n",
	       manufacturer, buf[6], buf[7], (buf[3] << 8) | buf[2]);
}

/*
 * Show a help message about the available "spiflash-*" commands.
 */
void aw_fel_spiflash_help(void)
{
	printf("	spiflash-info			Retrieves basic information\n"
	       "	spiflash-read addr length file	Write SPI flash contents into file\n"
	       "	spiflash-write addr file	    Store file contents into SPI flash\n"
           "	spiflash-erase-blocks page_addr block_cnt Erase SPI flash blocks\n");
}
