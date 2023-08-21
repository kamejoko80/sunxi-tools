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
		0x00, 0x50, 0xd0, 0xe5, /*    8:    ldrb     r5, [r0]                           */
		0x02, 0x40, 0xd0, 0xe5, /*    c:    ldrb     r4, [r0, #2]                       */
		0x0c, 0x54, 0x85, 0xe1, /*   10:    orr      r5, r5, ip, lsl #8                 */
		0x03, 0xc0, 0xd0, 0xe5, /*   14:    ldrb     ip, [r0, #3]                       */
		0x00, 0xe0, 0xe0, 0xe3, /*   18:    mvn      lr, #0                             */
		0x00, 0xe0, 0x83, 0xe5, /*   1c:    str      lr, [r3]                           */
		0x0c, 0x44, 0x84, 0xe1, /*   20:    orr      r4, r4, ip, lsl #8                 */
		0x30, 0xe0, 0x9d, 0xe5, /*   24:    ldr      lr, [sp, #48]                      */
		0x38, 0x70, 0x9d, 0xe5, /*   28:    ldr      r7, [sp, #56]                      */
		0x04, 0xb0, 0x85, 0xe0, /*   2c:    add      fp, r5, r4                         */
		0x00, 0xb0, 0x8e, 0xe5, /*   30:    str      fp, [lr]                           */
		0x34, 0xe0, 0x9d, 0xe5, /*   34:    ldr      lr, [sp, #52]                      */
		0x04, 0xc0, 0x85, 0xe2, /*   38:    add      ip, r5, #4                         */
		0x00, 0x00, 0x57, 0xe3, /*   3c:    cmp      r7, #0                             */
		0x24, 0x80, 0x9d, 0xe5, /*   40:    ldr      r8, [sp, #36]                      */
		0x28, 0xa0, 0x9d, 0xe5, /*   44:    ldr      sl, [sp, #40]                      */
		0x2c, 0x90, 0x9d, 0xe5, /*   48:    ldr      r9, [sp, #44]                      */
		0x04, 0x60, 0x80, 0xe2, /*   4c:    add      r6, r0, #4                         */
		0x0c, 0xc0, 0x80, 0xe0, /*   50:    add      ip, r0, ip                         */
		0x00, 0x50, 0x8e, 0xe5, /*   54:    str      r5, [lr]                           */
		0x09, 0x00, 0x00, 0x0a, /*   58:    beq      84 <spi_batch_data_transfer+0x84>  */
		0x00, 0xe0, 0x97, 0xe5, /*   5c:    ldr      lr, [r7]                           */
		0x04, 0xb0, 0xd0, 0xe5, /*   60:    ldrb     fp, [r0, #4]                       */
		0xff, 0xe4, 0x0e, 0xe2, /*   64:    and      lr, lr, #-16777216                 */
		0x0e, 0xe0, 0x85, 0xe1, /*   68:    orr      lr, r5, lr                         */
		0x32, 0x00, 0x5b, 0xe3, /*   6c:    cmp      fp, #50                            */
		0x6b, 0x00, 0x5b, 0x13, /*   70:    cmpne    fp, #107                           */
		0x0f, 0xe4, 0xce, 0x03, /*   74:    biceq    lr, lr, #251658240                 */
		0x02, 0xe2, 0x8e, 0x03, /*   78:    orreq    lr, lr, #536870912                 */
		0x2f, 0xe4, 0xce, 0x13, /*   7c:    bicne    lr, lr, #788529152                 */
		0x00, 0xe0, 0x87, 0xe5, /*   80:    str      lr, [r7]                           */
		0x00, 0xe0, 0x0f, 0xe1, /*   84:    mrs      lr, CPSR                           */
		0xc0, 0x70, 0x8e, 0xe3, /*   88:    orr      r7, lr, #192                       */
		0x07, 0xf0, 0x21, 0xe1, /*   8c:    msr      CPSR_c, r7                         */
		0x00, 0x70, 0x91, 0xe5, /*   90:    ldr      r7, [r1]                           */
		0x01, 0x04, 0x80, 0xe2, /*   94:    add      r0, r0, #16777216                  */
		0x02, 0x20, 0x87, 0xe1, /*   98:    orr      r2, r7, r2                         */
		0x04, 0x00, 0x80, 0xe2, /*   9c:    add      r0, r0, #4                         */
		0x00, 0x20, 0x81, 0xe5, /*   a0:    str      r2, [r1]                           */
		0x00, 0x00, 0x55, 0xe3, /*   a4:    cmp      r5, #0                             */
		0x07, 0x00, 0x00, 0x1a, /*   a8:    bne      cc <spi_batch_data_transfer+0xcc>  */
		0x01, 0x24, 0xa0, 0xe3, /*   ac:    mov      r2, #16777216                      */
		0x00, 0x00, 0x54, 0xe3, /*   b0:    cmp      r4, #0                             */
		0x1f, 0x00, 0x00, 0x1a, /*   b4:    bne      138 <spi_batch_data_transfer+0x138> */
		0x00, 0x30, 0x93, 0xe5, /*   b8:    ldr      r3, [r3]                           */
		0x07, 0x0c, 0x13, 0xe3, /*   bc:    tst      r3, #1792                          */
		0x11, 0x00, 0x00, 0x1a, /*   c0:    bne      10c <spi_batch_data_transfer+0x10c> */
		0x0e, 0xf0, 0x21, 0xe1, /*   c4:    msr      CPSR_c, lr                         */
		0xf0, 0x8f, 0xbd, 0xe8, /*   c8:    pop      {r4, r5, r6, r7, r8, r9, sl, fp, pc} */
		0x00, 0x20, 0x93, 0xe5, /*   cc:    ldr      r2, [r3]                           */
		0x10, 0x00, 0x12, 0xe3, /*   d0:    tst      r2, #16                            */
		0xfc, 0xff, 0xff, 0x0a, /*   d4:    beq      cc <spi_batch_data_transfer+0xcc>  */
		0x01, 0x20, 0xd6, 0xe4, /*   d8:    ldrb     r2, [r6], #1                       */
		0x00, 0x00, 0x54, 0xe3, /*   dc:    cmp      r4, #0                             */
		0x01, 0x50, 0x45, 0xe2, /*   e0:    sub      r5, r5, #1                         */
		0x00, 0x20, 0xca, 0xe5, /*   e4:    strb     r2, [sl]                           */
		0x05, 0x00, 0x00, 0x0a, /*   e8:    beq      104 <spi_batch_data_transfer+0x104> */
		0x00, 0x20, 0x98, 0xe5, /*   ec:    ldr      r2, [r8]                           */
		0xff, 0x20, 0x02, 0xe2, /*   f0:    and      r2, r2, #255                       */
		0x00, 0x00, 0x52, 0xe3, /*   f4:    cmp      r2, #0                             */
		0x00, 0x20, 0xd9, 0x15, /*   f8:    ldrbne   r2, [r9]                           */
		0x01, 0x40, 0x44, 0x12, /*   fc:    subne    r4, r4, #1                         */
		0x01, 0x20, 0xcc, 0x14, /*  100:    strbne   r2, [ip], #1                       */
		0x06, 0x00, 0x50, 0xe1, /*  104:    cmp      r0, r6                             */
		0xe5, 0xff, 0xff, 0x1a, /*  108:    bne      a4 <spi_batch_data_transfer+0xa4>  */
		0x02, 0x34, 0xa0, 0xe3, /*  10c:    mov      r3, #33554432                      */
		0xf0, 0x20, 0x93, 0xe5, /*  110:    ldr      r2, [r3, #240]                     */
		0x0f, 0x24, 0xc2, 0xe3, /*  114:    bic      r2, r2, #251658240                 */
		0xf0, 0x20, 0x83, 0xe5, /*  118:    str      r2, [r3, #240]                     */
		0xf0, 0x20, 0x93, 0xe5, /*  11c:    ldr      r2, [r3, #240]                     */
		0x01, 0x24, 0x82, 0xe3, /*  120:    orr      r2, r2, #16777216                  */
		0xf0, 0x20, 0x83, 0xe5, /*  124:    str      r2, [r3, #240]                     */
		0x00, 0x21, 0x93, 0xe5, /*  128:    ldr      r2, [r3, #256]                     */
		0x40, 0x20, 0x82, 0xe3, /*  12c:    orr      r2, r2, #64                        */
		0x00, 0x21, 0x83, 0xe5, /*  130:    str      r2, [r3, #256]                     */
		0xf0, 0x8f, 0xbd, 0xe8, /*  134:    pop      {r4, r5, r6, r7, r8, r9, sl, fp, pc} */
		0x00, 0x10, 0x98, 0xe5, /*  138:    ldr      r1, [r8]                           */
		0xff, 0x10, 0x01, 0xe2, /*  13c:    and      r1, r1, #255                       */
		0x00, 0x00, 0x51, 0xe3, /*  140:    cmp      r1, #0                             */
		0x00, 0x10, 0xd9, 0x15, /*  144:    ldrbne   r1, [r9]                           */
		0x01, 0x40, 0x44, 0x12, /*  148:    subne    r4, r4, #1                         */
		0x01, 0x10, 0xcc, 0x14, /*  14c:    strbne   r1, [ip], #1                       */
		0x01, 0x20, 0x52, 0xe2, /*  150:    subs     r2, r2, #1                         */
		0xd5, 0xff, 0xff, 0x1a, /*  154:    bne      b0 <spi_batch_data_transfer+0xb0>  */
		0xeb, 0xff, 0xff, 0xea, /*  158:    b        10c <spi_batch_data_transfer+0x10c> */
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
