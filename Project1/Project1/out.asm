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
	L1 BYTE "hello world", 0
	L2 DWORD 2
	L3 DWORD 2
	L4 DWORD 2
	L5 BYTE "Результат:", 0
	L6 DWORD 3
	L7 DWORD 2
	L8 BYTE "it true", 0
	L9 BYTE "it false", 0
	L10 BYTE "hello", 0
	L11 BYTE "done", 0
	L12 DWORD 'f'
	L13 DWORD 2
	L14 DWORD 1
	L15 DWORD 2
	L16 DWORD 3
	L17 DWORD 1
	L18 DWORD 3
	L19 DWORD 5
	L20 DWORD 0
.DATA
	tsa DWORD 0
	tssts DWORD empty_string
	saa DWORD empty_string
	sab DWORD 0
	mainx DWORD 0
	mainy DWORD 0
	mainz DWORD 0
	mainksa DWORD empty_string
	mainghj DWORD 0

.CODE
ts PROC tsz:DWORD, tsx:DWORD
push offset L1
	pop tssts

	push L2
	push L3
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push L4
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov tsa, eax

push offset L5
call _printStr

push tssts
call _printStr

push tsa
call _printInt
	push tsx
	push tsz
	call _pow
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov tsa, eax
	push tsa
	jmp local0
local0:
	pop eax
	ret
ts ENDP

sa PROC sak:DWORD
	push L7
	push L6
	call _pow
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov sab, eax

push sab
call _printInt
	push sak
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov sab, eax
	mov eax, sab
	cmp eax, sak
	jz ifi1
	jnz else1
ifi1:
push offset L8
	pop saa

	jmp ifEnd1
else1:
push offset L9
	pop saa

ifEnd1:

push saa
call _printStr
	push OFFSET saa
	jmp local1
local1:
	pop eax
	ret
sa ENDP

sayhi PROC 

push offset L10
call _printStr
	push OFFSET L11
	jmp local2
local2:
	pop eax
	ret
sayhi ENDP

main PROC

	call sayhi
	push L12
	pop mainghj

	push L13
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainx, eax
	push L14
	push L15
	push L16
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
	mov mainy, eax
	mov eax, mainx
	cmp eax, mainy
	jz ifi2
	jnz else2
ifi2:
	push mainy
	push L17
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainx, eax
	jmp ifEnd2
else2:
	push mainy
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainx, eax
ifEnd2:
	push mainx
	call sa
	push eax
	pop mainksa

	push L18
	call _exp
	push eax
	push L19
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainz, eax

push mainz
call _printInt
	push mainy
	push mainx
	call ts
	push eax
	pop eax
	cmp eax, 255
	jg overflow
	cmp eax, 0
	jl overflow
	mov mainz, eax

push mainz
call _printInt
	push L20
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