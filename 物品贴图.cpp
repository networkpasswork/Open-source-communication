#include<windows.h>
#include<iostream>
//这而开始写

//mov rax, rsp
//push rbp
//push rsi
//push rdi
//sub rsp, 250h
//mov qword ptr[rsp + 38h], 0FFFFFFFFFFFFFFFEh
//mov qword ptr[rax + 20h], rbx
//movaps xmmword ptr[rax - 28h], xmm6
//movaps xmmword ptr[rax - 38h], xmm7
//movaps xmmword ptr[rax - 48h], xmm8
//movaps xmm8, xmm3
//mov rbp, r8
//mov rdi, rdx
//mov rsi, rcx
//movss xmm6, dword ptr[rsp + 2A0h]
//movss xmm7, dword ptr[rsp + 290h]
//cmp byte ptr[rsp + 2A8h], 0h
//je tslgame_7FF792429BD8
//mulss xmm8, xmm6
//mulss xmm7, xmm6
//tslgame_7FF792429BD8 :
//mov rbx, qword ptr[rsp + 298h]
//test rbx, rbx
//jne tslgame_7FF792429BED
//call qword ptr[Canvas_ConstDrawTextCall1]
//mov rbx, rax
//tslgame_7FF792429BED :
//mov rdx, rdi
//lea rcx, qword ptr[rsp + 40h]
//call qword ptr[Canvas_ConstDrawTextCall2]
//movss dword ptr[rsp + 30h], xmm8
//movss dword ptr[rsp + 34h], xmm7
//mov qword ptr[rsp + 20h], rbp
//mov r9, rbx
//mov r8, rax
//lea rdx, qword ptr[rsp + 30h]
//lea rcx, qword ptr[rsp + 58h]
//call qword ptr[Canvas_ConstDrawTextCall3]
//mov rbx, qword ptr[rsp + 48h]
//test rbx, rbx
//je tslgame_7FF792429C5A
//or edi, 0FFFFFFFFh
//mov eax, edi
//lock xadd dword ptr[rbx + 08h], eax
//cmp eax, 1
//jne tslgame_7FF792429C5A
//mov rax, qword ptr[rbx]
//mov rcx, rbx
//call qword ptr[rax]
//lock xadd dword ptr[rbx + 0Ch], edi
//cmp edi, 1
//jne tslgame_7FF792429C5A
//mov rax, qword ptr[rbx]
//mov edx, edi
//mov rcx, rbx
//call qword ptr[rax + 08h]
//tslgame_7FF792429C5A:
//movss dword ptr[rsp + 0F8h], xmm6
//movss dword ptr[rsp + 0FCh], xmm6
//lea rdx, qword ptr[rsp + 58h]
//mov rcx, rsi
//call qword ptr[Canvas_ConstDrawCall]
//lea rcx, qword ptr[rsp + 58h]
//call qword ptr[Canvas_ConstDrawTextCall4]
//lea r11, qword ptr[rsp + 250h]
//mov rbx, qword ptr[r11 + 38h]
//movaps xmm6, xmmword ptr[r11 - 10h]
//movaps xmm7, xmmword ptr[r11 - 20h]
//movaps xmm8, xmmword ptr[r11 - 30h]
//mov rsp, r11
//pop rdi
//pop rsi
//pop rbp
//ret















