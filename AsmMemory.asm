EXTERN  FuncIndex : DD; 引用外部变量
.CODE

Asm_SysCall PROC
mov r10,rcx
mov eax,dword ptr[FuncIndex]
syscall
ret
Asm_SysCall ENDP


Asm_IsReadPtr PROC
push rdi
push rsi
sub rsp,18h
mov rdi,rcx
xor rsi,rsi
cmp rdi,1000h
jle Return2
Inloop:
add rdi,rsi
mov al, byte ptr [rdi]
inc rsi
cmp rsi,rdx
jle Inloop
xor eax,eax
jmp Return1
Return2:
mov rax,1h
Return1:
add rsp,18h
pop rsi
pop rdi
ret
Asm_IsReadPtr ENDP

Asm_CopyMemory PROC
push rdi
push rsi
push r8
sub rsp,18h
mov rdi,rcx
mov rsi,rdx
mov rcx,r8
rep movs byte ptr [rdi],byte ptr [rsi]
mov eax,1h
jmp Return1
xor eax,eax
Return1:
add rsp,18h
pop r8
pop rsi
pop rdi
ret
Asm_CopyMemory ENDP

Asm_ZeroMemory PROC
push rdi
push rsi
sub rsp,18h
mov rdi,rcx
xor rax,rax
mov rcx,rdx
rep stos byte ptr [rdi]
mov rax,1h
add rsp,18h
pop rsi
pop rdi
ret
Asm_ZeroMemory ENDP
END