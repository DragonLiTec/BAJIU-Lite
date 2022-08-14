.section .init
.globl _start
.type _start,@function
_start:
#ifdef USE_GP
.option push
.option norelax
	la gp, __global_pointer$
.option pop
#endif

init:
	la sp, _sp

	/* Load data section */
	la a0, _data_lma
	la a1, _data
	la a2, _edata
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, 1b
2:

	/* Clear bss section */
	la a0, __bss_start
	la a1, _end
	bgeu a0, a1, 2f
1:
	sw zero, (a0)
	addi a0, a0, 4
	bltu a0, a1, 1b
2:

#ifndef DISABLE_LIBC
    call __libc_init_array
#endif
	call main
_done:
	j _done

.globl _init
_init:
	ret

.type trap_entry,@function
.global  trap_entry
.align(4) //mtvec require 32 bits allignement
trap_entry:
	addi sp,sp, -16*4
	sw x1,   0*4(sp)
	sw x5,   1*4(sp)
	sw x6,   2*4(sp)
	sw x7,   3*4(sp)
	sw x10,  4*4(sp)
	sw x11,  5*4(sp)
	sw x12,  6*4(sp)
	sw x13,  7*4(sp)
	sw x14,  8*4(sp)
	sw x15,  9*4(sp)
	sw x16, 10*4(sp)
	sw x17, 11*4(sp)
	sw x28, 12*4(sp)
	sw x29, 13*4(sp)
	sw x30, 14*4(sp)
	sw x31, 15*4(sp)
	call interrupt_handler
	lw x1 ,  0*4(sp)
	lw x5,   1*4(sp)
	lw x6,   2*4(sp)
	lw x7,   3*4(sp)
	lw x10,  4*4(sp)
	lw x11,  5*4(sp)
	lw x12,  6*4(sp)
	lw x13,  7*4(sp)
	lw x14,  8*4(sp)
	lw x15,  9*4(sp)
	lw x16, 10*4(sp)
	lw x17, 11*4(sp)
	lw x28, 12*4(sp)
	lw x29, 13*4(sp)
	lw x30, 14*4(sp)
	lw x31, 15*4(sp)
	addi sp,sp, 16*4
	mret
