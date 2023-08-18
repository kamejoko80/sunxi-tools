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
		0xf0, 0x4f, 0x2d, 0xe9, /*    0:    push     {r4, r5, r6, r7, r8, r9, sl, fp, lr} */
		0x01, 0xc0, 0xd0, 0xe5, /*    4:    ldrb     ip, [r0, #1]                       */
		0x00, 0x40, 0xd0, 0xe5, /*    8:    ldrb     r4, [r0]                           */
		0x02, 0xe0, 0xd0, 0xe5, /*    c:    ldrb     lr, [r0, #2]                       */
		0x0c, 0x44, 0x84, 0xe1, /*   10:    orr      r4, r4, ip, lsl #8                 */
		0x03, 0xc0, 0xd0, 0xe5, /*   14:    ldrb     ip, [r0, #3]                       */
		0x00, 0x50, 0xe0, 0xe3, /*   18:    mvn      r5, #0                             */
		0x00, 0x50, 0x83, 0xe5, /*   1c:    str      r5, [r3]                           */
		0x0c, 0xe4, 0x8e, 0xe1, /*   20:    orr      lr, lr, ip, lsl #8                 */
		0x30, 0x50, 0x9d, 0xe5, /*   24:    ldr      r5, [sp, #48]                      */
		0x38, 0x70, 0x9d, 0xe5, /*   28:    ldr      r7, [sp, #56]                      */
		0x0e, 0xb0, 0x84, 0xe0, /*   2c:    add      fp, r4, lr                         */
		0x00, 0xb0, 0x85, 0xe5, /*   30:    str      fp, [r5]                           */
		0x34, 0x50, 0x9d, 0xe5, /*   34:    ldr      r5, [sp, #52]                      */
		0x00, 0x00, 0x57, 0xe3, /*   38:    cmp      r7, #0                             */
		0x00, 0x40, 0x85, 0xe5, /*   3c:    str      r4, [r5]                           */
		0x00, 0x50, 0x97, 0x15, /*   40:    ldrne    r5, [r7]                           */
		0x04, 0xc0, 0x84, 0xe2, /*   44:    add      ip, r4, #4                         */
		0x0f, 0x52, 0x05, 0x12, /*   48:    andne    r5, r5, #-268435456                */
		0x04, 0x50, 0x85, 0x11, /*   4c:    orrne    r5, r5, r4                         */
		0x24, 0x80, 0x9d, 0xe5, /*   50:    ldr      r8, [sp, #36]                      */
		0x28, 0xa0, 0x9d, 0xe5, /*   54:    ldr      sl, [sp, #40]                      */
		0x2c, 0x90, 0x9d, 0xe5, /*   58:    ldr      r9, [sp, #44]                      */
		0x04, 0x60, 0x80, 0xe2, /*   5c:    add      r6, r0, #4                         */
		0x0c, 0xc0, 0x80, 0xe0, /*   60:    add      ip, r0, ip                         */
		0x00, 0x50, 0x87, 0x15, /*   64:    strne    r5, [r7]                           */
		0x00, 0x50, 0x0f, 0xe1, /*   68:    mrs      r5, CPSR                           */
		0xc0, 0x70, 0x85, 0xe3, /*   6c:    orr      r7, r5, #192                       */
		0x07, 0xf0, 0x21, 0xe1, /*   70:    msr      CPSR_c, r7                         */
		0x00, 0x70, 0x91, 0xe5, /*   74:    ldr      r7, [r1]                           */
		0x01, 0x04, 0x80, 0xe2, /*   78:    add      r0, r0, #16777216                  */
		0x02, 0x20, 0x87, 0xe1, /*   7c:    orr      r2, r7, r2                         */
		0x04, 0x00, 0x80, 0xe2, /*   80:    add      r0, r0, #4                         */
		0x00, 0x20, 0x81, 0xe5, /*   84:    str      r2, [r1]                           */
		0x00, 0x00, 0x54, 0xe3, /*   88:    cmp      r4, #0                             */
		0x11, 0x00, 0x00, 0x1a, /*   8c:    bne      d8 <spi_batch_data_transfer+0xd8>  */
		0x01, 0x24, 0xa0, 0xe3, /*   90:    mov      r2, #16777216                      */
		0x00, 0x00, 0x5e, 0xe3, /*   94:    cmp      lr, #0                             */
		0x28, 0x00, 0x00, 0x1a, /*   98:    bne      140 <spi_batch_data_transfer+0x140> */
		0x00, 0x30, 0x93, 0xe5, /*   9c:    ldr      r3, [r3]                           */
		0x07, 0x0c, 0x13, 0xe3, /*   a0:    tst      r3, #1792                          */
		0x09, 0x00, 0x00, 0x0a, /*   a4:    beq      d0 <spi_batch_data_transfer+0xd0>  */
		0x02, 0x34, 0xa0, 0xe3, /*   a8:    mov      r3, #33554432                      */
		0xf0, 0x20, 0x93, 0xe5, /*   ac:    ldr      r2, [r3, #240]                     */
		0x0f, 0x24, 0xc2, 0xe3, /*   b0:    bic      r2, r2, #251658240                 */
		0xf0, 0x20, 0x83, 0xe5, /*   b4:    str      r2, [r3, #240]                     */
		0xf0, 0x20, 0x93, 0xe5, /*   b8:    ldr      r2, [r3, #240]                     */
		0x01, 0x24, 0x82, 0xe3, /*   bc:    orr      r2, r2, #16777216                  */
		0xf0, 0x20, 0x83, 0xe5, /*   c0:    str      r2, [r3, #240]                     */
		0x00, 0x21, 0x93, 0xe5, /*   c4:    ldr      r2, [r3, #256]                     */
		0x40, 0x20, 0x82, 0xe3, /*   c8:    orr      r2, r2, #64                        */
		0x00, 0x21, 0x83, 0xe5, /*   cc:    str      r2, [r3, #256]                     */
		0x05, 0xf0, 0x21, 0xe1, /*   d0:    msr      CPSR_c, r5                         */
		0xf0, 0x8f, 0xbd, 0xe8, /*   d4:    pop      {r4, r5, r6, r7, r8, r9, sl, fp, pc} */
		0x00, 0x20, 0x93, 0xe5, /*   d8:    ldr      r2, [r3]                           */
		0x10, 0x00, 0x12, 0xe3, /*   dc:    tst      r2, #16                            */
		0xfc, 0xff, 0xff, 0x0a, /*   e0:    beq      d8 <spi_batch_data_transfer+0xd8>  */
		0x01, 0x20, 0xd6, 0xe4, /*   e4:    ldrb     r2, [r6], #1                       */
		0x00, 0x00, 0x5e, 0xe3, /*   e8:    cmp      lr, #0                             */
		0x01, 0x40, 0x44, 0xe2, /*   ec:    sub      r4, r4, #1                         */
		0x00, 0x20, 0xca, 0xe5, /*   f0:    strb     r2, [sl]                           */
		0x04, 0x00, 0x00, 0x0a, /*   f4:    beq      10c <spi_batch_data_transfer+0x10c> */
		0x00, 0x20, 0x98, 0xe5, /*   f8:    ldr      r2, [r8]                           */
		0x0f, 0x00, 0x12, 0xe3, /*   fc:    tst      r2, #15                            */
		0x00, 0x20, 0xd9, 0x15, /*  100:    ldrbne   r2, [r9]                           */
		0x01, 0xe0, 0x4e, 0x12, /*  104:    subne    lr, lr, #1                         */
		0x01, 0x20, 0xcc, 0x14, /*  108:    strbne   r2, [ip], #1                       */
		0x06, 0x00, 0x50, 0xe1, /*  10c:    cmp      r0, r6                             */
		0xdc, 0xff, 0xff, 0x1a, /*  110:    bne      88 <spi_batch_data_transfer+0x88>  */
		0x02, 0x34, 0xa0, 0xe3, /*  114:    mov      r3, #33554432                      */
		0xf0, 0x20, 0x93, 0xe5, /*  118:    ldr      r2, [r3, #240]                     */
		0x0f, 0x24, 0xc2, 0xe3, /*  11c:    bic      r2, r2, #251658240                 */
		0xf0, 0x20, 0x83, 0xe5, /*  120:    str      r2, [r3, #240]                     */
		0xf0, 0x20, 0x93, 0xe5, /*  124:    ldr      r2, [r3, #240]                     */
		0x01, 0x24, 0x82, 0xe3, /*  128:    orr      r2, r2, #16777216                  */
		0xf0, 0x20, 0x83, 0xe5, /*  12c:    str      r2, [r3, #240]                     */
		0x00, 0x21, 0x93, 0xe5, /*  130:    ldr      r2, [r3, #256]                     */
		0x40, 0x20, 0x82, 0xe3, /*  134:    orr      r2, r2, #64                        */
		0x00, 0x21, 0x83, 0xe5, /*  138:    str      r2, [r3, #256]                     */
		0xf0, 0x8f, 0xbd, 0xe8, /*  13c:    pop      {r4, r5, r6, r7, r8, r9, sl, fp, pc} */
		0x00, 0x10, 0x98, 0xe5, /*  140:    ldr      r1, [r8]                           */
		0x0f, 0x00, 0x11, 0xe3, /*  144:    tst      r1, #15                            */
		0x00, 0x10, 0xd9, 0x15, /*  148:    ldrbne   r1, [r9]                           */
		0x01, 0xe0, 0x4e, 0x12, /*  14c:    subne    lr, lr, #1                         */
		0x01, 0x10, 0xcc, 0x14, /*  150:    strbne   r1, [ip], #1                       */
		0x01, 0x20, 0x52, 0xe2, /*  154:    subs     r2, r2, #1                         */
		0xcd, 0xff, 0xff, 0x1a, /*  158:    bne      94 <spi_batch_data_transfer+0x94>  */
		0xec, 0xff, 0xff, 0xea, /*  15c:    b        114 <spi_batch_data_transfer+0x114> */
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
	aw_fel_remotefunc_prepare(dev, 36, arm_code, sizeof(arm_code), 10, args);
}
