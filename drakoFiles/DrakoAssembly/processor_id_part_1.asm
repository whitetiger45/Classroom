global _start

section .data

vendorid: resb 12

section .text

_start:
	xor eax, eax
	cpuid
	
	mov [vendorid],   ebx
	mov [vendorid+4], edx
	mov [vendorid+8], ecx
	
	mov eax, 4
	xor ebx, ebx
	inc ebx
	mov ecx, vendorid
	mov edx, 12
	int 0x80

exit:
	xor     eax, eax
	inc     eax
	xor		ebx, ebx
	int		0x80
