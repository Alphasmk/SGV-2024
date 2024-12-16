.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib E:\unic\courseKPO\Project1\Debug\SGVLIB.lib
	ExitProcess PROTO :DWORD

	_exp PROTO :DWORD
	_pow PROTO :DWORD, :DWORD
	_printInt PROTO :DWORD
	_printStr PROTO :DWORD
	_printBool PROTO :DWORD
	_printChar PROTO :DWORD
	_pause PROTO

.stack 4096
.CONST
	null_division BYTE 'ERROR: DIVISION BY ZERO', 0
	OVER_FLOW BYTE 'ERROR: OVERFLOW', 0
	true BYTE "true", 0
	false BYTE "false", 0
	empty_string BYTE 0
	L1 DWORD 2
	L2 DWORD 2
	L3 DWORD 2
	L4 BYTE "hello", 0
	L5 DWORD 0
.DATA
	maina DWORD 0

.CODE
main PROC
	push L1
	push L2
	push L3
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov maina, eax

push offset L4
call _printStr
	push L5
	jmp theend

jmp theend
SOMETHINGWRONG::
	push offset null_division
	call _printStr
jmp THEEND
THEEND:
	push eax
	call ExitProcess
overflow::
	push offset OVER_FLOW
	call _printStr
main ENDP
end main