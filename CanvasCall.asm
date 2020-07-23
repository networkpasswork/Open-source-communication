
EXTERN  Canvas_ConstDrawTextCall1 : DQ; 
EXTERN  Canvas_ConstDrawTextCall2 : DQ; ªÊ÷∆ÃÓ≥‰CALL
EXTERN  Canvas_ConstDrawTextCall3 : DQ; ªÊ÷∆ÃÓ≥‰CALL
EXTERN  Canvas_ConstDrawTextCall4 : DQ; ªÊ÷∆ÃÓ≥‰CALL

EXTERN  Canvas_ConstDrawLineAdds : DQ; ªÊ÷∆ÃÓ≥‰≥£¡ø

EXTERN  Canvas_ConstDrawRectAdds : DQ; ªÊ÷∆ÃÓ≥‰≥£¡ø
EXTERN  Canvas_ConstDrawRectCall : DQ; ªÊ÷∆ÃÓ≥‰CALL



EXTERN  Canvas_ConstDrawCall : DQ; ªÊ÷∆CALL
.CODE
UCanvas_DrawText PROC
mov rax,rsp
push rbp
push rsi
push rdi
sub rsp,250h
mov qword ptr [rsp+38h],0FFFFFFFFFFFFFFFEh
mov qword ptr [rax+20h],rbx
movaps xmmword ptr [rax-28h],xmm6
movaps xmmword ptr [rax-38h],xmm7
movaps xmmword ptr [rax-48h],xmm8
movaps xmm8,xmm3
mov rbp,r8
mov rdi,rdx
mov rsi,rcx
movss xmm6,dword ptr [rsp+2A0h]
movss xmm7,dword ptr [rsp+290h]
cmp byte ptr [rsp+2A8h],0h
je tslgame_7FF792429BD8
mulss xmm8,xmm6
mulss xmm7,xmm6
tslgame_7FF792429BD8:
mov rbx,qword ptr [rsp+298h]
test rbx,rbx
jne tslgame_7FF792429BED
call qword ptr [Canvas_ConstDrawTextCall1]
mov rbx,rax
tslgame_7FF792429BED:
mov rdx,rdi
lea rcx,qword ptr [rsp+40h]
call qword ptr [Canvas_ConstDrawTextCall2]
movss dword ptr [rsp+30h],xmm8
movss dword ptr [rsp+34h],xmm7
mov qword ptr [rsp+20h],rbp
mov r9,rbx
mov r8,rax
lea rdx,qword ptr [rsp+30h]
lea rcx,qword ptr [rsp+58h]
call qword ptr [Canvas_ConstDrawTextCall3]
mov rbx,qword ptr [rsp+48h]
test rbx,rbx
je tslgame_7FF792429C5A
or edi,0FFFFFFFFh
mov eax,edi
lock xadd dword ptr [rbx+08h],eax
cmp eax,1
jne tslgame_7FF792429C5A
mov rax,qword ptr [rbx]
mov rcx,rbx
call qword ptr [rax]
lock xadd dword ptr [rbx+0Ch],edi
cmp edi,1
jne tslgame_7FF792429C5A
mov rax,qword ptr [rbx]
mov edx,edi
mov rcx,rbx
call qword ptr [rax+08h]
tslgame_7FF792429C5A:
movss dword ptr [rsp+0F8h],xmm6
movss dword ptr [rsp+0FCh],xmm6
lea rdx,qword ptr [rsp+58h]
mov rcx,rsi
call qword ptr [Canvas_ConstDrawCall]
lea rcx,qword ptr [rsp+58h]
call qword ptr [Canvas_ConstDrawTextCall4]
lea r11,qword ptr [rsp+250h]
mov rbx,qword ptr [r11+38h]
movaps xmm6,xmmword ptr [r11-10h]
movaps xmm7,xmmword ptr [r11-20h]
movaps xmm8,xmmword ptr [r11-30h]
mov rsp,r11
pop rdi
pop rsi
pop rbp
ret 
UCanvas_DrawText ENDP


UCanvas_DrawLine PROC
mov rax,rsp
push rbx
sub rsp,0C0h
mov qword ptr [rsp+20h],0FFFFFFFFFFFFFFFEh
movaps xmmword ptr [rax-18h],xmm6
movaps xmmword ptr [rax-28h],xmm7
movaps xmmword ptr [rax-38h],xmm8
movaps xmm8,xmm3
movaps xmm6,xmm2
movaps xmm7,xmm1
mov rbx,rcx
movss dword ptr [rsp+38h],xmm7
movss dword ptr [rsp+3Ch],xmm6
xor eax,eax
mov qword ptr [rsp+40h],rax
mov byte ptr [rsp+48h],al
mov qword ptr [rsp+50h],rax
mov rax,qword ptr [Canvas_ConstDrawLineAdds]
mov qword ptr [rsp+30h],rax
movss dword ptr [rsp+68h],xmm7
movss dword ptr [rsp+6Ch],xmm6
mov dword ptr [rsp+70h],0
movss dword ptr [rsp+74h],xmm8
movss xmm1,dword ptr [rsp+0F0h]
movss dword ptr [rsp+78h],xmm1
mov dword ptr [rsp+7Ch],0
mov rax,qword ptr [rsp+0F8h]
movups xmm0,xmmword ptr [rax]
movups xmmword ptr [rsp+58h],xmm0
movss xmm1,dword ptr [rsp+100h]
movss dword ptr [rsp+80h],xmm1
lea rdx,qword ptr [rsp+30h]
mov rcx,rbx
call qword ptr [Canvas_ConstDrawCall]
lea r11,qword ptr [rsp+0C0h]
movaps xmm6,xmmword ptr [r11-10h]
movaps xmm7,xmmword ptr [r11-20h]
movaps xmm8,xmmword ptr [r11-30h]
mov rsp,r11
pop rbx
ret 
UCanvas_DrawLine ENDP



UCanvas_DrawRect PROC
mov rax, rsp
push rdi
sub rsp, 0F0h
mov qword ptr [rsp+40h], 0FFFFFFFFFFFFFFFEh
mov qword ptr [rax+08h], rbx
movaps xmmword ptr [rax-18h], xmm6
movaps xmmword ptr [rax-28h],xmm7
movaps xmm6,xmm3
movaps xmm7,xmm2
mov rdi,rdx
mov rbx,rcx
movss xmm0,dword ptr [rsp+120h]
movss dword ptr [rsp+30h],xmm0
movss xmm1,dword ptr [rsp+128h]
movss dword ptr [rsp+34h],xmm1
movss dword ptr [rsp+38h],xmm7
movss dword ptr [rsp+3Ch],xmm6
mov qword ptr [rsp+20h],rdi
lea r9,qword ptr [rsp+30h]
mov r8,qword ptr [Canvas_ConstDrawRectAdds]
mov r8,qword ptr [r8]
lea rdx,qword ptr [rsp+38h]
lea rcx,qword ptr [rsp+50h]
call qword ptr [Canvas_ConstDrawRectCall]
mov dword ptr [rsp+64h],2h
lea rdx,qword ptr [rsp+50h]
mov rcx,rbx
call qword ptr [Canvas_ConstDrawCall]
lea r11,qword ptr [rsp+0F0h]
mov rbx,qword ptr [r11+10h]
movaps xmm6,xmmword ptr [r11-10h]
movaps xmm7,xmmword ptr [r11-20h]
mov rsp,r11
pop rdi
ret
UCanvas_DrawRect ENDP

END