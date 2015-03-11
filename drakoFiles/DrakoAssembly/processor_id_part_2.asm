global _start

section .data

vendorid: resb 48

section .text

_start:
	mov eax, 0x80000002
	cpuid
	
	mov [vendorid],   eax
	mov [vendorid+4],   ebx
	mov [vendorid+8], ecx
	mov [vendorid+12], edx
	
	mov eax, 0x80000003
	cpuid
	
	mov [vendorid+16], eax
	mov [vendorid+20], ebx
	mov [vendorid+24], ecx
	mov [vendorid+28], edx
	
	mov eax, 0x80000004
	cpuid
	
	mov [vendorid+32], eax
	mov [vendorid+36], ebx
	mov [vendorid+40], ecx
	mov [vendorid+44], edx
	
	mov eax, 4
	mov ebx, 1
	mov ecx, vendorid
	mov edx, 48
	int 0x80

exit:
	xor     eax, eax
	inc     eax
	xor		ebx, ebx
	int		0x80
