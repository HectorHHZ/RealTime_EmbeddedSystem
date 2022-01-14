.syntax unified

.global asm_sub
.global asm_led
.global add_overflow
.global add_6


asm_sub:
    SUB r0, r0, r1
    bx lr;


asm_led:
    bx lr;


