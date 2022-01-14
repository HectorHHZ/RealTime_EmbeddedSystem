.syntax unified

.global asm_sub
.global asm_led
.global add_overflow
.global add_overflow1
.global add_6
.global add_overflow1


asm_sub:
    SUB r0, r0, r1
    bx lr;




asm_led:
    cmp r0, #0
    beq ifZero
    sub r0, r0, #1
    bx lr;

ifZero:
    add r0, r0, #1
    bx lr;

// Part3 method 1
add_overflow:
    adds r0, r0, r1
    bvs ifSet
    mov r0, #0
    bx lr;
ifSet:
    mov r0, #1
    bx lr;
    
//Part3 method 2
add_overflow1:
    adds r0, r0, r1
    ite VS
    movvs r0, #1
    movvc r0, #0
    bx lr;

add_6:
    push {r11}
    add r0, r0, r1
    add r0, r0, r2
    add r0, r0, r3
    ldr r11, [sp, #4]
    add r0, r0, r11
    ldr r11, [sp, #8]
    add r0, r0, r11
    pop {r11}
    bx lr;

