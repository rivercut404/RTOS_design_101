Uart.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <Hal_uart_init>:
   0:   e52db004        push    {fp}            ; (str fp, [sp, #-4]!)
   4:   e28db000        add     fp, sp, #0
   8:   e3003000        movw    r3, #0
   c:   e3403000        movt    r3, #0
  10:   e5932000        ldr     r2, [r3]
  14:   e5923030        ldr     r3, [r2, #48]   ; 0x30
  18:   e7c0301f        bfc     r3, #0, #1
  1c:   e5823030        str     r3, [r2, #48]   ; 0x30
  20:   e3003000        movw    r3, #0
  24:   e3403000        movt    r3, #0
  28:   e5932000        ldr     r2, [r3]
  2c:   e5923030        ldr     r3, [r2, #48]   ; 0x30
  30:   e3833c01        orr     r3, r3, #256    ; 0x100
  34:   e5823030        str     r3, [r2, #48]   ; 0x30
  38:   e3003000        movw    r3, #0
  3c:   e3403000        movt    r3, #0
  40:   e5932000        ldr     r2, [r3]
  44:   e5923030        ldr     r3, [r2, #48]   ; 0x30
  48:   e3833c02        orr     r3, r3, #512    ; 0x200
  4c:   e5823030        str     r3, [r2, #48]   ; 0x30
  50:   e3003000        movw    r3, #0
  54:   e3403000        movt    r3, #0
  58:   e5932000        ldr     r2, [r3]
  5c:   e5923030        ldr     r3, [r2, #48]   ; 0x30
  60:   e3833001        orr     r3, r3, #1
  64:   e5823030        str     r3, [r2, #48]   ; 0x30
  68:   e320f000        nop     {0}
  6c:   e28bd000        add     sp, fp, #0
  70:   e49db004        pop     {fp}            ; (ldr fp, [sp], #4)
  74:   e12fff1e        bx      lr

00000078 <Hal_uart_put_char>:
  78:   e52db004        push    {fp}            ; (str fp, [sp, #-4]!)
  7c:   e28db000        add     fp, sp, #0
  80:   e24dd00c        sub     sp, sp, #12
  84:   e1a03000        mov     r3, r0
  88:   e54b3005        strb    r3, [fp, #-5]
  8c:   e320f000        nop     {0}
  90:   e3003000        movw    r3, #0
  94:   e3403000        movt    r3, #0
  98:   e5933000        ldr     r3, [r3]
  9c:   e5933018        ldr     r3, [r3, #24]
  a0:   e7e032d3        ubfx    r3, r3, #5, #1
  a4:   e6ef3073        uxtb    r3, r3
  a8:   e3530000        cmp     r3, #0
  ac:   1afffff7        bne     90 <Hal_uart_put_char+0x18>
  b0:   e3003000        movw    r3, #0
  b4:   e3403000        movt    r3, #0
  b8:   e5933000        ldr     r3, [r3]
  bc:   e55b2005        ldrb    r2, [fp, #-5]
  c0:   e5832000        str     r2, [r3]
  c4:   e320f000        nop     {0}
  c8:   e28bd000        add     sp, fp, #0
  cc:   e49db004        pop     {fp}            ; (ldr fp, [sp], #4)
  d0:   e12fff1e        bx      lr

000000d4 <Hal_uart_get_char>:
  d4:   e52db004        push    {fp}            ; (str fp, [sp, #-4]!)
  d8:   e28db000        add     fp, sp, #0
  dc:   e24dd00c        sub     sp, sp, #12
  e0:   e320f000        nop     {0}
  e4:   e3003000        movw    r3, #0
  e8:   e3403000        movt    r3, #0
  ec:   e5933000        ldr     r3, [r3]
  f0:   e5933018        ldr     r3, [r3, #24]
  f4:   e7e03253        ubfx    r3, r3, #4, #1
  f8:   e6ef3073        uxtb    r3, r3
  fc:   e3530000        cmp     r3, #0
 100:   1afffff7        bne     e4 <Hal_uart_get_char+0x10>
 104:   e3003000        movw    r3, #0
 108:   e3403000        movt    r3, #0
 10c:   e5933000        ldr     r3, [r3]
 110:   e5933000        ldr     r3, [r3]
 114:   e7e03553        ubfx    r3, r3, #10, #1
 118:   e6ef3073        uxtb    r3, r3
 11c:   e3530000        cmp     r3, #0
 120:   1a000017        bne     184 <Hal_uart_get_char+0xb0>
 124:   e3003000        movw    r3, #0
 128:   e3403000        movt    r3, #0
 12c:   e5933000        ldr     r3, [r3]
 130:   e5933000        ldr     r3, [r3]
 134:   e7e03453        ubfx    r3, r3, #8, #1
 138:   e6ef3073        uxtb    r3, r3
 13c:   e3530000        cmp     r3, #0
 140:   1a00000f        bne     184 <Hal_uart_get_char+0xb0>
 144:   e3003000        movw    r3, #0
 148:   e3403000        movt    r3, #0
 14c:   e5933000        ldr     r3, [r3]
 150:   e5933000        ldr     r3, [r3]
 154:   e7e035d3        ubfx    r3, r3, #11, #1
 158:   e6ef3073        uxtb    r3, r3
 15c:   e3530000        cmp     r3, #0
 160:   1a000007        bne     184 <Hal_uart_get_char+0xb0>
 164:   e3003000        movw    r3, #0
 168:   e3403000        movt    r3, #0
 16c:   e5933000        ldr     r3, [r3]
 170:   e5933000        ldr     r3, [r3]
 174:   e7e034d3        ubfx    r3, r3, #9, #1
 178:   e6ef3073        uxtb    r3, r3
 17c:   e3530000        cmp     r3, #0
 180:   0a000019        beq     1ec <Hal_uart_get_char+0x118>
 184:   e3003000        movw    r3, #0
 188:   e3403000        movt    r3, #0
 18c:   e5932000        ldr     r2, [r3]
 190:   e5923000        ldr     r3, [r2]
 194:   e3833b01        orr     r3, r3, #1024   ; 0x400
 198:   e5823000        str     r3, [r2]
 19c:   e3003000        movw    r3, #0
 1a0:   e3403000        movt    r3, #0
 1a4:   e5932000        ldr     r2, [r3]
 1a8:   e5923000        ldr     r3, [r2]
 1ac:   e3833c01        orr     r3, r3, #256    ; 0x100
 1b0:   e5823000        str     r3, [r2]
 1b4:   e3003000        movw    r3, #0
 1b8:   e3403000        movt    r3, #0
 1bc:   e5932000        ldr     r2, [r3]
 1c0:   e5923000        ldr     r3, [r2]
 1c4:   e3833b02        orr     r3, r3, #2048   ; 0x800
 1c8:   e5823000        str     r3, [r2]
 1cc:   e3003000        movw    r3, #0
 1d0:   e3403000        movt    r3, #0
 1d4:   e5932000        ldr     r2, [r3]
 1d8:   e5923000        ldr     r3, [r2]
 1dc:   e3833c02        orr     r3, r3, #512    ; 0x200
 1e0:   e5823000        str     r3, [r2]
 1e4:   e3a03000        mov     r3, #0
 1e8:   ea000005        b       204 <Hal_uart_get_char+0x130>
 1ec:   e3003000        movw    r3, #0
 1f0:   e3403000        movt    r3, #0
 1f4:   e5933000        ldr     r3, [r3]
 1f8:   e5933000        ldr     r3, [r3]
 1fc:   e54b3005        strb    r3, [fp, #-5]
 200:   e55b3005        ldrb    r3, [fp, #-5]
 204:   e1a00003        mov     r0, r3
 208:   e28bd000        add     sp, fp, #0
 20c:   e49db004        pop     {fp}            ; (ldr fp, [sp], #4)
 210:   e12fff1e        bx      lr