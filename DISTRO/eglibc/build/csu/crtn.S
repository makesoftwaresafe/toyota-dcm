	.cpu cortex-a5
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfpv4
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 18, 4
#APP
	
#include "defs.h"
	
/*@HEADER_ENDS*/
/*@_init_EPILOG_BEGINS*/
@ 0 "" 2
@ 101 "../sysdeps/generic/initfini.c" 1
	.section .init
@ 0 "" 2
	ldmfd	sp!, {r3, pc}
#APP
	END_INIT
	
/*@_init_EPILOG_ENDS*/
/*@_fini_EPILOG_BEGINS*/
@ 0 "" 2
@ 130 "../sysdeps/generic/initfini.c" 1
	.section .fini
@ 0 "" 2
	ldmfd	sp!, {r3, pc}
#APP
	END_FINI
	
/*@_fini_EPILOG_ENDS*/
/*@TRAILER_BEGINS*/
	.weak	__gmon_start__
	.ident	"GCC: (GNU) 4.6.2"
	.section	.note.GNU-stack,"",%progbits
