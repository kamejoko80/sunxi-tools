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
		0xf7, 0x4f, 0x2d, 0xe9, /*    0:    push     {r0, r1, r2, r4, r5, r6, r7, r8, r9, sl, fp, lr} */
		0x01, 0xc0, 0xd0, 0xe5, /*    4:    ldrb     ip, [r0, #1]                       */
		0x00, 0xe0, 0xd0, 0xe5, /*    8:    ldrb     lr, [r0]                           */
		0x02, 0x40, 0xd0, 0xe5, /*    c:    ldrb     r4, [r0, #2]                       */
		0x0c, 0xe4, 0x8e, 0xe1, /*   10:    orr      lr, lr, ip, lsl #8                 */
		0x40, 0x00, 0x5e, 0xe3, /*   14:    cmp      lr, #64                            */
		0x03, 0xc0, 0xd0, 0xe5, /*   18:    ldrb     ip, [r0, #3]                       */
		0x6c, 0x51, 0x9f, 0xe5, /*   1c:    ldr      r5, [pc, #364]                     */
		0x6c, 0x81, 0x9f, 0x85, /*   20:    ldrhi    r8, [pc, #364]                     */
		0x6c, 0x81, 0x9f, 0x95, /*   24:    ldrls    r8, [pc, #364]                     */
		0x24, 0xb0, 0x95, 0xe5, /*   28:    ldr      fp, [r5, #36]                      */
		0x44, 0x70, 0x9d, 0xe5, /*   2c:    ldr      r7, [sp, #68]                      */
		0x0c, 0x44, 0x84, 0xe1, /*   30:    orr      r4, r4, ip, lsl #8                 */
		0x04, 0x20, 0x8d, 0xe5, /*   34:    str      r2, [sp, #4]                       */
		0x30, 0x90, 0x9d, 0xe5, /*   38:    ldr      r9, [sp, #48]                      */
		0x38, 0xa0, 0x9d, 0xe5, /*   3c:    ldr      sl, [sp, #56]                      */
		0x3c, 0x20, 0x9d, 0xe5, /*   40:    ldr      r2, [sp, #60]                      */
		0x24, 0x80, 0x85, 0xe5, /*   44:    str      r8, [r5, #36]                      */
		0x00, 0x80, 0xe0, 0xe3, /*   48:    mvn      r8, #0                             */
		0x00, 0x80, 0x83, 0xe5, /*   4c:    str      r8, [r3]                           */
		0x04, 0x80, 0x8e, 0xe0, /*   50:    add      r8, lr, r4                         */
		0x00, 0x80, 0x82, 0xe5, /*   54:    str      r8, [r2]                           */
		0x40, 0x80, 0x9d, 0xe5, /*   58:    ldr      r8, [sp, #64]                      */
		0x04, 0xc0, 0x8e, 0xe2, /*   5c:    add      ip, lr, #4                         */
		0x00, 0x00, 0x57, 0xe3, /*   60:    cmp      r7, #0                             */
		0x04, 0x60, 0x80, 0xe2, /*   64:    add      r6, r0, #4                         */
		0x0c, 0xc0, 0x80, 0xe0, /*   68:    add      ip, r0, ip                         */
		0x00, 0xe0, 0x88, 0xe5, /*   6c:    str      lr, [r8]                           */
		0x04, 0x00, 0x00, 0x0a, /*   70:    beq      88 <spi_batch_data_transfer+0x88>  */
		0x00, 0x80, 0x97, 0xe5, /*   74:    ldr      r8, [r7]                           */
		0xff, 0x84, 0x08, 0xe2, /*   78:    and      r8, r8, #-16777216                 */
		0x08, 0x80, 0x8e, 0xe1, /*   7c:    orr      r8, lr, r8                         */
		0x0f, 0x84, 0xc8, 0xe3, /*   80:    bic      r8, r8, #251658240                 */
		0x00, 0x80, 0x87, 0xe5, /*   84:    str      r8, [r7]                           */
		0x00, 0x80, 0x0f, 0xe1, /*   88:    mrs      r8, CPSR                           */
		0xc0, 0x70, 0x88, 0xe3, /*   8c:    orr      r7, r8, #192                       */
		0x07, 0xf0, 0x21, 0xe1, /*   90:    msr      CPSR_c, r7                         */
		0x00, 0x70, 0x91, 0xe5, /*   94:    ldr      r7, [r1]                           */
		0x04, 0x20, 0x9d, 0xe5, /*   98:    ldr      r2, [sp, #4]                       */
		0x01, 0x04, 0x80, 0xe2, /*   9c:    add      r0, r0, #16777216                  */
		0x02, 0x70, 0x87, 0xe1, /*   a0:    orr      r7, r7, r2                         */
		0x04, 0x00, 0x80, 0xe2, /*   a4:    add      r0, r0, #4                         */
		0x00, 0x70, 0x81, 0xe5, /*   a8:    str      r7, [r1]                           */
		0x00, 0x00, 0x5e, 0xe3, /*   ac:    cmp      lr, #0                             */
		0x12, 0x00, 0x00, 0x1a, /*   b0:    bne      100 <spi_batch_data_transfer+0x100> */
		0x01, 0x24, 0xa0, 0xe3, /*   b4:    mov      r2, #16777216                      */
		0x00, 0x00, 0x54, 0xe3, /*   b8:    cmp      r4, #0                             */
		0x2b, 0x00, 0x00, 0x1a, /*   bc:    bne      170 <spi_batch_data_transfer+0x170> */
		0x00, 0x30, 0x93, 0xe5, /*   c0:    ldr      r3, [r3]                           */
		0x07, 0x0c, 0x13, 0xe3, /*   c4:    tst      r3, #1792                          */
		0x09, 0x00, 0x00, 0x0a, /*   c8:    beq      f4 <spi_batch_data_transfer+0xf4>  */
		0x02, 0x34, 0xa0, 0xe3, /*   cc:    mov      r3, #33554432                      */
		0xf0, 0x20, 0x93, 0xe5, /*   d0:    ldr      r2, [r3, #240]                     */
		0x0f, 0x24, 0xc2, 0xe3, /*   d4:    bic      r2, r2, #251658240                 */
		0xf0, 0x20, 0x83, 0xe5, /*   d8:    str      r2, [r3, #240]                     */
		0xf0, 0x20, 0x93, 0xe5, /*   dc:    ldr      r2, [r3, #240]                     */
		0x01, 0x24, 0x82, 0xe3, /*   e0:    orr      r2, r2, #16777216                  */
		0xf0, 0x20, 0x83, 0xe5, /*   e4:    str      r2, [r3, #240]                     */
		0x00, 0x21, 0x93, 0xe5, /*   e8:    ldr      r2, [r3, #256]                     */
		0x40, 0x20, 0x82, 0xe3, /*   ec:    orr      r2, r2, #64                        */
		0x00, 0x21, 0x83, 0xe5, /*   f0:    str      r2, [r3, #256]                     */
		0x24, 0xb0, 0x85, 0xe5, /*   f4:    str      fp, [r5, #36]                      */
		0x08, 0xf0, 0x21, 0xe1, /*   f8:    msr      CPSR_c, r8                         */
		0x19, 0x00, 0x00, 0xea, /*   fc:    b        168 <spi_batch_data_transfer+0x168> */
		0x00, 0x20, 0x93, 0xe5, /*  100:    ldr      r2, [r3]                           */
		0x10, 0x00, 0x12, 0xe3, /*  104:    tst      r2, #16                            */
		0xfc, 0xff, 0xff, 0x0a, /*  108:    beq      100 <spi_batch_data_transfer+0x100> */
		0x34, 0x10, 0x9d, 0xe5, /*  10c:    ldr      r1, [sp, #52]                      */
		0x01, 0x20, 0xd6, 0xe4, /*  110:    ldrb     r2, [r6], #1                       */
		0x00, 0x00, 0x54, 0xe3, /*  114:    cmp      r4, #0                             */
		0x01, 0xe0, 0x4e, 0xe2, /*  118:    sub      lr, lr, #1                         */
		0x00, 0x20, 0xc1, 0xe5, /*  11c:    strb     r2, [r1]                           */
		0x04, 0x00, 0x00, 0x0a, /*  120:    beq      138 <spi_batch_data_transfer+0x138> */
		0x00, 0x20, 0x99, 0xe5, /*  124:    ldr      r2, [r9]                           */
		0x0f, 0x00, 0x12, 0xe3, /*  128:    tst      r2, #15                            */
		0x00, 0x20, 0xda, 0x15, /*  12c:    ldrbne   r2, [sl]                           */
		0x01, 0x40, 0x44, 0x12, /*  130:    subne    r4, r4, #1                         */
		0x01, 0x20, 0xcc, 0x14, /*  134:    strbne   r2, [ip], #1                       */
		0x06, 0x00, 0x50, 0xe1, /*  138:    cmp      r0, r6                             */
		0xda, 0xff, 0xff, 0x1a, /*  13c:    bne      ac <spi_batch_data_transfer+0xac>  */
		0x02, 0x34, 0xa0, 0xe3, /*  140:    mov      r3, #33554432                      */
		0xf0, 0x20, 0x93, 0xe5, /*  144:    ldr      r2, [r3, #240]                     */
		0x0f, 0x24, 0xc2, 0xe3, /*  148:    bic      r2, r2, #251658240                 */
		0xf0, 0x20, 0x83, 0xe5, /*  14c:    str      r2, [r3, #240]                     */
		0xf0, 0x20, 0x93, 0xe5, /*  150:    ldr      r2, [r3, #240]                     */
		0x01, 0x24, 0x82, 0xe3, /*  154:    orr      r2, r2, #16777216                  */
		0xf0, 0x20, 0x83, 0xe5, /*  158:    str      r2, [r3, #240]                     */
		0x00, 0x21, 0x93, 0xe5, /*  15c:    ldr      r2, [r3, #256]                     */
		0x40, 0x20, 0x82, 0xe3, /*  160:    orr      r2, r2, #64                        */
		0x00, 0x21, 0x83, 0xe5, /*  164:    str      r2, [r3, #256]                     */
		0x0c, 0xd0, 0x8d, 0xe2, /*  168:    add      sp, sp, #12                        */
		0xf0, 0x8f, 0xbd, 0xe8, /*  16c:    pop      {r4, r5, r6, r7, r8, r9, sl, fp, pc} */
		0x00, 0x10, 0x99, 0xe5, /*  170:    ldr      r1, [r9]                           */
		0x0f, 0x00, 0x11, 0xe3, /*  174:    tst      r1, #15                            */
		0x00, 0x10, 0xda, 0x15, /*  178:    ldrbne   r1, [sl]                           */
		0x01, 0x40, 0x44, 0x12, /*  17c:    subne    r4, r4, #1                         */
		0x01, 0x10, 0xcc, 0x14, /*  180:    strbne   r1, [ip], #1                       */
		0x01, 0x20, 0x52, 0xe2, /*  184:    subs     r2, r2, #1                         */
		0xca, 0xff, 0xff, 0x1a, /*  188:    bne      b8 <spi_batch_data_transfer+0xb8>  */
		0xeb, 0xff, 0xff, 0xea, /*  18c:    b        140 <spi_batch_data_transfer+0x140> */
		0x00, 0x50, 0x02, 0x04, /*  190:    .word    0x04025000                         */
		0x02, 0x02, 0x00, 0x00, /*  194:    .word    0x00000202                         */
		0x02, 0x03, 0x00, 0x00, /*  198:    .word    0x00000302                         */
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
	aw_fel_remotefunc_prepare(dev, 48, arm_code, sizeof(arm_code), 10, args);
}
