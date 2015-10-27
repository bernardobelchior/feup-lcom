#include "i8042.h"

.data
last	= 0x00
attempts = 5

.global _funcasm

.text
_funcasm:
movl $0, %ecx
while:
movl $KB_STATUS, %ebx
pushl %eax
movl %ebx, %eax
andl $KB_OUTBUF_FULL, %eax
cmpl $0, %eax
jz endouterif
movl $KB_STAT_PARITY, %eax
orl $KB_STAT_PARITY, %eax
andl %ebx, %eax
cmpl $0, %eax
jnz endouterif
popl %eax

movl $KB_OUT_BUF, %eax

pushl %eax
cmpl $KB_2BYTE_SCODE, %eax
popl %eax
jnz endfirstif

movl $0x00, last
jmp endfunc
endfirstif:

pushl %eax
movl $last, %eax
cmpl $KB_2BYTE_SCODE, %eax
popl %eax
jnz endsecondif

movl $last, %edx
shll $4, %edx
orl %edx, %eax

movl $0x00, last

jmp endfunc
endsecondif:
endouterif:
jmp endfunc
loop while

endfunc:ret
