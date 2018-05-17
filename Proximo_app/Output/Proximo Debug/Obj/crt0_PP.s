# 1 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
# 52 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
  .section .init, "ax"
  .code 32
  .align 4
# 64 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
  .weak _start
  .global __start
  .extern main
  .global exit
  .weak exit
# 78 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
_start:
__start:
  mrs r0, cpsr
  bic r0, r0, #0x1F


  orr r1, r0, #0x1B
  msr cpsr_cxsf, r1
  ldr sp, =__stack_und_end__

  bic sp, sp, #0x7


  orr r1, r0, #0x17
  msr cpsr_cxsf, r1
  ldr sp, =__stack_abt_end__

  bic sp, sp, #0x7


  orr r1, r0, #0x12
  msr cpsr_cxsf, r1
  ldr sp, =__stack_irq_end__

  bic sp, sp, #0x7


  orr r1, r0, #0x11
  msr cpsr_cxsf, r1
  ldr sp, =__stack_fiq_end__

  bic sp, sp, #0x7


  orr r1, r0, #0x13
  msr cpsr_cxsf, r1
  ldr sp, =__stack_svc_end__

  bic sp, sp, #0x7
# 130 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
  orr r1, r0, #0x1F
  msr cpsr_cxsf, r1
  ldr sp, =__stack_end__

  bic sp, sp, #0x7
# 161 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
  ldr r0, =__data_load_start__
  ldr r1, =__data_start__
  ldr r2, =__data_end__
  bl memory_copy
  ldr r0, =__text_load_start__
  ldr r1, =__text_start__
  ldr r2, =__text_end__
  bl memory_copy
  ldr r0, =__fast_load_start__
  ldr r1, =__fast_start__
  ldr r2, =__fast_end__
  bl memory_copy
  ldr r0, =__ctors_load_start__
  ldr r1, =__ctors_start__
  ldr r2, =__ctors_end__
  bl memory_copy
  ldr r0, =__dtors_load_start__
  ldr r1, =__dtors_start__
  ldr r2, =__dtors_end__
  bl memory_copy
  ldr r0, =__rodata_load_start__
  ldr r1, =__rodata_start__
  ldr r2, =__rodata_end__
  bl memory_copy
  ldr r0, =__tdata_load_start__
  ldr r1, =__tdata_start__
  ldr r2, =__tdata_end__
  bl memory_copy
# 205 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
  ldr r0, =__bss_start__
  ldr r1, =__bss_end__
  mov r2, #0
  bl memory_set
  ldr r0, =__tbss_start__
  ldr r1, =__tbss_end__
  mov r2, #0
  bl memory_set
# 221 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
  ldr r0, = __heap_start__
  ldr r1, = __heap_end__
  sub r1, r1, r0
  cmp r1, #8
  movge r2, #0
  strge r2, [r0], #+4
  strge r1, [r0]
# 240 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
  ldr r0, =__ctors_start__
  ldr r1, =__ctors_end__
ctor_loop:
  cmp r0, r1
  beq ctor_end
  ldr r2, [r0], #+4
  stmfd sp!, {r0-r1}
  mov lr, pc



  bx r2

  ldmfd sp!, {r0-r1}
  b ctor_loop
ctor_end:

  .type start, function
start:
# 272 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
  mov r0, #0
  mov r1, #0

  ldr r2, =main
  mov lr, pc



  bx r2


exit:
# 327 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
exit_loop:
  b exit_loop

memory_copy:
  cmp r0, r1
  moveq pc, lr
  subs r2, r2, r1
  moveq pc, lr


  orr r3, r0, r1
  orr r3, r3, r2
  tst r3, #0x3
  bne 2f

1:
  ldr r3, [r0], #+4
  str r3, [r1], #+4
  subs r2, r2, #4
  bne 1b
  mov pc, lr

2:
  ldrb r3, [r0], #+1
  strb r3, [r1], #+1
  subs r2, r2, #1
  bne 2b
  mov pc, lr

memory_set:
  cmp r0, r1
  moveq pc, lr
  strb r2, [r0], #1
  b memory_set



.macro HELPER helper_name
  .section .text.\helper_name, "ax", %progbits
  .type \helper_name, function
  .global \helper_name
  .weak \helper_name
\helper_name:
.endm

HELPER __aeabi_read_tp
  ldr r0, =__tbss_start__-8
  bx lr
HELPER __heap_lock
  bx lr
HELPER __heap_unlock
  bx lr
HELPER __printf_lock
  bx lr
HELPER __printf_unlock
  bx lr
HELPER __scanf_lock
  bx lr
HELPER __scanf_unlock
  bx lr
HELPER __debug_io_lock
  bx lr
HELPER __debug_io_unlock
  bx lr
HELPER abort
  b .
HELPER __assert
  b .
HELPER __aeabi_assert
  b .
HELPER __cxa_pure_virtual
  b .
HELPER __cxa_guard_acquire
  ldr r3, [r0]
  tst r3, #1
  beq 1f
  movs r0, #0
  bx lr
1:
  movs r0, #1
  bx lr
HELPER __cxa_guard_release
  movs r3, #1
  str r3, [r0]
  bx lr
HELPER __cxa_guard_abort
  bx lr
HELPER __sync_synchronize
  bx lr
HELPER __getchar
  b debug_getchar
HELPER __putchar
  b debug_putchar
HELPER __open
  b debug_fopen
HELPER __close
  b debug_fclose
HELPER __write
  mov r3, r0
  mov r0, r1
  mov r1, #1
  b debug_fwrite
HELPER __read
  mov r3, r0
  mov r0, r1
  mov r1, #1
  b debug_fread
HELPER __seek
  push {r4, lr}
  mov r4, r0
  bl debug_fseek
  cmp r0, #0
  bne 1f
  mov r0, r4
  bl debug_ftell
  b 2f
1:
  ldr r0, =-1
2:
  pop {r4, lr}
  bx lr

  .section .bss.__user_locale_name_buffer, "aw", %nobits
  .global __user_locale_name_buffer
  .weak __user_locale_name_buffer
  __user_locale_name_buffer:
  .word 0x0
# 462 "D:\\localrep\\Proximo\\Proximo_app\\crt0.s"
  .section .stack, "wa", %nobits
  .section .stack_abt, "wa", %nobits
  .section .stack_irq, "wa", %nobits
  .section .stack_fiq, "wa", %nobits
  .section .stack_svc, "wa", %nobits
  .section .stack_und, "wa", %nobits
  .section .heap, "wa", %nobits
