#include "i8042.h"

.data
last = 0x00
attempts = 5

.global _funcasm

.text
_funcasm:
movl $0, %ecx						;initializes counter
while:
movl $KB_STATUS, %ebx
pushl %eax
movl %ebx, %eax
andl $KB_OUTBUF_FULL, %eax
cmpl $0, %eax							;checks output buffer status
jz endouterif
movl $KB_STAT_PARITY, %eax
orl $KB_STAT_TIMEOUT, %eax					;checks parity and timeout bits
andl %ebx, %eax
cmpl $0, %eax
jnz endouterif
popl %eax

movl $KB_OUT_BUF, %eax

pushl %eax
cmpl $KB_2BYTE_SCODE, %eax		;checks if key pressed has a 2 byte scancode
popl %eax
jnz endfirstif

movl %eax, last				;stores last scancode
jmp endfunc
endfirstif:

pushl %eax
movl $last, %eax
cmpl $KB_2BYTE_SCODE, %eax			;checks last scancode for 1st byte of 2 byte scancode
popl %eax
jnz endsecondif

movl $last, %edx
shll $4, %edx
orl %edx, %eax		;completes 2 byte scancode

movl $0x00, last

jmp endfunc
endsecondif:
endouterif:
jmp endfunc
loop while

endfunc:ret
