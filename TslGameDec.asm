EXTERN  Aimbot_sw : DQ; 引用外部变量
EXTERN  Aimbot_x : DQ; 引用外部变量
EXTERN  Aimbot_y : DQ; 引用外部变量 
EXTERN  Aimbot_z : DQ; 引用外部变量 
EXTERN  HookSilenceAimBotReturn : DQ; 引用外部变量
EXTERN  HookTurnBulletReturn : DQ; 引用外部变量

EXTERN  HookAtanfReturn : DQ; 引用外部变量
EXTERN  JmpAtanfAddress : DQ; 引用外部变量





.CODE



Dec_PUBG PROC
push rbx
push rsi
push rdi
push r10
push r11
push r12
push r13
push r14
push r15
call qword ptr [r8]
pop r15
pop r14
pop r13
pop r12
pop r11
pop r10
pop rdi
pop rsi
pop rbx
ret
Dec_PUBG ENDP
END

