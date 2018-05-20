# 1 "D:\\localrep\\Proximo\\Proximo_app\\ARM_Startup.s"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "D:\\localrep\\Proximo\\Proximo_app\\ARM_Startup.s"
# 12 "D:\\localrep\\Proximo\\Proximo_app\\ARM_Startup.s"
  .section .vectors, "ax"
  .code 32
  .align 0
  .global _vectors
  .global reset_handler

_vectors:
  ldr pc, =reset_handler
  ldr pc, =undef_handler
  ldr pc, =swi_handler
  ldr pc, =pabort_handler
  ldr pc, =dabort_handler
  nop
  ldr pc, =irq_handler
  ldr pc, =fiq_handler

  .section .init, "ax"
  .code 32
  .align 0






reset_handler:
# 50 "D:\\localrep\\Proximo\\Proximo_app\\ARM_Startup.s"
  mrc p15, #0x00, r0, c1, c0, #0x02
  orr r0, r0, #0x00F00000
  mcr p15, #0x00, r0, c1, c0, #0x02

  mov r0, #0x40000000
  fmxr fpexc, r0





  b _start
# 70 "D:\\localrep\\Proximo\\Proximo_app\\ARM_Startup.s"
  .global undef_handler
  .type undef_handler, function
undef_handler:
  b undef_handler

  .global swi_handler
  .type swi_handler, function
swi_handler:
  b swi_handler

  .global pabort_handler
  .type pabort_handler, function
pabort_handler:
  b pabort_handler

  .global dabort_handler
  .type dabort_handler, function
dabort_handler:
  b dabort_handler

  .global irq_handler
  .type irq_handler, function
irq_handler:
  b irq_handler

  .global fiq_handler
  .type fiq_handler, function
fiq_handler:
  b fiq_handler

  .weak undef_handler, swi_handler, pabort_handler, dabort_handler, irq_handler, fiq_handler
