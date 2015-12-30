/* int vg_set_pixel(short x, short y, unsigned short color); */

.intel_syntax
.globl _vg_set_pixel_asm

.data

.text
_vg_set_pixel_asm:
	push	ebp
	mov	ebp, esp

	xor ebx, ebx
	//mov bx, [ebp+8]
	movzx WORD PTR ebx, [ebp+8]	// bx = x
	//cmp ebx, 0	// x < 0 ?
	//jb ret1
	movzx WORD PTR eax, _h_res
	cmp bx, ax	// x >= h_res ?
	jae ret2

	xor ecx, ecx
	movzx WORD PTR ecx, [ebp+12]	// cx = y
	//cmp ecx, 0	// y < 0 ?
	//jb ret3
	movzx WORD PTR eax, _v_res
	cmp ecx, eax	// y >= v_res ?
	jae ret4

	//if conditions are met, then proceed to set pixel

	mov esi, _double_buffer	//moves the double buffer to esi register

	imul ebx, 2 	// ebx = 2*x
	imul ecx, 2 	// ecx = 2*y
	imul ecx, _h_res	// ecx = 2*y*h_res
	add ebx, ecx	// ebx = 2*x + 2*y*h_res

	mov ax, [ebp+16]	// eax = color

	mov [esi + ebx], ax

	mov eax, 0	//pixel set successfully
	jmp end
ret1:
	mov eax, 1	// x < 0
	jmp end
ret2:
	mov eax, 2	// x >= h_res
	jmp end
ret3:
	mov eax, 3	// y < 0
	jmp end
ret4:
	mov eax, 4	// y >= v_res
	jmp end
end:
	leave
	ret
