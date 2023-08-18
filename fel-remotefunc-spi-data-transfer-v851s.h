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
		0x01, 0xc0, 0xd0, 0xe5, /*    4:    ldrb     ip, [r0, #1]                       */
		0x00, 0xe0, 0xd0, 0xe5, /*    8:    ldrb     lr, [r0]                           */
		0x03, 0x40, 0xd0, 0xe5, /*    c:    ldrb     r4, [r0, #3]                       */
		0x0c, 0xe4, 0x8e, 0xe1, /*   10:    orr      lr, lr, ip, lsl #8                 */
		0x02, 0xc0, 0xd0, 0xe5, /*   14:    ldrb     ip, [r0, #2]                       */
		0x02, 0xa4, 0xa0, 0xe3, /*   18:    mov      sl, #33554432                      */
		0x04, 0xc4, 0x8c, 0xe1, /*   1c:    orr      ip, ip, r4, lsl #8                 */
		0x04, 0x40, 0x8e, 0xe2, /*   20:    add      r4, lr, #4                         */
		0x04, 0x80, 0x80, 0xe2, /*   24:    add      r8, r0, #4                         */
		0x04, 0x00, 0x80, 0xe0, /*   28:    add      r0, r0, r4                         */
		0x00, 0x40, 0xe0, 0xe3, /*   2c:    mvn      r4, #0                             */
		0x00, 0x40, 0x83, 0xe5, /*   30:    str      r4, [r3]                           */
		0x00, 0x41, 0x9a, 0xe5, /*   34:    ldr      r4, [sl, #256]                     */
		0x34, 0x50, 0x9d, 0xe5, /*   38:    ldr      r5, [sp, #52]                      */
		0x40, 0x40, 0xc4, 0xe3, /*   3c:    bic      r4, r4, #64                        */
		0x20, 0x60, 0x9d, 0xe5, /*   40:    ldr      r6, [sp, #32]                      */
		0x24, 0x90, 0x9d, 0xe5, /*   44:    ldr      r9, [sp, #36]                      */
		0x28, 0x70, 0x9d, 0xe5, /*   48:    ldr      r7, [sp, #40]                      */
		0x00, 0x41, 0x8a, 0xe5, /*   4c:    str      r4, [sl, #256]                     */
		0x2c, 0x40, 0x9d, 0xe5, /*   50:    ldr      r4, [sp, #44]                      */
		0x0c, 0xa0, 0x8e, 0xe0, /*   54:    add      sl, lr, ip                         */
		0x00, 0xa0, 0x84, 0xe5, /*   58:    str      sl, [r4]                           */
		0x30, 0x40, 0x9d, 0xe5, /*   5c:    ldr      r4, [sp, #48]                      */
		0x00, 0x00, 0x55, 0xe3, /*   60:    cmp      r5, #0                             */
		0x00, 0xe0, 0x84, 0xe5, /*   64:    str      lr, [r4]                           */
		0x00, 0x40, 0x95, 0x15, /*   68:    ldrne    r4, [r5]                           */
		0x0f, 0x42, 0x04, 0x12, /*   6c:    andne    r4, r4, #-268435456                */
		0x0e, 0x40, 0x84, 0x11, /*   70:    orrne    r4, r4, lr                         */
		0x00, 0x40, 0x85, 0x15, /*   74:    strne    r4, [r5]                           */
		0x00, 0x40, 0x0f, 0xe1, /*   78:    mrs      r4, CPSR                           */
		0xc0, 0x50, 0x84, 0xe3, /*   7c:    orr      r5, r4, #192                       */
		0x05, 0xf0, 0x21, 0xe1, /*   80:    msr      CPSR_c, r5                         */
		0x00, 0x50, 0x91, 0xe5, /*   84:    ldr      r5, [r1]                           */
		0x02, 0x20, 0x85, 0xe1, /*   88:    orr      r2, r5, r2                         */
		0x00, 0x20, 0x81, 0xe5, /*   8c:    str      r2, [r1]                           */
		0x00, 0x00, 0x5e, 0xe3, /*   90:    cmp      lr, #0                             */
		0x11, 0x00, 0x00, 0x1a, /*   94:    bne      e0 <spi_batch_data_transfer+0xe0>  */
		0x0c, 0xc0, 0x80, 0xe0, /*   98:    add      ip, r0, ip                         */
		0x00, 0x00, 0x5c, 0xe1, /*   9c:    cmp      ip, r0                             */
		0x1c, 0x00, 0x00, 0x1a, /*   a0:    bne      118 <spi_batch_data_transfer+0x118> */
		0x00, 0x30, 0x93, 0xe5, /*   a4:    ldr      r3, [r3]                           */
		0x07, 0x0c, 0x13, 0xe3, /*   a8:    tst      r3, #1792                          */
		0x09, 0x00, 0x00, 0x0a, /*   ac:    beq      d8 <spi_batch_data_transfer+0xd8>  */
		0x02, 0x34, 0xa0, 0xe3, /*   b0:    mov      r3, #33554432                      */
		0xf0, 0x20, 0x93, 0xe5, /*   b4:    ldr      r2, [r3, #240]                     */
		0x0f, 0x24, 0xc2, 0xe3, /*   b8:    bic      r2, r2, #251658240                 */
		0xf0, 0x20, 0x83, 0xe5, /*   bc:    str      r2, [r3, #240]                     */
		0xf0, 0x20, 0x93, 0xe5, /*   c0:    ldr      r2, [r3, #240]                     */
		0x01, 0x24, 0x82, 0xe3, /*   c4:    orr      r2, r2, #16777216                  */
		0xf0, 0x20, 0x83, 0xe5, /*   c8:    str      r2, [r3, #240]                     */
		0x00, 0x21, 0x93, 0xe5, /*   cc:    ldr      r2, [r3, #256]                     */
		0x40, 0x20, 0x82, 0xe3, /*   d0:    orr      r2, r2, #64                        */
		0x00, 0x21, 0x83, 0xe5, /*   d4:    str      r2, [r3, #256]                     */
		0x04, 0xf0, 0x21, 0xe1, /*   d8:    msr      CPSR_c, r4                         */
		0xf0, 0x87, 0xbd, 0xe8, /*   dc:    pop      {r4, r5, r6, r7, r8, r9, sl, pc}   */
		0x00, 0x20, 0x93, 0xe5, /*   e0:    ldr      r2, [r3]                           */
		0x10, 0x00, 0x12, 0xe3, /*   e4:    tst      r2, #16                            */
		0xfc, 0xff, 0xff, 0x0a, /*   e8:    beq      e0 <spi_batch_data_transfer+0xe0>  */
		0x01, 0x20, 0xd8, 0xe4, /*   ec:    ldrb     r2, [r8], #1                       */
		0x00, 0x00, 0x5c, 0xe3, /*   f0:    cmp      ip, #0                             */
		0x01, 0xe0, 0x4e, 0xe2, /*   f4:    sub      lr, lr, #1                         */
		0x00, 0x20, 0xc9, 0xe5, /*   f8:    strb     r2, [r9]                           */
		0xe3, 0xff, 0xff, 0x0a, /*   fc:    beq      90 <spi_batch_data_transfer+0x90>  */
		0x00, 0x20, 0x96, 0xe5, /*  100:    ldr      r2, [r6]                           */
		0x0f, 0x00, 0x12, 0xe3, /*  104:    tst      r2, #15                            */
		0x00, 0x20, 0xd7, 0x15, /*  108:    ldrbne   r2, [r7]                           */
		0x01, 0xc0, 0x4c, 0x12, /*  10c:    subne    ip, ip, #1                         */
		0x01, 0x20, 0xc0, 0x14, /*  110:    strbne   r2, [r0], #1                       */
		0xdd, 0xff, 0xff, 0xea, /*  114:    b        90 <spi_batch_data_transfer+0x90>  */
		0x00, 0x20, 0x96, 0xe5, /*  118:    ldr      r2, [r6]                           */
		0x0f, 0x00, 0x12, 0xe3, /*  11c:    tst      r2, #15                            */
		0x00, 0x20, 0xd7, 0x15, /*  120:    ldrbne   r2, [r7]                           */
		0x01, 0x20, 0xc0, 0x14, /*  124:    strbne   r2, [r0], #1                       */
		0xdb, 0xff, 0xff, 0xea, /*  128:    b        9c <spi_batch_data_transfer+0x9c>  */
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
