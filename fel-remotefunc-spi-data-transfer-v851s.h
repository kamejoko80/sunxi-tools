/* Automatically generated, do not edit! */

static void
aw_fel_remotefunc_prepare_spi_batch_data_transfer(feldev_handle *dev,
                                                  uint32_t              buf,
                                                  uint32_t              spi_ctl_reg,
                                                  uint32_t              spi_ctl_xch_bitmask,
                                                  uint32_t              spi_sta_reg,
                                                  uint32_t              spi_fifo_reg,
                                                  uint32_t              spi_tx_reg,
                                                  uint32_t              spi_rx_reg,
                                                  uint32_t              spi_bc_reg,
                                                  uint32_t              spi_tc_reg,
                                                  uint32_t              spi_bcc_reg)
{
	static uint8_t arm_code[] = {
		0xf0, 0x47, 0x2d, 0xe9, /*    0:    push     {r4, r5, r6, r7, r8, r9, sl, lr}   */
		0x01, 0xe0, 0xd0, 0xe5, /*    4:    ldrb     lr, [r0, #1]                       */
		0x00, 0xc0, 0xd0, 0xe5, /*    8:    ldrb     ip, [r0]                           */
		0x03, 0x40, 0xd0, 0xe5, /*    c:    ldrb     r4, [r0, #3]                       */
		0x0e, 0xc4, 0x8c, 0xe1, /*   10:    orr      ip, ip, lr, lsl #8                 */
		0x02, 0xe0, 0xd0, 0xe5, /*   14:    ldrb     lr, [r0, #2]                       */
		0x04, 0x80, 0x80, 0xe2, /*   18:    add      r8, r0, #4                         */
		0x04, 0xe4, 0x8e, 0xe1, /*   1c:    orr      lr, lr, r4, lsl #8                 */
		0x04, 0x40, 0x8c, 0xe2, /*   20:    add      r4, ip, #4                         */
		0x04, 0x00, 0x80, 0xe0, /*   24:    add      r0, r0, r4                         */
		0x00, 0x40, 0xe0, 0xe3, /*   28:    mvn      r4, #0                             */
		0x00, 0x40, 0x83, 0xe5, /*   2c:    str      r4, [r3]                           */
		0x2c, 0x40, 0x9d, 0xe5, /*   30:    ldr      r4, [sp, #44]                      */
		0x34, 0x50, 0x9d, 0xe5, /*   34:    ldr      r5, [sp, #52]                      */
		0x0e, 0xa0, 0x8c, 0xe0, /*   38:    add      sl, ip, lr                         */
		0x00, 0xa0, 0x84, 0xe5, /*   3c:    str      sl, [r4]                           */
		0x30, 0x40, 0x9d, 0xe5, /*   40:    ldr      r4, [sp, #48]                      */
		0x00, 0x00, 0x55, 0xe3, /*   44:    cmp      r5, #0                             */
		0x00, 0xc0, 0x84, 0xe5, /*   48:    str      ip, [r4]                           */
		0x00, 0x40, 0x95, 0x15, /*   4c:    ldrne    r4, [r5]                           */
		0x20, 0x60, 0x9d, 0xe5, /*   50:    ldr      r6, [sp, #32]                      */
		0x0f, 0x42, 0x04, 0x12, /*   54:    andne    r4, r4, #-268435456                */
		0x0c, 0x40, 0x84, 0x11, /*   58:    orrne    r4, r4, ip                         */
		0x24, 0x90, 0x9d, 0xe5, /*   5c:    ldr      r9, [sp, #36]                      */
		0x28, 0x70, 0x9d, 0xe5, /*   60:    ldr      r7, [sp, #40]                      */
		0x00, 0x40, 0x85, 0x15, /*   64:    strne    r4, [r5]                           */
		0x00, 0x40, 0x0f, 0xe1, /*   68:    mrs      r4, CPSR                           */
		0xc0, 0x50, 0x84, 0xe3, /*   6c:    orr      r5, r4, #192                       */
		0x05, 0xf0, 0x21, 0xe1, /*   70:    msr      CPSR_c, r5                         */
		0x00, 0x50, 0x91, 0xe5, /*   74:    ldr      r5, [r1]                           */
		0x02, 0x20, 0x85, 0xe1, /*   78:    orr      r2, r5, r2                         */
		0x00, 0x20, 0x81, 0xe5, /*   7c:    str      r2, [r1]                           */
		0x00, 0x00, 0x5c, 0xe3, /*   80:    cmp      ip, #0                             */
		0x13, 0x00, 0x00, 0x1a, /*   84:    bne      d8 <spi_batch_data_transfer+0xd8>  */
		0x0e, 0xe0, 0x80, 0xe0, /*   88:    add      lr, r0, lr                         */
		0x00, 0x00, 0x5e, 0xe1, /*   8c:    cmp      lr, r0                             */
		0x1c, 0x00, 0x00, 0x1a, /*   90:    bne      108 <spi_batch_data_transfer+0x108> */
		0x00, 0x20, 0x93, 0xe5, /*   94:    ldr      r2, [r3]                           */
		0x07, 0x0c, 0x12, 0xe3, /*   98:    tst      r2, #1792                          */
		0x09, 0x00, 0x00, 0x0a, /*   9c:    beq      c8 <spi_batch_data_transfer+0xc8>  */
		0x02, 0x24, 0xa0, 0xe3, /*   a0:    mov      r2, #33554432                      */
		0xf0, 0x10, 0x92, 0xe5, /*   a4:    ldr      r1, [r2, #240]                     */
		0x0f, 0x14, 0xc1, 0xe3, /*   a8:    bic      r1, r1, #251658240                 */
		0xf0, 0x10, 0x82, 0xe5, /*   ac:    str      r1, [r2, #240]                     */
		0xf0, 0x10, 0x92, 0xe5, /*   b0:    ldr      r1, [r2, #240]                     */
		0x01, 0x14, 0x81, 0xe3, /*   b4:    orr      r1, r1, #16777216                  */
		0xf0, 0x10, 0x82, 0xe5, /*   b8:    str      r1, [r2, #240]                     */
		0x00, 0x11, 0x92, 0xe5, /*   bc:    ldr      r1, [r2, #256]                     */
		0x40, 0x10, 0x81, 0xe3, /*   c0:    orr      r1, r1, #64                        */
		0x00, 0x11, 0x82, 0xe5, /*   c4:    str      r1, [r2, #256]                     */
		0x00, 0x20, 0xe0, 0xe3, /*   c8:    mvn      r2, #0                             */
		0x00, 0x20, 0x83, 0xe5, /*   cc:    str      r2, [r3]                           */
		0x04, 0xf0, 0x21, 0xe1, /*   d0:    msr      CPSR_c, r4                         */
		0xf0, 0x87, 0xbd, 0xe8, /*   d4:    pop      {r4, r5, r6, r7, r8, r9, sl, pc}   */
		0x00, 0x20, 0x93, 0xe5, /*   d8:    ldr      r2, [r3]                           */
		0x10, 0x00, 0x12, 0xe3, /*   dc:    tst      r2, #16                            */
		0xfc, 0xff, 0xff, 0x0a, /*   e0:    beq      d8 <spi_batch_data_transfer+0xd8>  */
		0x01, 0x20, 0xd8, 0xe4, /*   e4:    ldrb     r2, [r8], #1                       */
		0x00, 0x20, 0xc9, 0xe5, /*   e8:    strb     r2, [r9]                           */
		0x00, 0x20, 0x96, 0xe5, /*   ec:    ldr      r2, [r6]                           */
		0x01, 0xc0, 0x4c, 0xe2, /*   f0:    sub      ip, ip, #1                         */
		0x0f, 0x00, 0x12, 0xe3, /*   f4:    tst      r2, #15                            */
		0x00, 0x20, 0xd7, 0x15, /*   f8:    ldrbne   r2, [r7]                           */
		0x01, 0xe0, 0x4e, 0x12, /*   fc:    subne    lr, lr, #1                         */
		0x01, 0x20, 0xc0, 0x14, /*  100:    strbne   r2, [r0], #1                       */
		0xdd, 0xff, 0xff, 0xea, /*  104:    b        80 <spi_batch_data_transfer+0x80>  */
		0x00, 0x20, 0x96, 0xe5, /*  108:    ldr      r2, [r6]                           */
		0x0f, 0x00, 0x12, 0xe3, /*  10c:    tst      r2, #15                            */
		0x00, 0x20, 0xd7, 0x15, /*  110:    ldrbne   r2, [r7]                           */
		0x01, 0x20, 0xc0, 0x14, /*  114:    strbne   r2, [r0], #1                       */
		0xdb, 0xff, 0xff, 0xea, /*  118:    b        8c <spi_batch_data_transfer+0x8c>  */
	};
	uint32_t args[] = {
		buf,
		spi_ctl_reg,
		spi_ctl_xch_bitmask,
		spi_sta_reg,
		spi_fifo_reg,
		spi_tx_reg,
		spi_rx_reg,
		spi_bc_reg,
		spi_tc_reg,
		spi_bcc_reg
	};
	aw_fel_remotefunc_prepare(dev, 32, arm_code, sizeof(arm_code), 10, args);
}
